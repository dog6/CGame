#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "level.hpp"

// Lives in game class, loads 'level'
class SceneManager {
  private:
  vector<ILevel*> levels;
  ILevel* currentLevel;
  
  public:
  SceneManager();
  ~SceneManager();
  void AddLevel(ILevel* level);                 // adds level to scene manager
  void AddLevels(vector<ILevel*> lvls);         // adds multiple levels to scene manager
  void RemoveLevel(int i);                      // removes level from scene manager using a given id
  void RemoveLevelByName(const char* name);     // removes level from scene manager using a given name
  void LoadLevel(int i);                        // loads level by it's index
  void LoadLevelByName(const char* name);       // loads level by it's name
  void UpdateCurrentScene();                    // updates current scene
  void RenderCurrentScene();                    // renders current scene to window

};

#endif