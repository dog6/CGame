#include "game.hpp"

#ifndef VERTEX_H
#define VERTEX_H
class Vertex {
  public:
  Vertex(Vector2 pos);
  ~Vertex();
  Vector2 position;
};

#endif