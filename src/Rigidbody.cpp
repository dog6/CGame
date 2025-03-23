#include "../include/rigidbody.hpp"

Rigidbody::Rigidbody(Vector2 pos, Vector2 velocity, Vector2 force){
    this->position = pos;
    this->velocity = velocity;
    this->force = force;
}

Rigidbody::~Rigidbody(){
    TraceLog(LOG_INFO, "Destructed body");
}