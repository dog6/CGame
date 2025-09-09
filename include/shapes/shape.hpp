#include "../game.hpp"
#include "../line.hpp"

#ifndef M_PI
#define M_PI 3.14
#endif

#ifndef SHAPE_HPP
#define SHAPE_HPP



// Interface
class IShape {
    public:
        virtual ~IShape() {} // Virtual destructor
        virtual void setVisible(bool isVisible) = 0;
        virtual bool isVisible() = 0;

        virtual Vector2 getSize() = 0;
        virtual Color getColor() = 0;
        virtual void setColor(Color color) = 0;
        virtual void setSize(Vector2 size) = 0;

        virtual vector<Vector2> getVertices(Vector2 pos) = 0;
        virtual vector<Line> getLines(Vector2 pos) = 0; // returns lines that make up shape

        virtual void draw(Vector2 position, float rot = 0) = 0; // draw shape to screen
};
#endif