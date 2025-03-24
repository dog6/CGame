#include "../../include/shapes/ellipse.hpp"

Ellipse::Ellipse(Vector2 size, Color color, bool visible){
    this->size = size;
    this->visible = visible;
    this->color = color;
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

void Ellipse::Draw(Vector2 position){ DrawEllipse(position.x, position.y, this->size.x, this->size.y, this->color); }

