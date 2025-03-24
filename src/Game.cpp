#include "../include/game.hpp"
#include "../include/scene.hpp"
#include "../include/entity.hpp"
// #include "../include/shapes/rectangle.hpp"
#include "../include/shapes/ellipse.hpp"
#include "../include/shapes/tilemap.hpp"

float frame_dt;

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

// Vector2 screenCenter = Vector2{float(GetScreenWidth()/2), float(GetScreenHeight()/2)};
Vector2 screenCenter = Vector2{float(screenWidth/2), float(screenHeight/2)};
Vector2 mousePos;

// Create scene
Scene demoScene = Scene("demoScene");

// Create entities           name, position
Entity tilemap = Entity("first tilemap", Vector2{50,50}, true);
Entity cursorRectangle = Entity("cursor", Vector2{100,100});
Entity ball = Entity("ball", screenCenter); 

/* Game start */
void Game::start(){

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, screenTitle);
    SetTargetFPS(60);

    // Create entities
    
    // Create tilemap
    float tileSize = 50;
    float tileGap = 1;
    Tilemap* map = new Tilemap(Vector2Zero(), Vector2{screenWidth/(tileSize+tileGap),screenHeight/(tileSize+tileGap)}, Vector2{tileSize,tileSize}, tileGap); 
    tilemap.shape = map; // give tilemap it's shape

    
    // Create ellipse
    ball.shape = new Ellipse(12, BLACK); // give ball shape
    ball.body->mass = 0.3; // 0.3 kg
    ball.body->isKinematic = false;
    ball.collideWithCamera = true;
    // ball.shape = new Ellipse(Vector2{36, 12}, BLUE); // give ball shape
    
    // Create rectangle
    cursorRectangle.shape = new Rect(Vector2{12, 12}, RED); // give cursor shape
    
    /*
    * Add entites to scene
    * Drawn first
        demoScene.addEntity(tilemap);    
        demoScene.addEntity(cursorRectangle);
        demoScene.addEntity(ball); 
    * Drawn last
    */

    // Set scene gravity
    // demoScene.setGravity(Vector2{3, 9.81});

    // Or add multiple entities at once instead
    demoScene.addEntities(vector<Entity>{tilemap, ball, cursorRectangle});

}

// bool ball_growing = true;

/* Update loop */
void Game::update(){
    
    // Update scene
    demoScene.update(frame_dt); // physics

    // Update cursor block
    mousePos = GetMousePosition();
    cursorRectangle.body->position = Vector2Subtract(mousePos, cursorRectangle.shape->getSize()/2);


    // Update gravity of ball
    float dist = Vector2Distance(ball.body->position, mousePos);
    Vector2 dir = Vector2{ball.body->position.x-mousePos.x, ball.body->position.y-mousePos.y};
    Vector2 mouseForce = Vector2{-dir.x, -dir.y};
    if(dist > 30){
        demoScene.setGravity(mouseForce);
    }

}

/* Draw loop */
void Game::draw(){
    ClearBackground(BLACK); // Bottom drawing
    demoScene.render();
    DrawLine(ball.body->position.x, ball.body->position.y, GetMousePosition().x, GetMousePosition().y, GREEN);
    DrawFPS(20, 20);    // Top drawing
}
