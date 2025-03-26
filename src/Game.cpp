#include "../include/game.hpp"
#include "../include/scene.hpp"
#include "../include/entity.hpp"
#include "../include/shapes/rectangle.hpp"
#include "../include/shapes/ellipse.hpp"
#include "../include/shapes/tilemap.hpp"
#include "../include/shapes/ngon.hpp"


float frame_dt;
Camera2D cam = { 0 };

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

float tileSize = 12;
float tileGap = 1;
float tilemapSize;
/* Game start */
void Game::start(){

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, screenTitle);
    SetTargetFPS(60); // 10 for conway

    // Create tilemap
    tilemapSize = Smallmath::Vector2LargerValue(Vector2{(screenWidth/(tileSize))+1, (screenHeight/(tileSize))+1});
    map = new Tilemap(Vector2Zero(), Vector2{tilemapSize, tilemapSize}, Vector2{tileSize, tileSize}, tileGap);
    map->setTileData(WHITE, false);
    // map->setAllTilesColor(WHITE);   // all tiles are white by default
    // map->setAllTilesVisible(false); // all tiles not visible by default
    tilemap.shape = map; // give tilemap it's shape

    // Set scene gravity
    // demoScene.setGravity(Vector2{0, 9.81});

    // Or add multiple entities at once instead
    demoScene.addEntities(vector<Entity*>{&tilemap});
    
    // Set scene gravity
    demoScene.setGravity(Vector2{0, 9.81f});

    // Create camera2D
    cam.target = Vector2{0,0};
    cam.offset = Vector2{0,0};
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;

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
            else if (pos.x == 0 && pos.y < map->getSize().y-1 && pos.y > 0 && offsets[i] != Vector2{-1,0} && offsets[i] != Vector2{-1, 1 }&& offsets[i] != Vector2{-1, -1}){
                // on left edge
                if (NeighborAlive(pos, offsets[i])){
                    livingNeighbors++;
                }
            }else if (pos.x < map->getSize().x-1 && pos.y < map->getSize().y-1 && pos.y > 0 && offsets[i] != Vector2{1,0} && offsets[i] != Vector2{1,1} && offsets[i] != Vector2{1,-1}){
                // on right edge
                if (NeighborAlive(pos, offsets[i])){
                    livingNeighbors++;
                }
            }else if (pos.x > 0  && pos.x < map->getSize().x-1 && pos.y == 0 && offsets[i] != Vector2{0,-1} && offsets[i] != Vector2{-1,-1} && offsets[i] != Vector2{1,-1}){
                // on top edge
                if (NeighborAlive(pos, offsets[i])){
                    livingNeighbors++;
                }
            }else if (pos.x > 0  && pos.x < map->getSize().x-1 && pos.y == map->getSize().y-1 && offsets[i] != Vector2{0,1} && offsets[i] != Vector2{1, 1} && offsets[i] != Vector2{-1, 1}){
                // on bottom edge
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

void handleCameraZoom(){
    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        cam.offset = GetMousePosition();
        cam.target = mousePos;

        float scale = 0.2f*wheel;
        cam.zoom = Clamp(expf(logf(cam.zoom)+scale), 0.25f, 5.0f);
    } 
}

void handleCameraTranslate(){
    // Translate based on mouse right click
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
    {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/cam.zoom);
        cam.target = Vector2Add(cam.target, delta);
    }
}

void demoCode(){

    // Update cursor block
    mousePos = GetScreenToWorld2D(GetMousePosition(), cam);


    // Left click to place tile, right click to delete
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

    // Hold to increase generation
    if (IsKeyDown(KEY_SPACE)){
        generations++;
        ConwayGameOfLife(); 
    }

    // Reset tilemap
    if (IsKeyPressed(KEY_C)){
        TraceLog(LOG_INFO, "Reset tilemap");
        map->setTileData(WHITE, false);
    }


    handleCameraTranslate();
    handleCameraZoom();
  
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

    rlPushMatrix();
        rlTranslatef(0, 25*50, 0);
        rlRotatef(90, 1, 0, 0);
    rlPopMatrix();

    ClearBackground(BLACK); // Bottom drawing

    // Draw 2D entities
    BeginMode2D(cam);
    demoScene.render();
    EndMode2D();

    DrawFPS(20, 20);    // Top drawing
    DrawText(string("Generations: " + to_string(generations)).c_str(), 13, screenHeight-26, 24, GREEN);
    DrawText(string("Zoom: " + to_string(Normalize(cam.zoom, 0, 1))).c_str(), 13, screenHeight-48, 24, GREEN);
}
