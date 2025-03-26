// #include "../../include/shapes/shape.hpp"
#include "../../include/shapes/shape.hpp"
#include "../../include/shapes/rectangle.hpp"
// #include "../../include/line.hpp"
// Constructor
Rect::Rect(Vector2 size, Color color, bool visible){
    this->size = size;
    this->color = color;
    this->visible = visible;
}

Rect::Rect(IShape* shape){
    this->size = shape->getSize();
    this->color = shape->getColor();
    this->visible = shape->isVisible();
}

Rect::Rect(){
    this->size = Vector2Zero();
    this->color = WHITE;
    this->visible = false;
}

Rect::~Rect(){} // destructor

bool Rect::isVisible() { return this->visible; };
void Rect::setVisible(bool isVisible) { this->visible = isVisible; };

Vector2 Rect::getSize() { return this->size; };
void Rect::setSize(Vector2 size) { this->size = size; };

Color Rect::getColor() { return this->color; };
void Rect::setColor(Color color) { this->color = color; };

void Rect::draw(Vector2 position, float rot) {
    DrawRectanglePro(this->toRectangle(position), Vector2Zero(), rot, this->color);
};

vector<Vector2> Rect::getVertices(Vector2 pos){
    vector<Vector2> result;
    Rectangle r = this->toRectangle(pos);
    result.push_back(Vector2{pos.x-(r.width), pos.y+(r.height)});
    result.push_back(Vector2{pos.x+(r.width), pos.y+(r.height)});
    result.push_back(Vector2{pos.x+(r.width), pos.y-(r.height)});
    result.push_back(Vector2{pos.x-(r.width), pos.y-(r.height)});
    return result;
  }

Rectangle Rect::toRectangle(Vector2 position){
    Rectangle r = Rectangle();
    r.width = this->size.x;
    r.height = this->size.y;
    r.x = position.x;
    r.y = position.y;
    return r;
}

vector<Line> Rect::getLines(Vector2 pos){
    vector<Line> result;
    vector<Vector2> points = this->getVertices(pos);
    // for each point, make a line
    for (int i = 0; i <= points.size(); i += 2){
        result.push_back(*(new Line(points[i], points[i+1], RED)));
    }
    return result;
}