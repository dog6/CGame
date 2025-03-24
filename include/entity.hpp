#include "game.hpp"
#include "shapes/shape.hpp"
#include "rigidbody.hpp"
#include "entity_type.hpp"

#ifndef ENTITY_H
#define ENTITY_H
/*
enum EntityType{
    Ellipse,
    Rectangle,
};
*/
class Entity {
    private: 
    void collideWithCameraBorders();
    
    public:
        Entity(string name, Vector2 position,  bool hasCollider = true, bool enabled = true); // constructor
        ~Entity();
        void draw();    // draw method
        void update(float dt, Vector2 sceneGravity); // update method
        void handleCollision(vector<Entity> entities);
        string name;
        EntityType entityType; // for collision
        bool collideWithCamera; // can the entity leave the screen?
        bool isEnabled; // is the entity active?
        bool hasCollider; // does the entity have collision?
        Rigidbody* body;
        IShape* shape; // *ptr to shape interface
};
#endif