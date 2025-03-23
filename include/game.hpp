#pragma once

#ifndef GAME_HPP
#define GAME_HPP

// Raylib includes------------------------
#include "../lib/raylib/raylib.h"
#include "../lib/raylib/raymath.h"
// ---------------------------------------
#include <string>
#include <vector>
/*
#include <stdlib.h>
#include <stdio.h>
*/
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
    void Run(); // game loop
    void Start(); // called at start of game
    void Update(); // called once a frame
    void Draw(); // where everything is drawn
    void Close(); // called when game closes
};

#endif // GAME_HPP