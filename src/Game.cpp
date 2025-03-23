#include "../include/game.hpp"
#include "../include/scene.hpp"
#include "../include/entity.hpp"
// #include "../include/shapes/rectangle.hpp"
#include "../include/shapes/tilemap.hpp"
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
Entity tilemap = Entity("first tilemap", Vector2{50,50}, true);
Entity cursorRectangle = Entity("cursor", Vector2{100,100}, true);

/* Game start */
void Game::Start(){

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, screenTitle);
    SetTargetFPS(60);

    // Create entities
    float tileSize = 16;
    Tilemap* map = new Tilemap(Vector2{screenWidth/tileSize,screenHeight/tileSize}, Vector2{tileSize,tileSize}, 1); 
    tilemap.shape = map;
    
    cursorRectangle.shape = new Rect(Vector2{12, 12}, RED); // Rectangle 

    // Add entites to scene
    demoScene.AddEntity(tilemap);    
    demoScene.AddEntity(cursorRectangle);
}


/* Update loop */
void Game::Update(){
    // Update scene
    demoScene.Update(); // physics

    // Update cursor block
    Vector2 mousePos = GetMousePosition();
    Vector2 rectSize = cursorRectangle.shape->getSize(); //cursorRectangle.shape.getSize().y
    cursorRectangle.body->position = Vector2{mousePos.x-(rectSize.x/2),mousePos.y-(rectSize.y/2)};

}

/* Draw loop */
void Game::Draw(){
    ClearBackground(BLACK);
    demoScene.Render();
    DrawFPS(20, 20);
}
