#include <CImg.h>  // Include the CImg library for image manipulation

#include <filesystem>  // Include the filesystem library for file operations
#include <fstream>     // Include the file stream library for file I/O
#include <iostream>    // Include the standard I/O library
#include <nlohmann/json.hpp>  // Include the nlohmann JSON library for JSON parsing
#include <string>             // Include the string library
#include <vector>             // Include the vector library

using namespace cimg_library;  // Use the CImg library namespace
using std::string, std::vector, std::to_string, std::range_error;

namespace fs =
    std::filesystem;  // Alias the filesystem namespace for convenience

#define path_symbol \
  fs::path::preferred_separator  // Define the preferred path separator

// Function to read JSON data from a file
nlohmann::json readJsonFromFile(const std::string& filename) {
  nlohmann::json jsonData;  // Create a JSON object to store the data

  // Open the JSON file
  std::ifstream inputFile(filename);

  if (!inputFile.is_open()) {  // Check if the file opening failed
    std::cerr << "Error: Unable to open file " << filename << '\n';
    return jsonData;  // Return an empty JSON object in case of an error
  }

  try {
    // Parse the JSON data from the file
    inputFile >> jsonData;
  } catch (const nlohmann::json::parse_error& e) {
    std::cerr << "JSON parsing error: " << e.what() << '\n';
  }

  // Close the file
  inputFile.close();

  return jsonData;  // Return the JSON data
}

// Function to get the current directory
string get_current_directory() {
  fs::path scriptPath = fs::canonical(fs::path("/proc/self/exe"));
  return scriptPath.parent_path().string();
}

// Function to change the color of a single pixel in an image
void changePixelValue(CImg<unsigned char>& image, int x, int y, int red,
                      int green, int blue) {
  if (x >= 0 && x < image.width() && y >= 0 && y < image.height()) {
    image(x, y, 0, 0) = static_cast<unsigned char>(red);
    image(x, y, 0, 1) = static_cast<unsigned char>(green);
    image(x, y, 0, 2) = static_cast<unsigned char>(blue);
  } else {
    throw range_error("Invalid pixel coordinates: " + to_string(x) + " " +
                      to_string(y));
  }
}

// Function to change the color of a pixel with a specified thickness
void changePixelValueWithThickness(CImg<unsigned char>& image, int x, int y,
                                   int red, int green, int blue,
                                   int thickness) {
  int halfThickness = thickness / 2;

  for (int i = x - halfThickness; i <= x + halfThickness; i++) {
    for (int j = y - halfThickness; j <= y + halfThickness; j++) {
      if (i >= 0 && i < image.width() && j >= 0 && j < image.height()) {
        image(i, j, 0, 0) = static_cast<unsigned char>(red);
        image(i, j, 0, 1) = static_cast<unsigned char>(green);
        image(i, j, 0, 2) = static_cast<unsigned char>(blue);
      }
    }
  }
}

// Function to convert an integer to a character
char int_to_char(int number) { return number + 48; }

int main(int argc, char* argv[]) {
  // Initialize CImg display window
  CImgDisplay main_disp;

  const string current_directory = get_current_directory();

  // Read JSON configuration data from files
  auto path_json_data =
      readJsonFromFile(current_directory + path_symbol + ".." + path_symbol +
                       "config" + path_symbol + "path.json");
  auto keys_json_data =
      readJsonFromFile(current_directory + path_symbol + ".." + path_symbol +
                       "config" + path_symbol + "keys.json");

  auto blank_dirs = path_json_data["blank_dir"];  // Extract data from JSON

  // Map color keys from JSON to characters
  char red = int_to_char(keys_json_data["colors"]["red"]);
  char orange = int_to_char(keys_json_data["colors"]["orange"]);
  char yellow = int_to_char(keys_json_data["colors"]["yellow"]);
  char green = int_to_char(keys_json_data["colors"]["green"]);
  char cyan = int_to_char(keys_json_data["colors"]["cyan"]);
  char blue = int_to_char(keys_json_data["colors"]["blue"]);
  char purple = int_to_char(keys_json_data["colors"]["purple"]);
  char gray = int_to_char(keys_json_data["colors"]["gray"]);
  char white = int_to_char(keys_json_data["colors"]["white"]);
  char black = int_to_char(keys_json_data["colors"]["black"]);

  // Extract string values from JSON
  string STR_increase_thickness = keys_json_data["thickness"]["increase"];
  string STR_decrease_thickness = keys_json_data["thickness"]["decrease"];
  string STR_exit_without_saving =
      keys_json_data["general"]["exit_without_saving"];
  string STR_exit_and_save = keys_json_data["general"]["exit_and_save"];
  string STR_undo = keys_json_data["general"]["undo"];

  // Map string values to characters
  char increase_thickness = STR_increase_thickness[0];
  char decrease_thickness = STR_decrease_thickness[0];
  char exit_without_saving = STR_exit_without_saving[0];
  char exit_and_save = STR_exit_and_save[0];
  char undo = STR_undo[0];

  string blank_dir = current_directory;

  // Construct the path to the blank image file using JSON data
  for (size_t i = 0; i < blank_dirs.size(); i++) {
    blank_dir += path_symbol;
    blank_dir += blank_dirs[i];
  }

  blank_dir += path_symbol;
  blank_dir += path_json_data["blank_file"];

  // Load an image from file
  CImg<unsigned char> image(blank_dir.c_str());

  // If command-line arguments are provided, load an image specified by the user
  if (argc == 2 || argc == 3) {
    image.load(argv[1]);
  }

  vector<CImg<unsigned char>>
      undo_images;               // Create a vector to store image history
  undo_images.push_back(image);  // Store the initial image state

  // Display the image
  main_disp.display(image);

  unsigned long long var = 0;

  unsigned char red_inp = 0, blue_inp = 0, green_inp = 0;
  int thickness = 15;

  while (!main_disp.is_closed()) {
    main_disp.wait();

    if (main_disp.key()) {
      char key = main_disp.key();  // Get the pressed key

      // Handle key press here
      if (key == tolower(exit_without_saving) ||
          key == toupper(exit_without_saving)) {
        break;  // Exit the loop if 'q' is pressed
      } else if (key == tolower(undo) || key == toupper(undo)) {
        if (undo_images.size() > 1) {
          image = undo_images.back();  // Restore the last saved image state
          undo_images.pop_back();
        } else {
          image = undo_images.back();  // Restore the last saved image state
        }
      } else if (key == tolower(exit_and_save) ||
                 key == toupper(exit_and_save)) {
        if (argc == 2) {
          image.save(argv[1]);  // Save the image to the specified filename
          break;
        } else if (argc == 3) {
          image.save(
              argv[2]);  // Save the image to the second specified filename
          break;
        }
        image.save("untitled.bmp");  // Save the image with a default filename
        break;
      } else if (key == red) {
        red_inp = 255;
        green_inp = 0;
        blue_inp = 0;
      } else if (key == orange) {
        red_inp = 255;
        green_inp = 128;
        blue_inp = 0;
      } else if (key == yellow) {
        red_inp = 255;
        green_inp = 255;
        blue_inp = 0;
      } else if (key == green) {
        red_inp = 0;
        green_inp = 255;
        blue_inp = 0;
      } else if (key == cyan) {
        red_inp = 0;
        green_inp = 255;
        blue_inp = 255;
      } else if (key == blue) {
        red_inp = 0;
        green_inp = 0;
        blue_inp = 255;
      } else if (key == purple) {
        red_inp = 255;
        green_inp = 0;
        blue_inp = 255;
      } else if (key == gray) {
        red_inp = 128;
        green_inp = 128;
        blue_inp = 128;
      } else if (key == white) {
        red_inp = 255;
        green_inp = 255;
        blue_inp = 255;
      } else if (key == black) {
        red_inp = 0;
        green_inp = 0;
        blue_inp = 0;
      } else if (key == tolower(decrease_thickness) ||
                 key == toupper(decrease_thickness)) {
        if (thickness >= 1) {
          thickness -= 1;
        }
      } else if (key == tolower(increase_thickness) ||
                 key == tolower(increase_thickness)) {
        if (thickness <= 50) {
          thickness += 1;
        }
      }
    }

    if (main_disp.button() && main_disp.mouse_y() >= 0) {
      // Get the pixel color at the mouse cursor position
      const int x = main_disp.mouse_x();
      const int y = main_disp.mouse_y();
      const unsigned char red = image(x, y, 0, 0);
      const unsigned char green = image(x, y, 0, 1);
      const unsigned char blue = image(x, y, 0, 2);
      var += 1;

      // Check if a certain number of pixel edits have occurred to push to undo
      // stack
      if (var % 100 == 0) {
        undo_images.push_back(
            image);  // Push the current image to the undo stack
      }

      // Call the function to change the pixel color with the specified
      // thickness
      changePixelValueWithThickness(image, x, y, red_inp, green_inp, blue_inp,
                                    thickness);
    }
    main_disp.display(image);  // Update the displayed image
  }

  return 0;  // Program termination
}
