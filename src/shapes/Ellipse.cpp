#include "../../include/shapes/ellipse.hpp"

Ellipse::Ellipse(Vector2 size, Color color, bool visible){
    this->size = size;
    this->visible = visible;
    this->color = color;
}

Ellipse::Ellipse(IShape* shape){
    this->size = shape->getSize();
    this->visible = shape->isVisible();
    this->color = shape->getColor();
}

Ellipse::Ellipse(float radius, Color color, bool visible){
    this->size = Vector2{radius*2, radius*2};
    this-> visible = visible;
    this->color = color;
}

Ellipse::~Ellipse(){} // destructor

Color Ellipse::getColor(){ return this->color; }

Vector2 Ellipse::getSize(){ return this->size; }
void Ellipse::setSize(Vector2 size){ this->size = size; }

bool Ellipse::isVisible(){ return this->visible; }
void Ellipse::setVisible(bool visible){ this->visible = visible; }

vector<Vector2> Ellipse::getVertices(Vector2 pos){
    // TL,TR,BR,BL, so they're inserted backwards
    vector<Vector2> result;
    Vector2 sz = this->getSize();
    result.push_back(Vector2{pos.x-sz.x, pos.x+sz.y}); // BL
    result.push_back(Vector2{pos.x+sz.x, pos.x+sz.y}); // BR
    result.push_back(Vector2{pos.x+sz.x, pos.x-sz.y}); // TR
    result.push_back(Vector2{pos.x-sz.x, pos.x-sz.y}); // TL
    return result;
}

void Ellipse::draw(Vector2 position){ 
    DrawEllipse(position.x, position.y, this->size.x, this->size.y, this->color);
    // DrawPoly(position, 32, this->sizeToRadius(), )
 }

