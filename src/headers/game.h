#pragma once
#include "../external/raylib/raylib.h"
#include <string>

using namespace std;

class Game {
    
private:
    // Prevent instantiation
    Game() = delete;

public: 
    static void Update();
    static void Draw();
};