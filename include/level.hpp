#include "scene.hpp"

#ifndef LEVEL_H
#define LEVEL_H

// A 'level' is an interface
class ILevel {

  private:

  public:
  virtual ~ILevel();
  virtual void load(); // load all game entities
  virtual void start(); // called once at start of game, after load
  virtual void update(); // update all game entities
  virtual void render(); // draw things to screen

};

#endif