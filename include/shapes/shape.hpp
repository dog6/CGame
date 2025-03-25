#include "../game.hpp"

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


        virtual void draw(Vector2 position, float rot = 0) = 0; // draw shape to screen
        // virtual float sizeToRadius(); // converts width & height to radius (for equidistant ellipse & rectangle)
};
#endif