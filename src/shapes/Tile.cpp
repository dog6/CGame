#include "../../include/shapes/tile.hpp"

bool Tile::isVisible() { return this->visible; };
void Tile::setVisible(bool isVisible) { this->visible = isVisible; };

Tile::Tile(Vector2 position, Vector2 size, Color color, bool visible){
    this->position = position;
    // this->rect = Rect{size, color, true};
    this->rect = new Rect{size, color, true};
    this->visible = visible;
}

Tile::Tile(Vector2 position, Rect& rect, bool visible){
    this->position = position;
    this->rect = &rect;
    this->visible = visible;
}

Tile::~Tile(){}

Vector2 Tile::getSize() { return this->rect->getSize(); };
void Tile::setSize(Vector2 size) { this->rect->setSize(size); };

Color Tile::getColor() { return this->rect->getColor(); };
void Tile::setColor(Color color) { this->rect->setColor(color); };

void Tile::draw(Vector2 position) {
    rect->draw(this->position);
};
vector<Vector2> Tile::getVertices(Vector2 pos){
    vector<Vector2> result;
    // TL,TR,BR,BL, so they're inserted backwards
    Vector2 sz = this->getSize();
    result.push_back(Vector2{pos.x-(sz.x/2), pos.y+(sz.x/2)}); // BL 
    result.push_back(Vector2{pos.x+(sz.x/2), pos.y+(sz.x/2)}); // BR
    result.push_back(Vector2{pos.x+(sz.x/2), pos.y-(sz.x/2)}); // TR
    result.push_back(Vector2{pos.x-(sz.x/2), pos.y-(sz.x/2)}); // TL 
    return result;
}

Vector2 Tile::getPosition() { return this->position; }
void Tile::setPosition(Vector2 pos) {this->position = pos;}