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
        
        virtual void setSize(Vector2 size) = 0;

        virtual void draw(Vector2 position) = 0; // draw shape to screen
};
#endif