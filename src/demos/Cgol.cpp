#include "../../include/demos/cgol.hpp"
#include "../../lib/raygui/raygui.h"

#define GUI_CGOLMENU_IMPLEMENTATION
#include "../../include/ui/gui_CGOLMenu.h"
GuiCGOLMenuState gameState;


bool changingGeneration = false;
float generationTimer; // tracking delay

bool ConwayGameOfLife::NeighborAlive(Vector2 pos, Vector2 offset){
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
int ConwayGameOfLife::IsEdgePixel(Vector2 pos, Vector2 sz) {
    int x = static_cast<int>(pos.x);
    int y = static_cast<int>(pos.y);
    int maxX = static_cast<int>(sz.x) - 1;
    int maxY = static_cast<int>(sz.y) - 1;

    // Debug print
    // << "Checking pos (" << x << "," << y << ") on grid (" << maxX + 1 << "x" << maxY + 1 << ")\n"
    TraceLog(LOG_INFO, "Checking pos: (", x, ", ", y, ")");

    if (x > 0 && x < maxX && y > 0 && y < maxY) return 0; // center
    if (x > 0 && x < maxX && y == 0) return 1;            // top edge
    if (x == maxX && y == 0) return 2;                    // top right corner
    if (x == maxX && y > 0 && y < maxY) return 3;         // right edge
    if (x == maxX && y == maxY) return 4;                 // bottom right corner
    if (x > 0 && x < maxX && y == maxY) return 5;         // bottom edge
    if (x == 0 && y == maxY) return 6;                    // bottom left corner
    if (x == 0 && y > 0 && y < maxY) return 7;            // left edge
    if (x == 0 && y == 0) return 8;                       // top left corner

    return -1; // invalid or out of bounds
}



bool ConwayGameOfLife::NotMovingTowards(Vector2 checkingDir, Vector2 possibleDir) {
    return (checkingDir.x != possibleDir.x || checkingDir.y != possibleDir.y);
}

template<typename... Args>
bool ConwayGameOfLife::NotMovingTowards(Vector2 checkingDir, Args... possibleDirs) {
    return (... && NotMovingTowards(checkingDir, possibleDirs));
}

const std::array<Vector2, 8> offsets{ Vector2{-1, -1}, Vector2{0, -1}, Vector2{1, -1},
Vector2{-1, 0},                  Vector2{1, 0},
Vector2{-1, 1}, Vector2{0, 1},   Vector2{1, 1} };


int ConwayGameOfLife::CountNeighbors(Vector2 pos, Tilemap* map){
    if (map == nullptr){
        TraceLog(LOG_ERROR, "Unable to count neighbors, map is null");
    }
    
    TraceLog(LOG_INFO, "Counting neighbors @ position ", pos.x, ", ", pos.y);
    int livingNeighbors = 0;
    
    
    int pixelType = IsEdgePixel(pos, map->getSize());
    TraceLog(LOG_INFO, "PixelType: ", pixelType);    
    for (int i = 0; i < offsets.size()-1; i++){
        switch(pixelType){
            case -1:
                TraceLog(LOG_ERROR, "[/IsEdgePixel] Unidentified pixel location");
            break;
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
                TraceLog(LOG_ERROR, "Failed to count neighbors");
            break;
        }
    }
    TraceLog(LOG_INFO, "Counted ", livingNeighbors, " neighbors");
    return livingNeighbors;
}

void ConwayGameOfLife::handleInput(){
    // Update cursor block
    this->mousePos = GetScreenToWorld2D(GetMousePosition(), this->cam);


    if (IsKeyPressed(KEY_M) || IsKeyPressed(KEY_GRAVE)) {
        TraceLog(LOG_INFO, "Toggling state of CGOL Menu");
        if (gameState.cgolWindowActive){
            gameState.cgolWindowActive = false;
            TraceLog(LOG_INFO, "CGOL Menu closed.");
        }else {
            gameState.cgolWindowActive = true;
       
            gameState = InitGuiCGOLMenu();
            gameState.tileGapValue = map->tileGap;
            gameState.tileSizeValue = map->getTileSize().x;
            gameState.mapSizeValue = map->getSize().x;
            gameState.tileColorPickerValue = map->getColor();


            TraceLog(LOG_INFO, "CGOL Menu opened.");
        }
    }


    // Left click to place tile, right click to delete
    Tile* hoveredTile = this->map->getTile(mousePos);
    if (hoveredTile != nullptr){
        // Change tile color
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 pos = hoveredTile->getPosition();
            hoveredTile->setVisible(true);
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
            hoveredTile->setVisible(false);
        }
    }

    // Press to increase one generation
    if (IsKeyPressed(KEY_RIGHT)){
        generations++;
        this->NextGeneration();
    }
    // or Hold to increase generation
    if (IsKeyDown(KEY_SPACE)){
        
        if (canLoadNextGeneration){
            canLoadNextGeneration = false;
            generations++;
            this->NextGeneration();
        }else {
            // increment timer
            this->genTime += GetFrameTime();
            if (this->genTime >= this->delayBetweenGenerations){
                canLoadNextGeneration = true;
                genTime = 0;
            }
        }
    }

    if (IsKeyPressed(KEY_H)){
        this->showColors = !this->showColors;
    }

    // Reset tilemap
    if (IsKeyPressed(KEY_C)){
        TraceLog(LOG_INFO, "Reset tilemap");
        map->setTileData(WHITE, map->getSize(), false);
    }

}

void ConwayGameOfLife::handleCameraZoom(){
    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        cam.offset = GetMousePosition();
        cam.target = mousePos;

        float scale = 0.2f*wheel;
        cam.zoom = Clamp(expf(logf(cam.zoom)+scale), 0.25f, 5.0f);
    } 
}

void ConwayGameOfLife::handleCameraTranslate(){
    // Translate based on mouse right click
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
    {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/cam.zoom);
        cam.target = Vector2Add(cam.target, delta);
    }
}

ConwayGameOfLife::ConwayGameOfLife(){
    TraceLog(LOG_INFO, "Initialized CGOL");
    this->scene = new Scene("CGOL");
    // this->gameState = InitGuiCGOLMenu();
};

ConwayGameOfLife::~ConwayGameOfLife() {
    TraceLog(LOG_INFO, "Closing CGOL..");
};

void ConwayGameOfLife::NextGeneration(){
    TraceLog(LOG_INFO, "Running generation ", generations);
    std::vector<Tile> newTileData = map->tileData; // make copy of tileData
    // look through each tile, find alive neighbors
    for (int i = Smallmath::Vector2Product(map->getSize()); i > 0; i--) {
        Vector2 pos = Smallmath::IndexToTilemap(i, map->getSize().x);
        int livingNeighbors = CountNeighbors(pos, map);
        if (newTileData[i].isVisible()){
            // Any live cell with two or three live neighbours lives on to the next generation.
            if (livingNeighbors != 2 && livingNeighbors != 3){
                newTileData[i].setVisible(false); // kill this tile due to under population
                continue;
            }

            if (livingNeighbors <= 1){
                newTileData[i].setVisible(false); // under pop
            }

            if (livingNeighbors >= 4){
                newTileData[i].setVisible(false); // over pop
            }

        }else {
            // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
            if (livingNeighbors == 3) {
                newTileData[i].setVisible(true); // repopulate this tile
                continue;
            }else {
                newTileData[i].setVisible(false); // repopulate this tile
            }
        }
    }


    float timeElapsed = 0;
    float delayInSeconds = 0.25f; // 250ms
    map->tileData = newTileData; // set new tile
}

void ConwayGameOfLife::handleMenu(){
   
    if (!gameState.cgolWindowActive){
        return; // return if window inactive
    }

    map->setAllTilesColor(gameState.tileColorPickerValue);

    if (gameState.applyButtonPressed){
        // Update map with new settings
        TraceLog(LOG_INFO, "COGL Menu Settings applied");
        map->updateTilemap( Vector2{(float)gameState.mapSizeValue,(float)gameState.mapSizeValue},
                            Vector2{(float)gameState.tileSizeValue,(float)gameState.tileSizeValue},
                            gameState.tileGapValue,
                            gameState.tileColorPickerValue
        );
        tilemapSize = gameState.mapSizeValue;
    }

    if (gameState.clearGridButtonPressed){
        map->setTileData(WHITE, map->getSize(), false);
    }



}

/* ILevel methods */
const char* ConwayGameOfLife::getLevelName(){
    return this->name;
}

void ConwayGameOfLife::load(){
    TraceLog(LOG_INFO, "Loading CGOL..");

    TraceLog(LOG_INFO, "Creating tilemap entity for CGOL..");
    // Create entities
    tilemap = new Entity("first tilemap", Vector2{50,50}, true);
    // tilemapSize = Smallmath::Vector2LargerValue(Vector2{(screenWidth/(tileSize+tileGap)), (screenHeight/(tileSize+tileGap))});
    tilemapSize = 128;
    map = new Tilemap(Vector2Zero(), Vector2{tilemapSize, tilemapSize}, Vector2{tileSize, tileSize}, tileGap);
    tilemap->shape = map; // give tilemap its shape
    tilemap->isEnabled = true;
    TraceLog(LOG_INFO, "Tilemap created.");

    // Create camera2D
    cam.target=map->position;
    cam.offset = Vector2{0,0};
    cam.rotation = 0.0f;
    cam.zoom = 0.5f;
    TraceLog(LOG_INFO, "Camera created.");   



}

void ConwayGameOfLife::start(){
    TraceLog(LOG_INFO, "Starting CGOL..");
    
    /*try {
        GuiLoadStyle(guiStylePath);
    }catch (exception e){
        TraceLog(LOG_ERROR, "Failed to load gui style.\n", e.what());
    }*/

    // set default menu settings
    gameState.mapSizeValue = map->getSize().x;
    gameState.tileSizeValue = this->tileSize;
    gameState.tileColorPickerValue = WHITE;
    gameState.tileGapValue = this->tileGap;

    // Create tilemap
    /*map->setTileData(WHITE, map->getSize(), false);
    map->hasOutline = true;
    map->outlineColor = WHITE;
    map->defaultVisible = false; // when map is refreshed, tiles should not be visible
    tilemap->shape = map; // give tilemap it's shape*/
    map->setTileData(WHITE, map->getSize(), false);
    map->hasOutline = true;
    map->outlineColor = WHITE;
    map->defaultVisible = false;
    tilemap->shape = map; 
    
    // Add entities to scene
    TraceLog(LOG_INFO, "Added tilemap to scene entities");
    this->scene->addEntities(vector<Entity*>{tilemap});
}

void ConwayGameOfLife::update(){
    handleCameraTranslate();
    handleCameraZoom();
    handleInput();
    handleMenu();
}

bool showMessageBox = false;
void ConwayGameOfLife::render(){

    rlPushMatrix();
        rlTranslatef(0, 25*50, 0);
        rlRotatef(90, 1, 0, 0);
    rlPopMatrix();

    ClearBackground(BLACK); // Bottom drawing

    // Draw 2D entities
    BeginMode2D(this->cam);
    this->scene->render();
    EndMode2D();

    // GuiCgolUi(&gameState);
    // map->setColor(gameState.tile_colorPickerValue);
    // map->setTileSize(Vector2{(float)gameState.tileSize_txtboxValue, (float)gameState.tileSize_txtboxValue});
    // this->delayBetweenGenerations = gameState.genDelay_txtboxValue;

    GuiCGOLMenu(&gameState); // sync game state w/ menu
  
    DrawFPS(20, 20);    // Top drawing
    DrawText(string("Generations: " + to_string(generations)).c_str(), 13, screenHeight-26, 24, GREEN);
    DrawText(string("Zoom: " + to_string(Normalize(cam.zoom, 0, 1))).c_str(), 13, screenHeight-48, 24, GREEN);
}

void ConwayGameOfLife::close(){
    delete this; // this will prolly crash game
}