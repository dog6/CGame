#include "../include/scene.hpp"
#include <vector>

// Constructor
Scene::Scene(string name){
    this->name = name;
}

// Deconstructor
Scene::~Scene(){
    char buff[100];
    snprintf(buff, sizeof(buff), "Deconstructed Scene {}", this->name.c_str());
    string buffAsStdStr = buff;
    TraceLog(LOG_INFO, buffAsStdStr.c_str());
}

// adds entitiy to scene
void Scene::addEntity(Entity e){
    entitiesInScene.push_back(e);
}

// adds multiple entites to scene
void Scene::addEntities(vector<Entity> entities){
    for (int i = 0; i < entities.size(); i++){
        Scene::addEntity(entities[i]);
    }
}

// renders all entities in the scene
void Scene::render(){
    for (int i = 0; i < entitiesInScene.size(); i++){
        if (entitiesInScene[i].isEnabled){
            entitiesInScene[i].draw(); // draw screen
        }
    }
}

void Scene::update(){
    for (int i = 0; i < entitiesInScene.size(); i++){
        entitiesInScene[i].update(); // update all game logic
    }
}

// returns number of active entities
int Scene::getEntityCount(){
    return entitiesInScene.size();
}