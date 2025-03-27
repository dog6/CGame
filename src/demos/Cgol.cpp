#include "../../include/demos/cgol.hpp"
#include "../../lib/raygui/raygui.h"

#define GUI_CGOL_UI_IMPLEMENTATION
#include "../../include/ui/gui_cgol_ui.h"

const char* guiStylePath = "../../assets/ui/styles/style_dark.rgs";
bool changingGeneration = false;
float generationTimer; // tracking delay

GuiCgolUiState coglstate;
/*
typedef struct {
    float genDelay = 0.1f; // delay in seconds between generations
    int tileSize;
    Color tileColor;
} GameState;

GameState gameState;*/

GuiCgolUiState gameState;

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
int ConwayGameOfLife::IsEdgePixel(Vector2 pos, Vector2 sz){
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

bool ConwayGameOfLife::NotMovingTowards(Vector2 checkingDir, Vector2 possibleDir) {
    return (checkingDir.x != possibleDir.x || checkingDir.y != possibleDir.y);
}

template<typename... Args>
bool ConwayGameOfLife::NotMovingTowards(Vector2 checkingDir, Args... possibleDirs) {
    return (... && NotMovingTowards(checkingDir, possibleDirs));
}

int ConwayGameOfLife::CountNeighbors(Vector2 pos, Tilemap* map){
    int livingNeighbors = 0;

    std::array<Vector2, 8> offsets{ Vector2{-1, -1}, Vector2{0, -1}, Vector2{1, -1},
                                    Vector2{-1, 0},                  Vector2{1, 0},
                                    Vector2{-1, 1}, Vector2{0, 1},   Vector2{1, 1} };
        
    // Vector2 v = Vector2SubtractValue(map->getSize(), 1);
    Vector2 v = map->getSize();
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
                TraceLog(LOG_ERROR, "Unidentified pixel location [/CountNeighbors]");
            break;
        }
    }
    return livingNeighbors;
}

void ConwayGameOfLife::handleInput(){
    // Update cursor block
    this->mousePos = GetScreenToWorld2D(GetMousePosition(), this->cam);

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
    if (GetKeyPressed() == KEY_RIGHT){
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
            }
        }
    }

    if (GetKeyPressed() == KEY_H){
        this->showColors = !this->showColors;
    }

    // Reset tilemap
    if (IsKeyPressed(KEY_C)){
        TraceLog(LOG_INFO, "Reset tilemap");
        map->setTileData(WHITE, false);
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
};

ConwayGameOfLife::~ConwayGameOfLife() {
    TraceLog(LOG_INFO, "Closing CGOL..");
};

void ConwayGameOfLife::NextGeneration(){
        vector<Tile> newTileData = map->tileData; // make copy of tileData
    Vector2 mapSize = map->getSize();

    // look through each tile, find alive neighbors
    for (int i = 0; i < tilemapSize*tilemapSize; i++){

       Vector2 pos = Smallmath::IndexToTilemap(i, mapSize.x);

       int livingNeighbors = CountNeighbors(pos, map);

       if (newTileData[i].isVisible()){
            
            // Any live cell with two or three live neighbours lives on to the next generation.
            if (livingNeighbors == 2 || livingNeighbors == 3){
                continue;
            }

            // Any live cell with more than three live neighbours dies, as if by overpopulation.
            if (livingNeighbors > 3){
                newTileData[i].setVisible(false); // kill this tile due to over population
            }

            // Any live cell with fewer than two live neighbours dies, as if by underpopulation.
            if (livingNeighbors < 2){
                newTileData[i].setVisible(false); // kill this tile due to under population
            }

        }else {

            // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
            if (livingNeighbors == 3) {
                newTileData[i].setVisible(true); // repopulate this tile
            }

        }
    }

    float timeElapsed = 0;
    float delayInSeconds = 0.25f; // 250ms
    map->tileData = newTileData; // set new tile
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
    tilemapSize = Smallmath::Vector2LargerValue(Vector2{(screenWidth/(tileSize+tileGap)), (screenHeight/(tileSize+tileGap))});
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

    gameState = InitGuiCgolUi(); // init gui
    // state.gen_delay_txtboxValue = delayBetweenGenerations;
    // state.tile_sz_txtboxValue = this->tileSize;
    // state.gen_delay_txtboxValue = this->delayBetweenGenerations;

    map->setTileData(WHITE, false);
    map->hasOutline = true;
    map->outlineColor = WHITE;
    tilemap->shape = map; // give tilemap it's shape
    
    // Or add multiple entities at once instead
    TraceLog(LOG_INFO, "Added tilemap to scene entities");
    this->scene->addEntities(vector<Entity*>{tilemap});
}

void ConwayGameOfLife::update(){
    handleCameraTranslate();
    handleCameraZoom();
    handleInput();
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

    GuiCgolUi(&gameState);
    map->setColor(gameState.tile_colorPickerValue);
    map->setTileSize(Vector2{(float)gameState.tileSize_txtboxValue, (float)gameState.tileSize_txtboxValue});
    this->delayBetweenGenerations = gameState.genDelay_txtboxValue;

 
    try {
        GuiLoadStyle(guiStylePath);
    }catch (exception e){
        TraceLog(LOG_ERROR, "Failed to find GUI style '%s'", guiStylePath);
        return;
    }
  
    DrawFPS(20, 20);    // Top drawing
    DrawText(string("Generations: " + to_string(generations)).c_str(), 13, screenHeight-26, 24, GREEN);
    DrawText(string("Zoom: " + to_string(Normalize(cam.zoom, 0, 1))).c_str(), 13, screenHeight-48, 24, GREEN);
}

void ConwayGameOfLife::close(){
    delete this; // this will prolly crash game
}