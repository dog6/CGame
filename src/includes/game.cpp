#include "../headers/game.h"



string framerate_label = "";

void Game::Update(){
    framerate_label = "FPS: " + std::to_string(GetFPS());
}

void Game::Draw(){

    ClearBackground(RAYWHITE);
    
    DrawText(framerate_label.c_str(), 10, 24, 24, GRAY);

}