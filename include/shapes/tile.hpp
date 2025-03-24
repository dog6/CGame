#include "../game.hpp"
#include "shape.hpp"
#include "rectangle.hpp"

#ifndef TILE_HPP
#define TILE_HPP
class Tile: public IShape {

    private:
    Vector2 position;
    bool visible;
    
    public:
    Tile(Vector2 position, Vector2 size, Color color, bool visible = true);
    Tile(Vector2 position, Rect& Rect, bool visible = true);
    ~Tile();
    void setVisible(bool isVisible) override;
    bool isVisible() override;
    
    Vector2 getSize() override; // get size
    void setSize(Vector2 size) override; // set size
    
    Color getColor() override; // get color
    
    void draw(Vector2 position) override; // draw tile to screen
    
    // Tile only
    Rect rect;
    Vector2 getPosition(); // get position
    void setPosition(Vector2 pos); // set position

};
#endif