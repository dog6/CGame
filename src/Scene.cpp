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
void Scene::AddEntity(Entity e){
    entitiesInScene.push_back(e);
}

// adds multiple entites to scene
void Scene::AddEntities(vector<Entity> entities){
    for (int i = 0; i < entities.size(); i++){
        Scene::AddEntity(entities[i]);
    }
}

// renders all entities in the scene
void Scene::Render(){
    for (int i = 0; i < entitiesInScene.size(); i++){
        if (entitiesInScene[i].isEnabled){
            entitiesInScene[i].Draw(); // draw screen
        }
    }
}

void Scene::Update(){
    for (int i = 0; i < entitiesInScene.size(); i++){
        entitiesInScene[i].Update(); // update all game logic
    }
}

// returns number of active entities
int Scene::EntityCount(){
    return entitiesInScene.size();
}