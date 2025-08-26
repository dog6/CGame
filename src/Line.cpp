#include "../include/game.hpp"
#include "../include/line.hpp"
#include "../include/smallmath.hpp"

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

Vector2 Line::getDirection(){
  return Smallmath::Vector2Direction(this->startPoint, this->endPoint);
}

bool Line::checkIfLinesIntersect(Line lineA, Line lineB){

    Vector2 p1 = lineA.startPoint;
    Vector2 p2 = lineA.endPoint;
    Vector2 p3 = lineB.startPoint;
    Vector2 p4 = lineB.endPoint;

    float d = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
    
    if (d == 0) return false;

    float t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / d;
    float u = -((p1.x - p2.x) * (p1.y - p3.y) - (p1.y - p2.y) * (p1.x - p3.x)) / d;

    return t >= 0 && t <= 1 && u >= 0 && u <= 1;

}