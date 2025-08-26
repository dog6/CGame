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
    Ellipse(IShape* shape);
    Ellipse(float radius, Color color, bool visible = true);
    ~Ellipse();
    void setVisible(bool isVisible) override;
    bool isVisible() override;
    Vector2 getSize() override; // get size
    void setSize(Vector2 size) override; // set size
    Color getColor() override; // get color
    void setColor(Color color) override;
    void draw(Vector2 position, float rot) override;
    vector<Vector2> getVertices(Vector2 pos) override;
    vector<Line> getLines(Vector2 pos) override;

};
#endif