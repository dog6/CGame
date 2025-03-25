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
  static float Vector2Product(Vector2 v);
  static Vector2 Vector2ProductValue(Vector2 v, float val);
  static float Vector2Divide(Vector2 v); // divides x/y
  static Vector2 Vector2DivideValue(Vector2 v, float val);
};
#endif