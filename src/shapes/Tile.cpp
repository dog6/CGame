#include "../../include/shapes/tile.hpp"

bool Tile::isVisible() { return this->visible; };
void Tile::setVisible(bool isVisible) { this->visible = isVisible; };

Tile::Tile(){
    this->position = Vector2{0,0};
    this->rect = new Rect{Vector2{0,0}, BLACK, false};
}

Tile::Tile(Vector2 position, Vector2 size, Color color, bool visible){
    this->position = position;
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

void Tile::draw(Vector2 position, float rot) {
    rect->draw(this->position, rot);
};
vector<Vector2> Tile::getVertices(Vector2 pos){
    vector<Vector2> result;
    // TL,TR,BR,BL, so they're inserted backwards
    Rectangle r = this->toRectangle(pos);
    result.push_back(Vector2{pos.x-(r.width), pos.y+(r.height)});
    result.push_back(Vector2{pos.x+(r.width), pos.y+(r.height)});
    result.push_back(Vector2{pos.x+(r.width), pos.y-(r.height)});
    result.push_back(Vector2{pos.x-(r.width), pos.y-(r.height)});
    return result;
}

Rectangle Tile::toRectangle(Vector2 pos) {
    Rectangle r = Rectangle();
    Vector2 sz = this->getSize();
    r.width = sz.x;
    r.height = sz.y;
    r.x = pos.x;
    r.y = pos.y;
    return r;
}

Vector2 Tile::getPosition() { return this->position; }
void Tile::setPosition(Vector2 pos) {this->position = pos;}


vector<Line> Tile::getLines(Vector2 pos){
    vector<Line> result;
    vector<Vector2> points = this->getVertices(pos);
    // for each point, make a line
    for (int i = 0; i <= points.size(); i += 2){
        result.push_back(*(new Line(points[i], points[i+1], RED)));
    }
    return result;
}
    