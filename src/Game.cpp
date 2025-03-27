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

float tileSize = 6;
float tileGap = 1;
float tilemapSize;// = 24;
/* Game start */
void Game::start(){

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, screenTitle);
    SetTargetFPS(60); // 10 for conway

    // Create tilemap
    tilemapSize = Smallmath::Vector2LargerValue(Vector2{(screenWidth/(tileSize+tileGap)), (screenHeight/(tileSize+tileGap))});
    map = new Tilemap(Vector2Zero(), Vector2{tilemapSize, tilemapSize}, Vector2{tileSize, tileSize}, tileGap);
    map->setTileData(WHITE, false);
    map->hasOutline = true;
    map->outlineColor = WHITE;

    tilemap.shape = map; // give tilemap it's shape
    
    // Or add multiple entities at once instead
    demoScene.addEntities(vector<Entity*>{&tilemap});
    
    // Create camera2D
    cam.target=map->position;//Vector2{-(tilemapSize/2),};
    cam.offset = Vector2{0,0};
    cam.rotation = 0.0f;
    cam.zoom = 0.5f;

}




// Demo------------------------
bool NeighborAlive(Vector2 pos, Vector2 offset){
    bool result = false;
    try {
        result = map->tileData[Smallmath::TilemapToIndex(Vector2{pos.x+offset.x, pos.y+offset.y}, map->getSize().x)].isVisible();
    } catch (exception e){
        TraceLog(LOG_INFO, "Failed to check neighbor", e.what());
    }
    return result;
}

/* returns pixel location as integer value
    0 - center
    1 - top edge 'north'
    2 - top right corner 'north-east'
    3 - right edge 'east'
    4 - bottom right corner 'south-east'
    5 - bottom edge 'south'
    6 - bottom left corner 'south-west'
    7 - left edge 'west'
    8 - top left corner 'north-west'
    parameters `<Vector2>` position, '<Vector2>' tilemap size
*/
int IsEdgePixel(Vector2 pos, Vector2 sz){
    if (pos.x > 0 && pos.y > 0 && pos.x < sz.y && pos.y < sz.x){
        return 0; // center
    }else if (pos.x > 0  && pos.x < sz.x && pos.y == 0) {
        return 1; // top edge 'north'
    }else if (pos.x == sz.x && pos.y == 0){
        return 2; // top right corner 'north-east'
    }else if (pos.x == sz.x && pos.y < sz.y && pos.y > 0){
        return 3; // right edge 'east'
    }else if (pos.x == sz.x && pos.y == sz.y) {
        return 4; // bottom right corner 'south-east'
    }else if (pos.x > 0  && pos.x < sz.x && pos.y == sz.y) {
        return 5; // bottom edge 'south'
    }else if (pos.x == 0 && pos.y == sz.y){
        return 6; // bottom left corner 'south-west'
    }else if (pos.x == 0 && pos.y < sz.y && pos.y > 0){
        return 7; // left edge 'west'
    }else if (pos.x == 0 && pos.y == 0){
        return 8; // top left corner 'north-west'
    }
    return -1;
}

bool NotMovingTowards(Vector2 checkingDir, Vector2 possibleDir) {
    return (checkingDir.x != possibleDir.x || checkingDir.y != possibleDir.y);
}

template<typename... Args>
bool NotMovingTowards(Vector2 checkingDir, Args... possibleDirs) {
    return (... && NotMovingTowards(checkingDir, possibleDirs));
}

int CountNeighbors(Vector2 pos){
    int livingNeighbors = 0;

    std::array<Vector2, 8> offsets{ Vector2{-1, -1}, Vector2{0, -1}, Vector2{1, -1},
                                    Vector2{-1, 0},                  Vector2{1, 0},
                                    Vector2{-1, 1}, Vector2{0, 1},   Vector2{1, 1} };
        
    Vector2 v = Vector2SubtractValue(map->getSize(), 1);                                
    int pixelType = IsEdgePixel(pos, v);            
    for (int i = 0; i < offsets.size(); i++){
        switch(pixelType){
            case 0: // center
                if (NeighborAlive(pos, offsets[i])){
                    livingNeighbors++;
                }
            break; 
            case 1: // north
                if (NotMovingTowards(offsets[i], NORTH, NORTH_EAST, NORTH_WEST) && NeighborAlive(pos, offsets[i])){
                    livingNeighbors++;
                }
            break;
            case 2: // north-east
                if (NotMovingTowards(offsets[i], NORTH, NORTH_EAST, NORTH_WEST, EAST, SOUTH_EAST) && NeighborAlive(pos, offsets[i])){
                    livingNeighbors++;
                }
            break;
            case 3: // east
                if (NotMovingTowards(offsets[i], EAST, NORTH_EAST, SOUTH_EAST) && NeighborAlive(pos, offsets[i])){
                    livingNeighbors++;
                }
            break;
            case 4: // south-east
                if (NotMovingTowards(offsets[i], SOUTH, SOUTH_EAST, SOUTH_WEST, EAST, NORTH_EAST) && NeighborAlive(pos, offsets[i])){
                    livingNeighbors++;
                }
            break;
            case 5: // south
                if (NotMovingTowards(offsets[i], SOUTH, SOUTH_EAST, SOUTH_WEST) && NeighborAlive(pos, offsets[i])){
                    livingNeighbors++;
                }
            break;
            case 6: // south-west
                if (NotMovingTowards(offsets[i], SOUTH_WEST, SOUTH_EAST, SOUTH, WEST, NORTH_WEST) && NeighborAlive(pos, offsets[i])){
                    livingNeighbors++;
                }
            break;
            case 7: // west
                if (NotMovingTowards(offsets[i], WEST, NORTH_WEST, SOUTH_WEST) && NeighborAlive(pos, offsets[i])){
                    livingNeighbors++;
                }
            break;
            case 8: // north-west
                if (NotMovingTowards(offsets[i], NORTH, WEST, NORTH_WEST, NORTH_EAST, SOUTH_WEST) && NeighborAlive(pos, offsets[i])){
                    livingNeighbors++;
                }
            break;
            default:
            break;
        }
    }
    return livingNeighbors;
}

void ConwayGameOfLife(float dt){
    vector<Tile> newTileData = map->tileData; // make copy of tileData
    Vector2 mapSize = map->getSize();

    // look through each tile, find alive neighbors
    for (int i = 0; i < tilemapSize*tilemapSize; i++){

       Vector2 pos = Smallmath::IndexToTilemap(i, mapSize.x);

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


    float timeElapsed = 0;
    float delayInSeconds = 0.25f; // 250ms
    map->tileData = newTileData; // set new tile


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
        ConwayGameOfLife(frame_dt); 
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
