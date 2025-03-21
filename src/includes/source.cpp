#include "../headers/game.h"


int main(void)
{

    // Initialization
    const char screenTitle[] = "Wow neat";
    const int screenWidth = 800;
    const int screenHeight = 450;
    const string framerateLabel;
    InitWindow(screenWidth, screenHeight, screenTitle);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        // TODO: Update your variables here
        Game::Update();

        BeginDrawing();
        Game::Draw();
        EndDrawing();

        // Draw
       
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}