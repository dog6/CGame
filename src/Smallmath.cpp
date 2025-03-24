#include "../include/smallmath.hpp"

Vector2 Smallmath::radiusToSize(float r){
  float v = r * sqrtf(2.0f);
  return Vector2{v,v}; 
}

float Smallmath::sizeToRadius(Vector2 v){
  return (fmaxf(v.x, v.y) / sqrtf(2.0f));
}
