#include "game.hpp"

#ifndef RIGIDBODY_H
#define RIGIDBODY_H
class Rigidbody {

    public: 
        Rigidbody(Vector2 position, Vector2 velocity = Vector2{0,0}, Vector2 force = Vector2{0,0});
        ~Rigidbody();
        Vector2 position; // position of body/entity
        Vector2 velocity; // velocity of body
        Vector2 force; // forces being applied to body
};
#endif