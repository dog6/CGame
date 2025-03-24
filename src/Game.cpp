#include "../include/game.hpp"
#include "../include/scene.hpp"
#include "../include/entity.hpp"
// #include "../include/shapes/rectangle.hpp"
#include "../include/shapes/ellipse.hpp"
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

// Vector2 screenCenter = Vector2{float(GetScreenWidth()/2), float(GetScreenHeight()/2)};
Vector2 screenCenter = Vector2{float(screenWidth/2), float(screenHeight/2)};

// Create scene
Scene demoScene = Scene("demoScene");

// Create entities      name, position
Entity tilemap = Entity("first tilemap", Vector2{50,50}, true);
Entity cursorRectangle = Entity("cursor", Vector2{100,100});
Entity ball = Entity("ball", screenCenter); 

/* Game start */
void Game::Start(){

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, screenTitle);
    SetTargetFPS(60);

    // Create entities
    float tileSize = 50;
    float tileGap = 1;
    Tilemap* map = new Tilemap(Vector2Zero(), Vector2{screenWidth/(tileSize+tileGap),screenHeight/(tileSize+tileGap)}, Vector2{tileSize,tileSize}, tileGap); 

    tilemap.shape = map; // give tilemap it's shape
    cursorRectangle.shape = new Rect(Vector2{12, 12}, RED); // give cursor shape
    ball.shape = new Ellipse(12, BLUE); // give ball shape
    
    /*
    * Add entites to scene
    * Drawn first
        demoScene.AddEntity(tilemap);    
        demoScene.AddEntity(cursorRectangle);
        demoScene.AddEntity(ball); 
    * Drawn last
    */

    // Or add multiple entities at once instead
    demoScene.AddEntities(vector<Entity>{tilemap, cursorRectangle, ball});

}


/* Update loop */
void Game::Update(){
    
    // Update scene
    demoScene.Update(); // physics

    // Update cursor block
    Vector2 mousePos = GetMousePosition();
    Vector2 sz = cursorRectangle.shape->getSize(); 
    cursorRectangle.body->position = Vector2{mousePos.x-(sz.x/2),mousePos.y-(sz.y/2)};

}

/* Draw loop */
void Game::Draw(){
    ClearBackground(BLACK); // Bottom drawing
    demoScene.Render();
    DrawFPS(20, 20);    // Top drawing
}
