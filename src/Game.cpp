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

int generations = 0;

/* Game start */
void Game::start(){

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, screenTitle);
    SetTargetFPS(60); // 10 for conway

    // Create tilemap
    float tileSize = 12;
    float tileGap = 0;
    // map = new Tilemap(Vector2Zero(), Vector2{screenWidth/(tileSize),screenHeight/(tileSize)}, Vector2{tileSize,tileSize}, tileGap); 
    // map = new Tilemap(Vector2Zero(), Vector2{screenWidth, screenHeight}, Vector2{tileSize, tileSize}, tileGap);
    // map = new Tilemap(Vector2Zero(), Vector2{30,30}, Vector2{tileSize,tileSize}, tileGap); 
    map = new Tilemap(Vector2Zero(), Vector2{50, 50}, Vector2{tileSize, tileSize}, tileGap);
    
    map->setTileData(WHITE, false);
    tilemap.shape = map; // give tilemap it's shape

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
    int livingNeighbors = 0;
    // Count neighbors
    vector<Vector2> offsets = vector<Vector2>{Vector2{-1, -1}, Vector2{0, -1}, Vector2{1, -1},
                                              Vector2{-1, 0},                 Vector2{1, 0},
                                              Vector2{-1, 1}, Vector2{0, 1}, Vector2{1, 1}};

        for (int i = 0; i < offsets.size(); i++){
            if (pos.x > 0 && pos.y > 0 && pos.x < map->getSize().x-1 && pos.y < map->getSize().y-1){
                if (NeighborAlive(pos, offsets[i])){
                    livingNeighbors++;
                }
            }
        }
    return livingNeighbors;
}

void ConwayGameOfLife(){

    vector<Tile> newTileData = map->tileData;

    // look through each tile, find alive neighbors
    for (int i = 0; i < newTileData.size(); i++){

       Vector2 pos = Smallmath::IndexToTilemap(i, map->getSize().x);

       if (pos.x == 0 || pos.y == 0){
        continue;
       }

       int livingNeighbors = CountNeighbors(pos);

       if (newTileData[i].isVisible()){
            // this tile is 'alive'
            if (livingNeighbors > 3){
                newTileData[i].setVisible(false); // kill this tile due to over population
            }else if (livingNeighbors < 2){
                newTileData[i].setVisible(false); // kill this tile due to under population
            }
        }else {
            // this tile is 'dead'
            if (livingNeighbors == 3) {
                newTileData[i].setVisible(true); // repopulate this tile
            }
        }
    }

    map->tileData = newTileData;
    WaitTime(0.1);
}

void demoCode(){

    // Update cursor block
    mousePos = GetMousePosition();

    Tile* hoveredTile = map->getTile(mousePos);
    if (hoveredTile != nullptr){
        // Change tile color
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            hoveredTile->setVisible(true);
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
            hoveredTile->setVisible(false);
        }
    }

    if (IsKeyDown(KEY_SPACE)){
        generations++;
        ConwayGameOfLife(); 
    }
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
    ClearBackground(BLACK); // Bottom drawing
    demoScene.render();
    DrawText(string("Generations: " + to_string(generations)).c_str(), 13, screenHeight-26, 24, GREEN);
    DrawFPS(20, 20);    // Top drawing
}
