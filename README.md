# 🏓 Pong Game (SFML 3.0.0)
<p align="center"> <img src="https://github.com/amaraoussama94/Pong/blob/main/Game.png" alt="Pong Game Screenshot"> </p>
A modern, cross-platform Pong clone built with C++17 and SFML 3.0.0. Supports both single-player and multiplayer modes, with smooth frame-rate independent movement and a retro-style HUD.

---

## 🎮 Features

- 🧠 **Game Modes**: Single-player and two-player (local multiplayer)
- ⚙️ **Cross-Platform**: Builds on both Windows and Linux
- 🖼️ **Dynamic Resolution**: Adapts to your screen size
- ⏱️ **Frame-Rate Independent**: Uses delta time for smooth movement
- 🎨 **Retro HUD**: Styled with a digital font
- 🧱 **Modular Code**: Clean separation of logic (Ball, Bat, Game loop)

---
## 🧩 Project Structure
Pong/
├── include/         # Header files

│   ├── Ball.hpp

│   └── Bat.hpp

├── src/             # Source files

│   ├── Ball.cpp

│   ├── Bat.cpp

│   └── Pong.cpp     # Contains main()

├── external/        # SFML submodule

│   └── SFML/

├── fonts/           # Font assets

│   └── ...

├── Game.png         # Game screenshot

├── Makefile         # Build instructions

├── .github/         # GitHub Actions workflows

│   └── workflows/

│       └── build.yml # CI/CD pipeline for building on Linux and Windows

├── bin/             # Output directory for binaries

│   └── pong         # Compiled executable

├── README.md        # Project documentation

## 🚀 Getting Started

### 🔧 Prerequisites

- **C++17-compatible compiler**
- **CMake ≥ 3.24**
- **SFML 3.0.0** (included as a submodule)

### 🛠️ Build Instructions

#### 🐧 Linux

```bash
sudo apt install build-essential cmake libx11-dev libxrandr-dev libxcursor-dev libxi-dev libxinerama-dev libgl1-mesa-dev libudev-dev libopenal-dev libflac-dev libvorbis-dev libfreetype6-dev
git clone --recurse-submodules https://github.com/yourusername/Pong.git
cd Pong
make
./bin/pong
### 🪟 Windows Build Instructions

#### Option 1: Using MinGW (GCC)

1. ✅ Install [MinGW-w64](https://www.mingw-w64.org/) with GCC 14.2.0 or compatible
2. ✅ Download the **SFML 3.0.0 MinGW package** from [SFML Downloads](https://www.sfml-dev.org/download/sfml/3.0.0/)
3. ✅ Extract SFML and place it in your project directory (e.g., `external/SFML`)
4. ✅ Add SFML's `include/` and `lib/` paths to your Makefile or compile command

Example compile command:
```bash
g++ src/*.cpp -Iexternal/SFML/include -Lexternal/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -o Pong.exe

## 🎮 Controls

| Key(s)       | Player        | Action              |
|--------------|---------------|---------------------|
| `Escape`     | —             | Exit the game       |
| `M`          | —             | Open/close menu     |
| `L` / `R`    | Player 1      | Move bat up/down    |
| `Q` / `D`    | Player 2      | Move bat up/down    |

---

## 📝 Version

- **Game Title**: Pong  
- **Current Version**: `v1.8`  
- **Build Type**: Standalone, portable  
- **Last Updated**: July 2025
