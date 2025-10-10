#include "../include/scene_manager.hpp"

SceneManager::SceneManager(){}
SceneManager::~SceneManager(){}

/* Adds level to the scene manager */
void SceneManager::AddLevel(ILevel* level){
  try {
    levels.push_back(level);
  }catch (exception e){
    TraceLog(LOG_ERROR, "Failed to add level to scene manager. -> %s", e.what());
  }
} 

/* Adds multiple levels to the SceneManager */
void SceneManager::AddLevels(vector<ILevel*> lvls){
  for (int i = 0; i < lvls.size(); i++){
    AddLevel(lvls[i]);
  }
}

/* Removes a level from scene manager using the levels index */
void SceneManager::RemoveLevel(int i){
  if (levels[i] == currentLevel){
    TraceLog(LOG_INFO, "SceneManager is closing the current level.");
    currentLevel->close();
  }
  try {
    levels.erase(levels.begin()+i);
  }catch (exception e){
    TraceLog(LOG_ERROR, "Failed to remove level from scene manager. -> %s", e.what());
  }
}      

/* Removes level from scene manager using a given level name */
void SceneManager::RemoveLevelByName(const char* name){
  for (int i = 0; i < levels.size(); i++){
    if (levels[i]->getLevelName() == name){
      RemoveLevel(i);
      return;
    }
  }
  TraceLog(LOG_INFO, "Failed to remove level with name %s", name);
} 

/* Selects level as current level & runs load() & start() methods*/
void SceneManager::LoadLevel(int i){
  if (levels[i] == nullptr){
    TraceLog(LOG_ERROR, "SceneManager is unable to load level %i. Only %i levels available", i, levels.size());
  }
  this->currentLevel = this->levels[i];
  TraceLog(LOG_INFO, "SceneManager is loading level '%s'", currentLevel->getLevelName());
  currentLevel->load(); // load level
  currentLevel->start(); // start level
} 

/* Selects level as current level by name & runs load() & start() methods*/
void SceneManager::LoadLevelByName(const char* n){
  for (int i = 0; i < levels.size(); i++){
    if (levels[i]->getLevelName() == n){
      LoadLevel(i);
      return;
    }
  }
  TraceLog(LOG_ERROR, "Failed to load level named: %s. Are you sure it's been added to the SceneManager?", n);
} 

// Updates currently loaded scene 'currentLevel'
void SceneManager::UpdateCurrentScene(){
  if (this->currentLevel == nullptr){
    TraceLog(LOG_ERROR, "Failed to update current scene. No level selected");
    return;
  }
  this->currentLevel->update();
}

// Renders currently loaded scene 'currentLevel'
void SceneManager::RenderCurrentScene(){
    if (this->currentLevel == nullptr){
      TraceLog(LOG_ERROR, "Failed to render current scene. No level selected");
      return;
    }
    this->currentLevel->render();
}