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

void Scene::setGravity(Vector2 grav){ this->gravity=grav; }

Vector2 Scene::getGravity(){ return this->gravity; }

// adds entitiy to scene
void Scene::addEntity(Entity* e){ entitiesInScene.push_back(e); }

// adds multiple entites to scene
void Scene::addEntities(vector<Entity*> entities){
    for (int i = 0; i < entities.size(); i++){ Scene::addEntity(entities[i]); }
    // delete &entities;
}

// renders all entities in the scene
void Scene::render(){
    for (int i = 0; i < entitiesInScene.size(); i++){
        if (entitiesInScene[i]->isEnabled){
            entitiesInScene[i]->draw(); // draw screen
        }
    }
}

void Scene::update(float dt){
    for (int i = 0; i < entitiesInScene.size(); i++){
        entitiesInScene[i]->update(dt, this->gravity); // update all game logic
        // entitiesInScene[i]->handleCollision(entitiesInScene); WIP
    }
}

// returns number of active entities
int Scene::getEntityCount(){
    return entitiesInScene.size();
}