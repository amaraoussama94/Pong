# === CONFIGURATION ===
#Sets the name of your final executable
PROJECT_NAME = pong
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
#where the final executable goes
BIN_DIR = bin
SFML_DIR = external/SFML
#where SFML will be built using CMake
SFML_BUILD_DIR = $(SFML_DIR)/build
# Compiler configuration
CXX = g++

# Compiler flags
#-std=c++17: use C++17 standard
#-Wall: enable all warnings
#-I...: include SFML headers
CXXFLAGS = -std=c++17 -Wall -I$(SFML_DIR)/include -I$(INC_DIR)

# Linker flags
LDFLAGS = 
# finds all .cpp files in src/
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
#SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')
#maps each .cpp file to a corresponding .o file in build/
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# === OS DETECTION ===
#Detects the operating system using uname
UNAME_S := $(shell uname -s)
#SFML_LIB_DIR: where to find the built SFML .lib or .a files
ifeq ($(UNAME_S),Linux)
	SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
	SFML_LIB_DIR = $(SFML_BUILD_DIR)/lib
	EXE = $(BIN_DIR)/$(PROJECT_NAME)
	COPY_DLLS = @true
	CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=TRUE
else
	SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
	SFML_LIB_DIR = $(SFML_BUILD_DIR)/lib
	EXE = $(BIN_DIR)/$(PROJECT_NAME).exe
#If on Windows, copy the SFML DLLs to the bin directory
	COPY_DLLS = cp $(SFML_BIN_DIR)/*.dll $(BIN_DIR)/
#works with MSYS2 or MinGW to avoid fail related	to CMake policies
	CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=TRUE -DCMAKE_POLICY_VERSION=3.5
endif

# === TARGETS ===
#The default target. It builds SFML first, then your game.
all: $(SFML_BUILD_DIR)/lib/libsfml-graphics.a $(EXE)

#Builds SFML if it hasn’t been built yet:
$(SFML_BUILD_DIR)/lib/libsfml-graphics.a:
	@echo " Building SFML..."
	mkdir -p $(SFML_BUILD_DIR)
	cd $(SFML_BUILD_DIR) && cmake .. $(CMAKE_FLAGS)
 	$(MAKE) -C $(SFML_BUILD_DIR)


#Compiles each .cpp file into a .o object file
#$< is the source file, $@ is the output object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#Links all object files into the final executable
#$^ is the list of object files
#-L...: tells the linker where to find SFML libraries
#$(SFML_LIBS): links against SFML
$(EXE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $@ -L$(SFML_LIB_DIR) $(SFML_LIBS)
	$(COPY_DLLS)

#Deletes your object files and final binary
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

#Also deletes the SFML build directory
clean-all: clean
	rm -rf $(SFML_BUILD_DIR)

#Declares these targets as "phony" (not real files), so Make always runs them when requested
.PHONY: all clean clean-all
