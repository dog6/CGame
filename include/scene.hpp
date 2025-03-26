#include "game.hpp"
#include "entity.hpp"
#include <vector>

#ifndef SCENE_HPP
#define SCENE_HPP
class Scene {

    private:
        string name;
        Vector2 gravity; // force of 'gravity'
        vector<Entity*> entitiesInScene;
    public:
        Scene(string name);
        ~Scene();
        void render(); // render entities in scene
        void update(float dt); // update entities in scene
        void addEntity(Entity* entity); 
        void addEntities(std::vector<Entity*> entities); 
        void setGravity(Vector2 gravity);
        Vector2 getGravity();
        int getEntityCount(); 
};
#endif