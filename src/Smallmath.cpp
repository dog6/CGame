#include "../include/smallmath.hpp"

/* estimates width and height using radius
  `returns <Vector2>, parameters <float> radius` */
Vector2 Smallmath::radiusToSize(float r){
  float v = r * sqrtf(2.0f);
  return Vector2{v,v}; 
}

/* estimates radius using width and height
  `returns <float>, parameters <Vector2> size` */
float Smallmath::sizeToRadius(Vector2 v){
  return (fmaxf(v.x, v.y) / sqrtf(2.0f));
}

/* returns x*y <float>
  `returns <float>, parameters <Vector2>` */
float Smallmath::Vector2Product(Vector2 v){
  return v.x*v.y;
}
