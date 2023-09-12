# BMP Image Editor

![BMP Image Editor](assets/logo.png)

## Overview

This is a simple BMP image editor written in C++ that utilizes the CImg.h library for image processing. It allows you to open, edit, and save BMP image files using both keyboard and mouse input. You can change colors, adjust thickness, save your work, undo changes, and exit the program with or without saving.

## Features

- Open and edit BMP image files.
- Change the drawing color using keyboard shortcuts.
- Adjust the drawing thickness using keyboard shortcuts.
- Save your edited image to a new file or overwrite the original.
- Undo changes made during the editing session.
- Exit the program with or without saving your work.

## Prerequisites

Before using the BMP image editor, you need to ensure that you have the following:

- CImg.h Library: The editor relies on the CImg.h library for image processing. Make sure you have it installed or included in your project.

## Usage

You can run the BMP image editor in different ways:

1. Run the editor with a blank canvas:
```./bmp_editor```

2. Open an existing BMP image for editing:
```./bmp_editor input_file.bmp```

3. Open an existing BMP image, make edits, and save it to a new file:
```./bmp_editor input_file.bmp output_file.bmp```


## Key Bindings

- **Change Colors:**
- Red: `1`
- Orange: `2`
- Yellow: `3`
- Green: `4`
- Cyan: `5`
- Blue: `6`
- Purple: `7`
- Gray: `8`
- White: `9`
- Black: `0`

- **Change Thickness:**
- Increase Thickness: `d`
- Decrease Thickness: `a`

- **General Actions:**
- Exit Without Saving: `q`
- Exit and Save: `x`
- Undo: `Ctrl+Z` or `z`

## Mouse Usage

- Left-click and drag the mouse to draw on the canvas.
- The drawing color and thickness can be adjusted using keyboard shortcuts.

## Configuration

The editor loads configuration data from JSON files. You can find the configuration files in the "config" directory.

- `path.json`: Specifies the paths to the blank canvas image and other resources.
- `keys.json`: Defines key bindings for colors, thickness, and general actions.

## Saving Changes

When you exit the program with the "Exit and Save" option, it will save your edited image to the specified output file or overwrite the input file if no output file is specified.

## Undo Changes

You can undo your last action by pressing `Ctrl+Z` or `z`. The editor maintains a history of changes, allowing you to step back through your editing session.

## License

This BMP image editor is open-source software licensed under the MIT License. Feel free to modify and distribute it as needed.

## Author

- cMard

If you have any questions or encounter issues with the editor, please don't hesitate to contact the author.

Happy editing! 🎨🖌️
