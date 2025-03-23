#include "../include/game.hpp"
#include "../include/scene.hpp"
#include "../include/entity.hpp"
#include "../include/shapes/rectangle.hpp"

/* Constructor/Destructor */
Game::Game(){
    TraceLog(LOG_INFO, "Game started (constructor)");
}
Game::~Game(){
    TraceLog(LOG_INFO, "Game closed (destructor)");
}

/* Game loop & Exit methods */
void Game::Close(){
    CloseWindow();        // Close window and OpenGL context
}
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
/*---------------------------*/

/* -- Add game code below -- */

// Create scene
Scene demoScene = Scene("demoScene");
Entity e = Entity("red rectangle", Vector2{50,50}, true);

/* Game start */
void Game::Start(){

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, screenTitle);
    SetTargetFPS(60);

    // Create entities
    e.shape = new Rect(Vector2{8, 8}, WHITE);

    // Add entites to scene
    demoScene.AddEntity(e);    
}


/* Update loop */
void Game::Update(){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){}
    else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){}
    // demoScene.Update();
}


/* Draw loop */
void Game::Draw(){
    ClearBackground(BLACK);
    DrawFPS(20, 20);
    demoScene.Render();
}
