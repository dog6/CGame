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
    vector<Tile> tileData; // arr of tiles
    vector<bool> tileVisible; // arr of bools, true if a tile is visible


    public: 
    Tilemap(Vector2 position, Vector2 size, Vector2 tile_size, float tile_gap = 0, bool visible = true);
    ~Tilemap();
    void setTileVisible(Vector2 pos, bool isVisible = true); // set tile @ position 
    void setTile(Vector2 pos, Tile tile); // set tile
    void setTileData(Color color); // sets all tiles 
    Tile* getTile(Vector2 pos); //gets hovered tile
    bool visible;
    float tileGap = 0;



    /* IShape methods */
    void setVisible(bool isVisible) override;
    bool isVisible() override;
    Vector2 getSize() override;
    Color getColor() override;
    void setColor(Color color) override;
    void setSize(Vector2 size) override;
    void draw(Vector2 position, float rot) override; // draws tilemap
    vector<Vector2> getVertices(Vector2 pos) override;


};
#endif