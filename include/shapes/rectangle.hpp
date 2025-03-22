#include "../game.hpp"
#include "shape.hpp"

class Rect: public IShape {

    private:
        Vector2 size;
        bool visible;
        Color color;

    public:
        Rect(Vector2 size, Color color, bool visible); // constructor
        ~Rect(); // deconstructor
        void setVisible(bool isVisible);
        bool isVisible();

        Vector2 getSize(); // get size
        void setSize(Vector2 size); // set size
        
        Color getColor(); // get color
        
        void Draw(Vector2 position);
};