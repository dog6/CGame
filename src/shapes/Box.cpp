#include "../../include/shapes/box.hpp"
#include "../../include/smallmath.hpp"
// Constructor
Box::Box(float size, Color color, bool visible){
  this->size = size;
  this->color = color;
  this->visible = visible;
}

Box::Box(IShape* shape){
  this->size = Smallmath::sizeToRadius(shape->getSize());
  this->color = shape->getColor();
  this->visible = shape->isVisible();
}

/*Box::Box(){
  this->size = 10;
  this->color = WHITE;
  this->visible = false;
}*/

Box::~Box(){} // destructor

bool Box::isVisible() { return this->visible; };
void Box::setVisible(bool isVisible) { this->visible = isVisible; };

Vector2 Box::getSize() { return Smallmath::radiusToSize(this->size); };
void Box::setSize(Vector2 size) { this->size = Smallmath::sizeToRadius(size); }; // only use x for box

Color Box::getColor() { return this->color; };

void Box::draw(Vector2 position, float rot) {
  DrawPoly(position, 4, this->size, rot+45, this->color);
};

Rectangle Box::toRectangle(Vector2 position){
  Rectangle r = Rectangle();
  Vector2 sz = Smallmath::radiusToSize(this->size);
  r.width = sz.x;
  r.height = sz.y;
  r.x = position.x;
  r.y = position.y;
  return r;
}

vector<Vector2> Box::getVertices(Vector2 pos){
  vector<Vector2> result;
  // TL,TR,BR,BL, so they're inserted backwards
  Vector2 sz = this->getSize();
  result.push_back(Vector2{pos.x-(sz.x/2), pos.y+(sz.x/2)}); // BL 
  result.push_back(Vector2{pos.x+(sz.x/2), pos.y+(sz.x/2)}); // BR
  result.push_back(Vector2{pos.x+(sz.x/2), pos.y-(sz.x/2)}); // TR
  result.push_back(Vector2{pos.x-(sz.x/2), pos.y-(sz.x/2)}); // TL 
  return result;
}

void Box::setColor(Color color) { this->color = color; }