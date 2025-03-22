// #include "../../include/game.hpp"
#include "../../include/shapes/rectangle.hpp"

// Constructor
Rect::Rect(Vector2 size, Color color, bool visible){
    this->size = size;
    this->color = color;
    this->visible = visible;
}

Rect::~Rect(){
}

bool Rect::isVisible() { return this->visible; };
void Rect::setVisible(bool isVisible) { this->visible = isVisible; };

Vector2 Rect::getSize() { return this->size; };
void Rect::setSize(Vector2 size) { this->size = size; };

Color Rect::getColor() { return this->color; };

void Rect::Draw(Vector2 position) {
    DrawRectangleV(position, size, color);
};