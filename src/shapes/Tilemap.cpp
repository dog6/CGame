#include "../../include/shapes/tilemap.hpp"
#include "../../include/shapes/tile.hpp"

Tilemap::Tilemap(Vector2 position, Vector2 size, Vector2 tile_size, float tile_gap, bool visible){
    this->position = position;
    this->size = size;
    this->tileSize = tile_size;
    this->tileGap = tile_gap;
    this->visible = visible;
    setTileData(WHITE);
}

Tilemap::~Tilemap(){ TraceLog(LOG_INFO, "Destructed tilemap"); }

void Tilemap::setTileData(Color color){
    this->tileData = vector<Tile>{}; // reset tileData
    for (int x = 0; x < size.x; x++){
        for (int y = 0; y < size.y; y++){
            int idx = y*size.x+x;
            float tileX = this->position.x+x*(tileSize.x+tileGap);//+(tileSize.x/2);
            float tileY = this->position.y+y*(tileSize.y+tileGap);//+(tileSize.y/2);
            this->tileData.push_back(Tile(Vector2{tileX,tileY}, *(new Rect(tileSize, color)))); // init default white colored tile @ position
        }
    }
}

void Tilemap::setTileVisible(Vector2 pos, bool isVisible){
   // not most performant option
   for (int i = 0; i < tileData.size(); i++){
    if (CheckCollisionPointRec(pos, tileData[i].rect.toRectangle(tileData[i].getPosition()))){
        tileData[i].setVisible(isVisible);
    }
}
}

void Tilemap::setTile(Vector2 pos, Tile tile){
    // not most performant option
    for (int i = 0; i < tileData.size(); i++){
        if (CheckCollisionPointRec(pos, tileData[i].rect.toRectangle(tileData[i].getPosition()))){
            tileData[i] = tile;
        }
    }
}

void Tilemap::draw(Vector2 tilemapPos){
    if (this->visible){ // if whole tilemap is visible
        for (int i = 0; i < tileData.size(); i++){
            if (tileData[i].isVisible()){ // if individual tile is visible
                tileData[i].draw(tilemapPos); // draw each tile
            }
        }
    }
}

void Tilemap::setSize(Vector2 size){ this->size = size; }
Vector2 Tilemap::getSize() { return this->size; }

bool Tilemap::isVisible() { return this->visible; }
void Tilemap::setVisible(bool isVisible){ this->visible = isVisible; };
vector<Vector2> Tilemap::getVertices(Vector2 pos){
    vector<Vector2> result;
    // TL,TR,BR,BL, so they're inserted backwards
    Vector2 sz = this->getSize();
    result.push_back(Vector2{pos.x-(sz.x/2), pos.y+(sz.x/2)}); // BL 
    result.push_back(Vector2{pos.x+(sz.x/2), pos.y+(sz.x/2)}); // BR
    result.push_back(Vector2{pos.x+(sz.x/2), pos.y-(sz.x/2)}); // TR
    result.push_back(Vector2{pos.x-(sz.x/2), pos.y-(sz.x/2)}); // TL 
    return result;
  }
// Does nothing for tilemap
Color Tilemap::getColor() { return WHITE; };
