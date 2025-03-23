
# CGame Docs

__# Getting started__

      As of v0.0.1, CMake is not properly configured, and the recommended way to compile the application is
    to run the `build.bat` file provided. Building on linux is not currently automated.
    Below is the the g++ command for building on windows:

        `g++ src/*.cpp src/shapes/*.cpp -o bin/cgame.exe -Llib/raylib -lraylib -lopengl32 -lgdi32 -lwinmm`

__Building w/ `build.bat` on Windows__

    - MinGW in Path enviroment (for G++/GCC)
