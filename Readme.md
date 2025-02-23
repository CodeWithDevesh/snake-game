# Snake Game

A simple Snake Game built using **C++** and **SFML**.

## Requirements
- **CMake** (version 3.10 or higher)
- **Git**
- **A C++ Compiler** (MSVC, GCC, or Clang)

## Getting Started

### 1. Clone the Repository
```sh
git clone https://github.com/CodeWithDevesh/snake-game.git
cd snake-game
```

## Build the Project
Be patient as this step downloads the required libraries too
### Windows

```sh
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Linux/macOS (GCC/Clang + Make)

```sh
mkdir build && cd build
cmake ..
make -j$(nproc)
```

## Run the Game
After building, the executable will be inside Release or Debug folder in build.

### Windows
```sh
cd Release
snake-game.exe
```

### Linux
```sh
./snake-game
```

## Ensure SFML DLLs are Present (Windows Only)
If the game does not run due to missing DLLs, manually copy the required SFML DLLs from the build/_deps/sfml-build/lib folder to the executable directory.

## Notes
- SFML is automatically fetched via CMake's FetchContent.
- If using a different compiler, adjust the cmake command accordingly.