#include "game.hpp"
#include "shapes/shape.hpp"
#include "rigidbody.hpp"

#ifndef ENTITY_H
#define ENTITY_H
class Entity {
    public:
        Entity(string name, Vector2 position, bool enabled = true); // constructor
        ~Entity();
        void draw();    // draw method
        void update(float dt, Vector2 sceneGravity); // update method
        void collideWithCameraBorders();
        string name;
        bool collideWithCamera; // can the entity leave the screen?
        bool isEnabled; // is the entity active?
        Rigidbody* body;
        IShape* shape; // *ptr to shape interface
};
#endif