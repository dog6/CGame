@echo off
setlocal enabledelayedexpansion
chcp 65001

echo Building Project 🔨 


:: Set source directory
set SOURCE_DIR=./src

:: Set project name
set PROJECT_NAME=cgame

:: delete previous version (should possibly make it copy a previous verison.exe)
if exist bin/%PROJECT_NAME%.exe (
    echo Deleted old cgame.exe 🗑️
    del bin\%PROJECT_NAME%.exe
)

:: link source files
for /r "%SOURCE_DIR%" %%f in (*.cpp) do (
    echo Adding source %%f ➕ 
    set sources=!sources! %%f
)

echo Linking sources files.. 🔗
echo !sources!
echo. 

:: Compile code
echo Compiling..
echo g++ !sources! -o bin/%PROJECT_NAME%.exe -Llib/raylib -lraylib -Llib/raygui -lopengl32 -lgdi32 -lwinmm
echo.
echo -------------------------------------------------------------------------------------------------------------------
echo.
g++ !sources! -o bin/%PROJECT_NAME%.exe -Llib/raylib -lraylib -Llib/raygui -lopengl32 -lgdi32 -lwinmm

:: try to run .exe
if exist bin/%PROJECT_NAME%.exe (
    echo Compilation Successful :D ✅
    echo Starting game.. 🚀
    cd bin
    %PROJECT_NAME%.exe
    cd ..
) else (
    echo Compilation Failed :( ❌
)