#include "../include/game.hpp"
#include "../include/scene.hpp"
#include "../include/entity.hpp"
#include "../include/shapes/rectangle.hpp"
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

Vector2 screenCenter = Vector2{float(screenWidth/2), float(screenHeight/2)};
Vector2 mousePos;

// Create scene
Scene demoScene = Scene("demoScene");

// Initialize tilemap pointer
Tilemap* map;

// Create entities           name, position
Entity tilemap = Entity("first tilemap", Vector2{50,50}, true);
Entity cursorRectangle = Entity("cursor", Vector2{100,100});
Entity rect = Entity("rect", Vector2{200, 45}, 0);

Entity ball = Entity("ball", screenCenter);
// Entity box = Entity("box", Vector2{300, 225});
/* Game start */
void Game::start(){

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, screenTitle);
    SetTargetFPS(60);

    // Create entities
    
    // Create tilemap
    float tileSize = 10;
    float tileGap = 1;
    map = new Tilemap(Vector2Zero(), Vector2{screenWidth/(tileSize+tileGap),screenHeight/(tileSize+tileGap)}, Vector2{tileSize,tileSize}, tileGap); 
    
    tilemap.shape = map; // give tilemap it's shape

    // Create rectangle
    rect.shape = new Rect(Vector2{50,50}, BLUE);
    rect.body->mass = 1;
    rect.body->isKinematic = false;
    rect.collideWithCamera = true;

    // Create ellipse
    ball.shape = new Ellipse(16, RED); // give ball shape
    ball.body->mass = 0.3; // 0.3 kg
    ball.body->isKinematic = false;
    ball.collideWithCamera = true;
    
    // Create cursor rectangle
    cursorRectangle.shape = new Rect(Vector2{12, 12}, RED); // give cursor shape

    // Create box (WIP)
    /*box.body->mass = 1; // 1 kg
    box.body->force = Vector2{1, 1};
    box.body->isKinematic = false;
    box.collideWithCamera = true;*/

    // Set scene gravity
    // demoScene.setGravity(Vector2{0, 9.81});

    // Or add multiple entities at once instead
    demoScene.addEntities(vector<Entity>{tilemap, ball, cursorRectangle, rect /*box <-- issue with box :/ */});
    
    // Set scene gravity
    demoScene.setGravity(Vector2{0, 9.81f});

}

// Demo------------------------
bool ballTiedToCursor = false;
void demoCode(){

    // Update cursor block
    mousePos = GetMousePosition();
    cursorRectangle.body->position = Vector2Subtract(mousePos, Smallmath::Vector2DivideValue(cursorRectangle.shape->getSize(), 2));

    // 'Tie' ball to cursor ( kinda bad, just for demo )
    if (ballTiedToCursor) {
        float dist = Vector2Distance(ball.body->position, mousePos);                                // get distance from ball to cursor
        Vector2 dir = Vector2Normalize(Vector2{ball.body->position.x-mousePos.x, ball.body->position.y-mousePos.y});  // getting direction from ball to cursor
        Vector2 mouseForce = Vector2{dir.x*(demoScene.getGravity().x-3), -dir.y*(demoScene.getGravity().y+3)};                                         // getting 'mouseForce' (direction*0.5f)
        if(dist > 30){
            ball.body->force = mouseForce;
        }
    }

    // Toggle ballTiedToCursor boolean
    if (GetKeyPressed() == KeyboardKey::KEY_SPACE){
        ballTiedToCursor = !ballTiedToCursor;
    }
    
    // Change tile color
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        // TraceLog(LOG_INFO, string("Clicked tile @ mouse position " + to_string(mousePos.x) + ", " + to_string(mousePos.y)).c_str());
        Tile* hoveredTile = map->getTile(mousePos);
        if (hoveredTile != nullptr){
            hoveredTile->rect->setColor(RED);
        }
    }

}
// ----------------------------

/* Update loop */
void Game::update(){
    
    // Update scene
    demoScene.update(frame_dt); // physics
    demoCode(); // for demo

}

/* Draw loop */
void Game::draw(){
    ClearBackground(BLACK); // Bottom drawing
    demoScene.render();
    if (ballTiedToCursor) { DrawLine(ball.body->position.x, ball.body->position.y, GetMousePosition().x, GetMousePosition().y, GREEN); }
    DrawFPS(20, 20);    // Top drawing
}
