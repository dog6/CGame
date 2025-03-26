#include "game.hpp"
#include "shapes/shape.hpp"
#include "rigidbody.hpp"

#ifndef ENTITY_H
#define ENTITY_H

class Entity {
    private: 
    void collideWithCameraBorders();
    float rotation;

    public:
        Entity(string name, Vector2 position, float rot = 0, bool hasCollider = true, bool enabled = true); // constructor
        ~Entity();
        void draw();    // draw method
        void update(float dt, Vector2 sceneGravity); // update method
        void handleCollision(vector<Entity*> entities);
        void setRotation(float rot);
        float getRotation();
        string name;
        bool doesCollideWithWindow; // can the entity collide with the window?
        bool isEnabled; // is the entity active?
        bool hasCollider; // does the entity have collision?
        bool isColliding; // is the entity currently colliding with at least one thing?
        Rigidbody* body;
        IShape* shape; // *ptr to shape interface
};
#endif