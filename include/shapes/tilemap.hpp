#include "../game.hpp"
#include "shape.hpp"
#include "tile.hpp"

#ifndef TILEMAP_H
#define TILEMAP_H
class Tilemap: public IShape {

    private:
    Vector2 position; // position of tilemap
    Vector2 size; // width & height
    Vector2 tileSize; // width & height of individual tiles
    vector<bool> tileVisible; // arr of bools, true if a tile is visible
    
    
    public: 
    vector<Tile> tileData; // arr of tiles
    Tilemap(Vector2 position, Vector2 size, Vector2 tile_size, float tile_gap = 0, bool visible = true);
    ~Tilemap();
    void setTile(Vector2 pos, Tile tile); // set tile
    void setTileVisible(Vector2 pos, bool isVisible = true); // set tile @ position 
    Vector2 getTileSize(); // resize tile to new size
    Tile* getTile(Vector2 pos); //gets hovered tile
    bool visible;
    float tileGap = 0;
    void setTileSize(Vector2 s); // resize tile to new size
    /*
    void setAllTilesVisible(bool vis);
    */
   void refreshMap();
    void setAllTilesColor(Color color); // sets all tiles
    void setTileData(Color color, bool visible);

    /* IShape methods */
    void setVisible(bool isVisible) override;
    bool isVisible() override;
    Vector2 getSize() override;
    Color getColor() override;
    void setColor(Color color) override;
    void setSize(Vector2 size) override;
    void draw(Vector2 position, float rot) override; // draws tilemap
    vector<Vector2> getVertices(Vector2 pos) override;
    vector<Line> getLines(Vector2 pos) override;

};
#endif