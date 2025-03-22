#include "../game.hpp"

// Interface
class IShape {
    public:
        virtual ~IShape() {} // Virtual destructor
        virtual void setVisible(bool isVisible) = 0;
        virtual bool isVisible() = 0;

        virtual Vector2 getSize() = 0;
        virtual Color getColor() = 0;
        
        virtual void setSize(Vector2 size) = 0;

        virtual void Draw() = 0; // draw shape to screen
};