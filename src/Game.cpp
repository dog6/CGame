#include "../include/game.hpp"
#include "../include/demos/cgol.hpp"

float frame_dt;
Camera2D cam = { 0 };
ConwayGameOfLife cgol;

/* Constructor/Destructor */
Game::Game(){
    TraceLog(LOG_INFO, "Game started (constructor)");
}
Game::~Game(){
    TraceLog(LOG_INFO, "Game closed (destructor)");
}

/* Game loop & Exit methods */
void Game::close(){
    CloseWindow();        // Close window and OpenGL context
}

void Game::run(){
    // Initialization
    Game::start();


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        frame_dt = GetFrameTime();

        // Update
        Game::update();
        
        // Draw
        BeginDrawing();
            Game::draw();
        EndDrawing();

    }

    // De-Initialization
    Game::close();
}
/*---------------------------*/

/* -- Add game code below -- */

/* Game start */
void Game::start(){
    cgol = ConwayGameOfLife();
    cgol.load(); // load cgol
    cgol.start();

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, screenTitle);
    SetTargetFPS(60); // 10 for conway
}


/* Update loop */
void Game::update(){
    cgol.update();
}

/* Draw loop */
void Game::draw(){
    cgol.render();
}
