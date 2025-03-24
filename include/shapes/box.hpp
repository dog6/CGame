// Polygon version of a rectangle
#include "../game.hpp"
#include "shape.hpp"

#ifndef BOX_H
#define BOX_H
class Box: public IShape {

    private:
    bool visible;
    float size;
    Color color;

    public:
    // constructors
    Box();
    Box(IShape* shape);
    Box(float size, Color color, bool visible = true); 
    ~Box(); // deconstructor
    void setVisible(bool isVisible) override;
    bool isVisible() override;

    Vector2 getSize() override; // get size
    void setSize(Vector2 size) override; // set size
    
    Color getColor() override; // get color
    void draw(Vector2 position) override;
    
    Rectangle toRectangle(Vector2 position);

    // float sizeToRadius();
    // Vector2 radiusToSize();
};
#endif