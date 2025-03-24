#include "game.hpp"

#ifndef RIGIDBODY_H
#define RIGIDBODY_H
class Rigidbody {

    public: 
        Rigidbody(Vector2 position, Vector2 velocity = Vector2{0,0}, Vector2 acceleration = Vector2{0,0}, Vector2 force = Vector2{0,0}, bool kinematic = true);
        ~Rigidbody();
        void update(float dt, Vector2 forces); // update physics of body
        bool isKinematic; // true = ignores external forces
        float mass; // mass of object in kg
        Vector2 position; // position of body/entity
        Vector2 velocity; // velocity of body
        Vector2 acceleration; // accleration on body 
        Vector2 force; // other forces being applied to body
};
#endif