#include "game.hpp"

#ifndef SMALLMATH_H
#define SMALLMATH_H
class Smallmath {
  private:
  Smallmath() = delete;
  public:
  ~Smallmath(); // destructor
  static Vector2 radiusToSize(float r);
  static float sizeToRadius(Vector2 v);

};
#endif