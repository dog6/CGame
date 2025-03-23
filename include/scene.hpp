#include "game.hpp"
#include "entity.hpp"
#include <vector>

#ifndef SCENE_HPP
#define SCENE_HPP
class Scene {

    private:
        string name;
        vector<Entity> entitiesInScene;
    public:
        Scene(string name);
        ~Scene();
        void Render(); // render entities in scene
        void Update(); // update entities in scene
        void AddEntity(Entity entity); 
        void AddEntities(std::vector<Entity> entities); 
        int EntityCount(); 
};
#endif