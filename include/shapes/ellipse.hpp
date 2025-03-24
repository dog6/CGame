#include "../game.hpp"
#include "shape.hpp"

#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP
class Ellipse: public IShape {
    private:
    bool visible;
    Vector2 size;
    Color color;

    public:
    Ellipse(Vector2 size, Color color, bool visible = true);
    Ellipse(float radius, Color color, bool visible = true);
    ~Ellipse();
    void setVisible(bool isVisible) override;
    bool isVisible() override;

    Vector2 getSize() override; // get size
    void setSize(Vector2 size) override; // set size
    
    Color getColor() override; // get color
    void Draw(Vector2 position) override;

};
#endif