#include "../game.hpp"
#include "shape.hpp"

#ifndef RECTANGLE_H
#define RECTANGLE_H
class Rect : public IShape {

    private:
        Vector2 size;
        bool visible;
        Color color;

    public:
        Rect(Vector2 size, Color color, bool visible = true); // constructor
        ~Rect(); // deconstructor
        void setVisible(bool isVisible) override;
        bool isVisible() override;

        Vector2 getSize() override; // get size
        void setSize(Vector2 size) override; // set size
        
        Color getColor() override; // get color
        
        void Draw(Vector2 position) override;
};
#endif