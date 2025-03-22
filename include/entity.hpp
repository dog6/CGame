#include "game.hpp"
#include "shapes/shape.hpp"

class Entity {
    public:
        Entity(string name, bool enabled = true); // constructor
        ~Entity();
        void Draw();    // draw method
        void Update(); // update method
        
        string name;
        bool isEnabled; // is the entity active?
        Vector2 position; // position of 2d object
        Vector2 velocity; // velocity of 2d object calculated w/ 'force'
        Vector2 force; // 2d forces applied to 2d object
        IShape* shape; // *ptr to shape interface
};