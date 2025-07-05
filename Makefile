# === CONFIGURATION ===
# Sets the name of your final executable
PROJECT_NAME = pong
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# SFML submodule and build paths
SFML_DIR = external/SFML
SFML_BUILD_DIR = $(SFML_DIR)/build
SFML_INSTALL_DIR = $(SFML_DIR)/install

# Compiler configuration
CXX = g++

# Compiler flags
# -std=c++17: use C++17 standard
# -Wall: enable all warnings
# -I...: include SFML and project headers
CXXFLAGS = -std=c++17 -Wall -I$(SFML_INSTALL_DIR)/include -I$(INC_DIR)

# Linker flags
LDFLAGS = -L$(SFML_INSTALL_DIR)/lib -lsfml-graphics -lsfml-window -lsfml-system

# Finds all .cpp files in src/
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# Maps each .cpp file to a corresponding .o file in build/
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# === OS DETECTION ===
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	EXE = $(BIN_DIR)/$(PROJECT_NAME)
	COPY_DLLS = @true
	CMAKE_GENERATOR = -G "Unix Makefiles"
	CMAKE_ENV =
else ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
	EXE = $(BIN_DIR)/$(PROJECT_NAME).exe
	COPY_DLLS = if exist $(SFML_INSTALL_DIR)/bin/*.dll copy $(SFML_INSTALL_DIR)/bin\*.dll $(BIN_DIR)\ >nul
	CMAKE_GENERATOR = -G "MinGW Makefiles"
	CMAKE_ENV = -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_MAKE_PROGRAM=mingw32-make
else ifeq ($(findstring MSYS,$(UNAME_S)),MSYS)
	EXE = $(BIN_DIR)/$(PROJECT_NAME).exe
	COPY_DLLS = cp $(SFML_INSTALL_DIR)/bin/*.dll $(BIN_DIR) 2>/dev/null || true
	CMAKE_GENERATOR = -G "Unix Makefiles"
	CMAKE_ENV =
else
	$(error Unsupported platform: $(UNAME_S))
endif

#	=== COMPILER AND MAKE PROGRAMS ===
# This section sets the C++ compiler, C compiler, and make program based on the detected OS.
# It ensures the correct tools are used for building the project, especially on Windows with MinGW
ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
	CXX := $(shell which g++)
	CC := $(shell which gcc)
	MAKE_PROGRAM := $(shell which mingw32-make)
	CMAKE_ENV = -DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX) -DCMAKE_MAKE_PROGRAM=$(MAKE_PROGRAM)
endif

#	=== ENVIRONMENT CHECK ===
# This target prints environment variables and compiler settings for debugging.
# It helps verify that the Makefile is using the correct tools and paths.
check-env:
	@echo "UNAME_S = $(UNAME_S)"
	@echo "MSYSTEM = $(shell echo $$MSYSTEM)"
	@echo "CXX = $(CXX)"
	@echo "CC = $(CC)"
	@echo "PATH = $$PATH"


# === TARGETS ===
# The default target. It builds SFML first, then your game.
all: $(SFML_INSTALL_DIR)/lib/libsfml-graphics.a $(EXE)

# Builds SFML if it hasn’t been built yet
# === Build and Install SFML from Source ===
# This rule ensures SFML is built and installed before compiling the game.
# It triggers when the static graphics library is missing from the install directory.
# 
# Steps:
# 1. Creates the SFML build directory if it doesn't exist.
# 2. Runs CMake to configure the SFML project:
#    - Uses the appropriate generator (e.g. "MinGW Makefiles" on Windows).
#    - Sets the install prefix to SFML_INSTALL_DIR to isolate headers/libs/DLLs.
#    - Enables shared library builds for dynamic linking.
#    - Explicitly sets compiler and make program on Windows to avoid CMake errors.
# 3. Builds SFML using make.
# 4. Installs the built libraries, headers, and DLLs into SFML_INSTALL_DIR.
#
# This setup ensures your project uses a clean, portable, and compiler-compatible SFML build.

$(SFML_INSTALL_DIR)/lib/libsfml-graphics.a:
	@echo "Building SFML in $(SFML_BUILD_DIR)..."
	mkdir -p $(SFML_BUILD_DIR)
	cd $(SFML_BUILD_DIR) && cmake .. $(CMAKE_GENERATOR) \
		-DCMAKE_INSTALL_PREFIX=$(abspath $(SFML_INSTALL_DIR)) \
		-DCMAKE_BUILD_TYPE=Release \
		-DBUILD_SHARED_LIBS=TRUE \
		$(CMAKE_ENV)
	$(MAKE) -C $(SFML_BUILD_DIR)
	$(MAKE) -C $(SFML_BUILD_DIR) install

# Compiles each .cpp file into a .o object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Links all object files into the final executable
$(EXE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS)
	$(COPY_DLLS)

# Deletes your object files and final binary
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Also deletes the SFML build and install directories
clean-all: clean
	rm -rf $(SFML_BUILD_DIR) $(SFML_INSTALL_DIR)

.PHONY: all clean clean-all
