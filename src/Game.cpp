#include "../include/game.hpp"
#include "../include/scene.hpp"
#include "../include/entity.hpp"
#include "../include/shapes/rectangle.hpp"
#include "../include/shapes/ellipse.hpp"
#include "../include/shapes/tilemap.hpp"
#include "../include/shapes/ngon.hpp"


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

// Create entities
Entity tilemap = Entity("first tilemap", Vector2{50,50}, true);

bool isSimRunning = false;

/* Game start */
void Game::start(){

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, screenTitle);
    SetTargetFPS(60);

    // Create tilemap
    float tileSize = 10;
    float tileGap = 0;
    map = new Tilemap(Vector2Zero(), Vector2{screenWidth/(tileSize+tileGap),screenHeight/(tileSize+tileGap)}, Vector2{tileSize,tileSize}, tileGap); 
    tilemap.shape = map; // give tilemap it's shape
    tilemap.shape->setColor(BLACK);

    // Set scene gravity
    // demoScene.setGravity(Vector2{0, 9.81});

    // Or add multiple entities at once instead
    demoScene.addEntities(vector<Entity*>{&tilemap});
    
    // Set scene gravity
    demoScene.setGravity(Vector2{0, 9.81f});

}




// Demo------------------------

bool NeighborAlive(Vector2 pos, Vector2 offset){
    return map->tileData[Smallmath::TilemapToIndex(Vector2{pos.x+offset.x, pos.y+offset.y}, map->getSize().x)].isVisible();
}

int CountNeighbors(Vector2 pos){
 // Get X & Y
 int livingNeighbors = 0;
 // Count neighbors
     // top left corner
     if (pos.x > 0 && pos.y > 0 && NeighborAlive(pos, Vector2Add(VECTOR2_UP, VECTOR2_LEFT))){
        livingNeighbors++;
     }

     // top
     if (pos.y > 0 && NeighborAlive(pos, VECTOR2_UP)){
        livingNeighbors++;
     }

     // top right
     if (pos.x < map->getSize().x && pos.y > 0 && NeighborAlive(pos, Vector2Add(VECTOR2_UP, VECTOR2_RIGHT))){
        livingNeighbors++;
     }

     // right neighbor
     if (pos.x < map->getSize().x && NeighborAlive(pos, VECTOR2_RIGHT)){
        livingNeighbors++;
     }

     // left neighbor
     if (pos.x > 0 && NeighborAlive(pos, VECTOR2_LEFT)){
        livingNeighbors++;
     }

     // bottom neighbor
     if (pos.y < map->getSize().y && NeighborAlive(pos, VECTOR2_DOWN)){
        livingNeighbors++;
     }

     // bottom right neighbor
     if (pos.y < map->getSize().y && pos.x < map->getSize().x && NeighborAlive(pos, Vector2Add(VECTOR2_DOWN, VECTOR2_RIGHT))){
        livingNeighbors++;
     }

     // bottom left
     if (pos.y < map->getSize().y && pos.x > 0 && NeighborAlive(pos, Vector2Add(VECTOR2_DOWN, VECTOR2_LEFT))){
        livingNeighbors++;
     }
    return livingNeighbors;
}

void ConwayGameOfLife(){
    if (!isSimRunning){
        return;
    }
    // look through each tile, find alive neighbors
    for (int i = 0; i < map->tileData.size(); i++){
       Vector2 pos = Smallmath::IndexToTilemap(i, map->getSize().x);
       int livingNeighbors = CountNeighbors(pos);

       if (map->tileData[i].isVisible()){
            // this tile is 'alive'
            if (livingNeighbors == 2 || livingNeighbors == 3){
                map->tileData[i].setVisible(false); // kill this tile due to over population
                continue;
            }

            if (livingNeighbors < 2){
                map->tileData[i].setVisible(false); // kill this tile due to under population
                continue;
            }


        }else {
            // this tile is 'dead'
            if (livingNeighbors == 3) {
                map->tileData[i].setVisible(true); // repopulate this tile
                continue;
            }
        }
        // anyone with exactly 2 or 3 neighbors lives
    }
    WaitTime(0.25);
}

void demoCode(){

    // Update cursor block
    mousePos = GetMousePosition();

    Tile* hoveredTile = map->getTile(mousePos);
    if (hoveredTile != nullptr){
        // Change tile color
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            hoveredTile->setVisible(false);
        }
    }

    if (GetKeyPressed() == KEY_SPACE){
        // toggle sim running
        isSimRunning = !isSimRunning;
    }

    ConwayGameOfLife(); 

}
// ----------------------------

/* Update loop */
void Game::update(){
    
    // Update scene
    // demoScene.update(frame_dt); // physics
    demoCode(); // for demo
}

/* Draw loop */
void Game::draw(){
    ClearBackground(WHITE); // Bottom drawing
    demoScene.render();
    DrawText(string("Sim Running?: " + to_string(isSimRunning)).c_str(), 13, screenHeight-26, 24, DARKGREEN);
    DrawFPS(20, 20);    // Top drawing
}
