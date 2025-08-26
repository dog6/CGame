#pragma once

#ifndef GAME_HPP
#define GAME_HPP
// # Vector2 definitions -----------------

// Directions relative to window ---------
#define VECTOR2_UP Vector2{0,-1}
#define VECTOR2_DOWN Vector2{0, 1}
#define VECTOR2_RIGHT Vector2{1, 0}
#define VECTOR2_LEFT Vector2{-1,0}
//----------------------------------------

// Cardinal directions <raylib Vector2>-------------------
#define NORTH_WEST Vector2{-1,-1}
#define NORTH Vector2{0,-1}
#define NORTH_EAST Vector2{1,-1}

#define SOUTH_WEST Vector2{-1,-1}
#define SOUTH Vector2{0, 1}
#define SOUTH_EAST Vector2{1,-1}

#define EAST Vector2{1, 0}
#define WEST Vector2{-1,0}
//----------------------------------------



// # Raylib includes------------------------
#include "../lib/raylib/raylib.h"
#include "../lib/raylib/raymath.h"
#include "../lib/raylib/rlgl.h"
// -----------------------------------------

// # Generic includes-----------------------
#include <string>
#include <vector> // on heap
#include <array> // more efficient, on stack
#include "smallmath.hpp" // custom static math class to keep it agnostic
// -----------------------------------------

// # Game Definitions----------------------------
/* These are mainly here as an example  *
*  and should eventually be moved to *
*  a more suitable location          */
#define GAME_TITLE "CGame v0.0.2"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
// ---------------------------------------

#ifndef RAYGUI_IMPLEMENTATION
    #define RAYGUI_IMPLEMENTATION       // must come before #include 'raygui.h' 
#endif

using namespace std;

// Screen config ---------------------------
const char screenTitle[] = GAME_TITLE;
const int screenWidth = SCREEN_WIDTH;
const int screenHeight = SCREEN_HEIGHT;
// -----------------------------------------

class Game {
public: 
    Game(); // constructor
    ~Game(); // destructor
    void run(); // game loop
    void start(); // called at start of game
    void update(); // called once a frame
    void draw(); // where everything is drawn
    void close(); // called when game closes
};

#endif // GAME_HPP