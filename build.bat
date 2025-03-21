@echo off
del build\*.exe
g++ -v src/includes/source.cpp src/includes/game.cpp -o build/cgame.exe -Lsrc/external/raylib -Isrc/external/physac -lraylib -lopengl32 -lm -lgdi32 -pthread -lwinmm
@REM g++ -v src/includes/source.cpp src/includes/game.cpp -o build/cgame.exe -Lsrc/external/raylib -lraylib -Isrc/external/physac -lopengl32 -lm -lgdi32 -pthread -lwinmm
cd build
cgame
cd ..

@REM g++ src/test.cpp -o build/cgame_test.exe -Lsrc/external/raylib -lraylib -Isrc/external/physac -lopengl32 -lm -lgdi32  -static -pthread -lwinmm