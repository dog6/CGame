#include "../include/game.hpp"

Game::Game(){
    TraceLog(LOG_INFO, "Game started (constructor)");
}

Game::~Game(){
    TraceLog(LOG_INFO, "Game closed (destructor)");
}

/* Game start */
void Game::Start(){

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, screenTitle);
    SetTargetFPS(60);

}


/* Update loop */
void Game::Update(){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){}
    else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){}
}


/* Draw loop */
void Game::Draw(){
    ClearBackground(RAYWHITE);
    DrawFPS(20, 20);
}


/* Game close */
void Game::Close(){
    CloseWindow();        // Close window and OpenGL context
}


/* Game Loop */
void Game::Run(){
    // Initialization
    Game::Start();


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        Game::Update();

        // Draw
        BeginDrawing();
        Game::Draw();
        EndDrawing();
    }

    // De-Initialization
    Game::Close();
}
