#pragma once

// Undefine any potential min/max macros before including physac
#undef min
#undef max

#ifdef _WIN32
    // Definitions
    #define NOGDI                // Prevents Windows GDI function definitions
    #define NOUSER              // Prevents conflicts with user interface functions
    #define WIN32_LEAN_AND_MEAN // Excludes rarely-used stuff from Windows headers
    // #define NOMINMAX

    // Includes
    // Make sure we have the time API available
    #include <windows.h>
    // #include <mmsystem.h>
    #include <winbase.h>

    // Ensure these are linked
    // #pragma comment(lib, "winmm.lib")
    // Make sure we have the time API available
#endif


#include "profileapi.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
// #include <algorithm>


#include "../external/raylib/raylib.h"

using namespace std;

// Screen config ---------------------------
const char screenTitle[] = "CGame v0.0.1";
const int screenWidth = 800;
const int screenHeight = 450;
// -----------------------------------------


class Game {
    
private:
    // Prevent instantiation
    Game() = delete;
    static int bodiesCount;
public: 
    static void Run();
    static void Start(); // called at start of game
    static void Update(); // called once a frame
    static void Draw(); // where everything is drawn
    static void Close(); // called when game closes
};