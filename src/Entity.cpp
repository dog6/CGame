#include "../include/game.hpp"
#include "../include/entity.hpp"

Entity::Entity(string name, Vector2 position, bool enabled){
    this->name = name;
    this->body = new Rigidbody(position);
    this->isEnabled = enabled;
    this->shape = nullptr;
}

Entity::~Entity(){
    char buff[100];
    snprintf(buff, sizeof(buff), "Deconstructed Entity {}", this->name.c_str());
    string buffAsStdStr = buff;
    TraceLog(LOG_INFO, buffAsStdStr.c_str());
}

// update entity logic
void Entity::update(){
}

// draw entity shape
void Entity::draw(){
    if (shape != nullptr){
        shape->draw(body->position);
    }
}