#include "game.hpp"
#include "shapes/shape.hpp"
#include "rigidbody.hpp"

#ifndef ENTITY_H
#define ENTITY_H
class Entity {
    public:
        Entity(string name, Vector2 position, bool enabled = true); // constructor
        ~Entity();
        void Draw();    // draw method
        void Update(); // update method
        string name;
        bool isEnabled; // is the entity active?
        Rigidbody* body;
        IShape* shape; // *ptr to shape interface
};
#endif