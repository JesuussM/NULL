# Compilers
CC = gcc
CXX = g++

# Output binary
TARGET = NULL

# Directories
SRC_DIR = src
ENGINE_DIR = $(SRC_DIR)/engine
ASSETS_DIR = $(SRC_DIR)/assets
SHADERS_DIR = $(ASSETS_DIR)/shaders
UTIL_DIR = util
IMGUI_DIR = $(UTIL_DIR)/imgui

# Include paths
INCLUDES = \
	-I$(SRC_DIR) \
	-I$(ENGINE_DIR) \
	-I$(ASSETS_DIR) \
	-I$(SHADERS_DIR) \
	-I$(UTIL_DIR) \
	-I$(IMGUI_DIR)

# Compiler flags
CFLAGS = -Wall -Wextra -g $(INCLUDES)
CXXFLAGS = -Wall -Wextra -g $(INCLUDES)

# Linker libs (Windows-style since you're using d3d11 headers in sokol setup likely)
LIBS = -ld3d11 -ldxgi -ldxguid -lgdi32 -luser32 -lshell32 -lole32

# Sources
C_SRC = \
	$(SRC_DIR)/main.c \
	$(ENGINE_DIR)/sokol_util.c \
	$(ENGINE_DIR)/renderer.c \
	$(ENGINE_DIR)/gui.c \

CPP_SRC = \
	$(IMGUI_DIR)/cimgui.cpp \
	$(IMGUI_DIR)/imgui.cpp \
	$(IMGUI_DIR)/imgui_demo.cpp \
	$(IMGUI_DIR)/imgui_draw.cpp \
	$(IMGUI_DIR)/imgui_tables.cpp \
	$(IMGUI_DIR)/imgui_widgets.cpp

# Objects
OBJ = $(C_SRC:.c=.o) $(CPP_SRC:.cpp=.o)

# Build rule
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS)

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJ) $(TARGET).exe

# Rebuild
rebuild: clean all

# Run
run: $(TARGET)
	./$(TARGET).exe

# Clean and Run
rerun: rebuild
	./$(TARGET).exe