#include "../game.hpp"
#include "shape.hpp"

#ifndef RECTANGLE_H
#define RECTANGLE_H
class Rect: public IShape {

    private:
    bool visible;
    Vector2 size;
    Color color;

    public:
    // constructors
    Rect();
    Rect(Vector2 size, Color color, bool visible = true); 
    ~Rect(); // deconstructor
    void setVisible(bool isVisible) override;
    bool isVisible() override;

    Vector2 getSize() override; // get size
    void setSize(Vector2 size) override; // set size
    
    Color getColor() override; // get color
    
    Rectangle ToRectangle(Vector2 position);

    void Draw(Vector2 position) override;
};
#endif