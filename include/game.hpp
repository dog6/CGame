#pragma once

#ifndef GAME_HPP
#define GAME_HPP

// Raylib includes------------------------
#include "../lib/raylib/raylib.h"
#include "../lib/raylib/raymath.h"
// ---------------------------------------
#include <string>
#include <vector>

// Definitions----------------------------
#define MAX_DYNAMIC_ENTITIES_IN_SCENE 100 // dynamic entites (i.e things with physics)
// ---------------------------------------

using namespace std;

// Screen config ---------------------------
const char screenTitle[] = "CGame v0.0.1";
const int screenWidth = 800;
const int screenHeight = 450;
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