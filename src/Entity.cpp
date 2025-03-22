#include "../include/game.hpp"
#include "../include/entity.hpp"

Entity::Entity(string name, bool enabled){
    this->name = name;
    this->isEnabled = enabled;
    this->shape = nullptr;
}

Entity::~Entity(){
    char buff[100];
    snprintf(buff, sizeof(buff), "Deconstructed Entity {}", this->name.c_str());
    string buffAsStdStr = buff;
    TraceLog(LOG_INFO, buffAsStdStr.c_str());
}

// Update entity logic
void Entity::Update(){

}

// Draw entity shape
void Entity::Draw(){
    if (shape != nullptr){
        shape->Draw();
    }
}