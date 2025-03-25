#include "../include/game.hpp"
#include "../include/line.hpp"

Line::Line(Vector2 start, Vector2 end, Color col){
  this->startPoint = start;
  this->endPoint = end;
  this->color = col;
  this->length = Vector2Distance(start,end);
}

Line::~Line(){}

void Line::draw(){
  DrawLineV(this->startPoint, this->endPoint, this->color);
}