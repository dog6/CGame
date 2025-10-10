#include "../game.hpp"
#include "shape.hpp"

#ifndef NGON_HPP
#define NGON_HPP
class Ngon: public IShape {

    private:
    float radius;
    int sideCount;
    Color color;
    bool visible;

    public:
    /*
    `<int>` Number of sides, 
      `<float>` radius,
      `<Color>` color,
      `<bool> *default = true*` visible
    */
    Ngon(int n, float r, Color color, bool visible = true);
    ~Ngon();

    void setSides(int n);       // sets number of sides
    int getSides();             // returns number of sides

    void setSize(Vector2 r) override;    // sets radius
    Vector2 getSize() override;          // gets radius

    void setColor(Color col) override;   // sets color
    Color getColor() override;           // gets color

    void setVisible(bool isVisible) override;
    bool isVisible() override;
    vector<Vector2> getVertices(Vector2 pos) override;
    vector<Line> getLines(Vector2 pos) override;

    void draw(Vector2 position, float rot) override;

};
#endif