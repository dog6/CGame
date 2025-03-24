#include "../include/game.hpp"
#include "../include/entity.hpp"

Entity::Entity(string name, Vector2 position, bool enabled){
    this->name = name;
    this->body = new Rigidbody(position);
    this->isEnabled = enabled;
    this->shape = nullptr;
}

Entity::~Entity(){
    TraceLog(LOG_INFO, "Destructed ~Entity()");
}

// update entity logic
void Entity::update(float dt, Vector2 forces){
    if (this->body != nullptr){
        if (collideWithCamera){ // check for collisions with camera
            this->collideWithCameraBorders();
        } 
        body->update(dt, forces); // update rigidbody physics
    }
}

float bounceStrength = 0.8;
void Entity::collideWithCameraBorders() {

    // Left of camera
    if (body->position.x-(shape->getSize().x) <= 0){
        body->position.x = (shape->getSize().x);
        body->velocity.x *= -0.5;
    }

    // Right of camera
    if (body->position.x+(shape->getSize().x) >= screenWidth){
        body->position.x = screenWidth-(shape->getSize().x);
        body->velocity.x *= -0.5;
    }

    // Top of camera
    if (body->position.y-(shape->getSize().y) <= 0){
        body->position.y = (shape->getSize().y);
        body->velocity.y *= -bounceStrength;
    }
    // Bottom of camera
    if (body->position.y+(shape->getSize().y) >= screenHeight){
        body->position.y = screenHeight-(shape->getSize().y);
        body->velocity.y *= -bounceStrength;
    }
    

}

// draw entity shape
void Entity::draw(){
    if (shape != nullptr){
        shape->draw(body->position);
    }
}