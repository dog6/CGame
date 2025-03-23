#include "../../include/shapes/tilemap.hpp"
#include "../../include/shapes/tile.hpp"

Tilemap::Tilemap(Vector2 size, Vector2 tile_size, float tile_gap){
    this->size = size;
    this->tileSize = tile_size;
    this->tileGap = tile_gap;
    setTileData(WHITE);
}

Tilemap::~Tilemap(){ TraceLog(LOG_INFO, "Destructed tilemap"); }

void Tilemap::setTileData(Color color){
    for (int x = 0; x < size.x; x++){
        for (int y = 0; y < size.y; y++){
            int idx = y*size.x+x;
            float tileX = x*(tileSize.x+tileGap);
            float tileY = y*(tileSize.y+tileGap);

            // float tileY = y*(tileSize.y+tileGap);
            this->tileData.push_back(Tile(Vector2{tileX,tileY}, *(new Rect(tileSize, color)))); // init default white colored tile @ position
        }
    }
}

void Tilemap::setTileVisible(Vector2 pos, bool isVisible){
   // not most performant option
   for (int i = 0; i < tileData.size(); i++){
    if (CheckCollisionPointRec(pos, tileData[i].rect.ToRectangle(tileData[i].getPosition()))){
        tileData[i].setVisible(isVisible);
    }
}
}

void Tilemap::setTile(Vector2 pos, Tile tile){
    // not most performant option
    for (int i = 0; i < tileData.size(); i++){
        if (CheckCollisionPointRec(pos, tileData[i].rect.ToRectangle(tileData[i].getPosition()))){
            tileData[i] = tile;
        }
    }
}

void Tilemap::Draw(Vector2 tilemapPos){
    // draw each tile
    for (int i = 0; i < tileData.size(); i++){
        float tileX = tileData[i].getPosition().x*(tileSize.x+tileGap);
        float tileY = tileData[i].getPosition().y*(tileSize.y+tileGap);
        tileData[i].Draw(Vector2{tileX,tileY});
    }
}

void Tilemap::setSize(Vector2 size){ this->size = size; }
Vector2 Tilemap::getSize() { return this->size; }

bool Tilemap::isVisible() { return this->visible; }
void Tilemap::setVisible(bool isVisible){ this->visible = isVisible; };

// Does nothing for tilemap
Color Tilemap::getColor() { return WHITE; };
