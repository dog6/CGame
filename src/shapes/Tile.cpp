#include "../../include/shapes/tile.hpp"

bool Tile::isVisible() { return this->visible; };
void Tile::setVisible(bool isVisible) { this->visible = isVisible; };

Tile::Tile(Vector2 position, Vector2 size, Color color, bool visible){
    this->position = position;
    this->rect = Rect{size, color, true};
    this->visible = visible;
}

Tile::Tile(Vector2 position, Rect& rect, bool visible){
    this->position = position;
    this->rect = rect;
    this->visible = visible;
}

Tile::~Tile(){}

Vector2 Tile::getSize() { return this->rect.getSize(); };
void Tile::setSize(Vector2 size) { this->rect.setSize(size); };

Color Tile::getColor() { return this->rect.getColor(); };

void Tile::draw(Vector2 position) {
    rect.draw(this->position);
};

Vector2 Tile::getPosition() { return this->position; }
void Tile::setPosition(Vector2 pos) {this->position = pos;}