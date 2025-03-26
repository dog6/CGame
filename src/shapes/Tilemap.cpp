#include "../../include/shapes/tilemap.hpp"
#include "../../include/shapes/tile.hpp"

Tilemap::Tilemap(Vector2 position, Vector2 size, Vector2 tile_size, float tile_gap, bool visible){
    this->position = position;
    this->size = size;
    this->tileSize = tile_size;
    this->tileGap = tile_gap;
    this->visible = visible;
    setTileSize(tile_size);
}

Tilemap::~Tilemap(){ TraceLog(LOG_INFO, "Destructed tilemap"); }

void Tilemap::setTileVisible(Vector2 pos, bool isVisible){
   // not most performant option
   for (int i = 0; i < tileData.size(); i++){
      // Check distance from tile to point
      if (Vector2Distance(tileData[i].getPosition(), pos) > 10){
        continue;
    }

    if (CheckCollisionPointRec(pos, tileData[i].rect->toRectangle(tileData[i].getPosition()))){
        tileData[i].setVisible(isVisible);
    }
}
}



Vector2 Tilemap::getTileSize(){
    // resize all tiles
    return this->tileData[0].getSize();
}


void Tilemap::setTile(Vector2 pos, Tile tile){
    // not most performant option
    for (int i = 0; i < tileData.size(); i++){
          // Check distance from tile to point
          Vector2 tPos = tileData[i].getPosition();
          if (Vector2Distance(Vector2{tPos.x-(this->size.x/2), tPos.y-(this->size.y/2)}, pos) > 10){
            continue;
        }

        if (CheckCollisionPointRec(pos, tileData[i].rect->toRectangle(tileData[i].getPosition()))){
            tileData[i] = tile;
        }
    }
}

Tile* Tilemap::getTile(Vector2 pos){
    for (int i = 0; i < tileData.size(); i++){
        // Check distance from tile to point
        if (Vector2Distance(tileData[i].getPosition(), pos) > Smallmath::sizeToRadius(this->tileSize)){
            continue;
        }

        if (CheckCollisionPointRec(pos, tileData[i].rect->toRectangle(tileData[i].getPosition()))){
            return &tileData[i];
        }
    }
    return nullptr;
}

void Tilemap::draw(Vector2 tilemapPos, float rot){
    if (this->visible){ // if whole tilemap is visible
        for (int i = 0; i < tileData.size(); i++){
            if (tileData[i].isVisible()){ // if individual tile is visible
                tileData[i].draw(tilemapPos, rot); // draw each tile
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
void Tilemap::setColor(Color color) { setAllTilesColor(color); };


vector<Line> Tilemap::getLines(Vector2 pos){
    vector<Line> result;
    vector<Vector2> points = this->getVertices(pos);
    // for each point, make a line
    for (int i = 0; i <= points.size(); i += 2){
        result.push_back(*(new Line(points[i], points[i+1], RED)));
    }
    return result;
}

void Tilemap::setTileData(Color color, bool visible){
    this->tileData = vector<Tile>{}; // reset tileData
    for (int x = 0; x < size.x; x++){
        for (int y = 0; y < size.y; y++){
            int idx = y*size.x+x;
            float tileX = this->position.x+x*(tileSize.x+tileGap);
            float tileY = this->position.y+y*(tileSize.y+tileGap);
            this->tileData.push_back(Tile(Vector2{tileX,tileY}, *(new Rect(tileSize, color)), visible)); // init default white colored tile @ position
        }
    }
}

/*
void Tilemap::setAllTilesVisible(bool vis){
    for (int i = 0; i < tileData.size(); i++){
        this->tileData[i].setVisible(vis);
    }
}

void Tilemap::createMap(Color defaultColor, Vector2 sz){

}
*/


void Tilemap::refreshMap(){
    vector<Tile> newData = vector<Tile>{};
    for (int x = 0; x < size.x; x++){
        for (int y = 0; y < size.y; y++){
            int idx = Smallmath::TilemapToIndex(Vector2{(float)x,(float)y}, size.x);
            float tileX = this->position.x+x*(tileSize.x+tileGap);
            float tileY = this->position.y+y*(tileSize.y+tileGap);
            newData.push_back(Tile(Vector2{tileX,tileY}, *(new Rect(tileSize, this->tileData[idx].getColor())), this->tileData[idx].isVisible())); // init default white colored tile @ position
        }
    }
    this->tileData = newData;
}

void Tilemap::setTileSize(Vector2 s){
    for (int i = 0; i < tileData.size(); i++){
       tileData[i].setSize(s);
   }
}

void Tilemap::setAllTilesColor(Color color){
        for (int i = 0; i < tileData.size(); i++){   
            this->tileData[i].setColor(color);
        }
}