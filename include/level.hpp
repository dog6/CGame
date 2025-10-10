#include "scene.hpp"

#ifndef LEVEL_H
#define LEVEL_H

// A 'level' is an interface
class ILevel {

  private:
  const char* name;

  public:
  virtual ~ILevel();
  virtual void setLevelName(const char* levelName);
  virtual const char* getLevelName() = 0; // gets name of level
  virtual void load() = 0; // load all game entities
  virtual void start() = 0; // called once at start of game, after load
  virtual void update() = 0; // update all game entities
  virtual void render() = 0; // draw things to screen
  virtual void close() = 0; // uninitialize current level
};

#endif