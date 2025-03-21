@echo off
g++ src/includes/source.cpp src/includes/game.cpp -o build/cgame.exe -Lsrc/external/raylib -lraylib -lOpenGL32 -lm -lgdi32 -lwinmm
cd build
cgame
cd ..