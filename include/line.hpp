#include "game.hpp"

#ifndef LINE_H
#define LINE_H
class Line {

  public:
  Line(Vector2 start, Vector2 end, Color color = BLACK);
  ~Line();
  void draw();
  Vector2 startPoint;
  Vector2 endPoint;
  Color color; // color of line
  float length; // length of line
};
#endif