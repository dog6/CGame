#include "../include/rigidbody.hpp"

Rigidbody::Rigidbody(Vector2 pos, Vector2 velocity, Vector2 acceleration, Vector2 force, bool kinematic){
    this->position = pos;
    this->velocity = velocity;
    this->acceleration = acceleration;
    this->force = force;
    this->isKinematic = kinematic;
}

Rigidbody::~Rigidbody(){
    TraceLog(LOG_INFO, "Destructed body");
}

void Rigidbody::update(float dt, Vector2 forces){

    // Move rigidbody according to physics
    if (!this->isKinematic){
        this->force = forces+this->force;
        this->acceleration = Vector2{this->force.x/this->mass, this->force.y/this->mass}; // A = F/m
        this->velocity += Vector2{acceleration.x*dt, acceleration.y*dt}; // V = A * T
        this->position += Vector2{this->velocity.x*dt, this->velocity.y*dt}; // D = V * T
    }

}