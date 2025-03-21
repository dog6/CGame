@echo off
g++ src/source.cpp -o build/cgame.exe -Lsrc/external/raylib -lraylib -lOpenGL32 -lm -lgdi32 -lwinmm
cd build
cgame
cd ..