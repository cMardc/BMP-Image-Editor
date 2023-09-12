CXX = g++
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/bmp_editor
LIBS = -lX11

all: $(TARGET)

$(TARGET): $(SRC_DIR)/main.cpp
	$(CXX) $< -o $@ $(LIBS)

clean:
	rm -f $(BUILD_DIR)/bmp_editor

.PHONY: all clean
