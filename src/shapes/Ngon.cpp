#include "../../include/shapes/ngon.hpp"

Ngon::Ngon(int n, float r, Color color, bool visible){
    this->sideCount = n;
    this->radius = r;
    this->color = color;
    this->visible = visible;
}

Ngon::~Ngon(){}

void Ngon::setSides(int n){ this->sideCount = n; }
int Ngon::getSides() { return this->sideCount;}             // returns number of sides

void Ngon::setSize(Vector2 r) { this->radius = r.x;}    // sets radius
Vector2 Ngon::getSize() { return Vector2{this->radius, this->radius};}          // gets radius

void Ngon::setColor(Color col) { this->color = col; }   // sets color
Color Ngon::getColor() { return this->color; }

void Ngon::setVisible(bool isVisible) { this->visible = isVisible; }
bool Ngon::isVisible() { return this->visible; }

vector<Vector2> Ngon::getVertices(Vector2 pos) {
    std::vector<Vector2> vertices;
        int c = (int)Clamp((float)sideCount, 3, 16);
        // float angleIncrement = 2.0f * 3.14 / sideCount; // Angle between vertices
        float angleIncrement = (360/c) * 3.14 / sideCount;

        for (int i = 0; i < c; i++) {
            float angle = i * angleIncrement;
            Vector2 vertex = {
                pos.x + radius * std::cos(angle),
                pos.y + radius * std::sin(angle)
            };
            vertices.push_back(vertex);
        }

        return vertices;
}

vector<Line> Ngon::getLines(Vector2 pos){
    vector<Line> result;
    vector<Vector2> points = this->getVertices(pos);
    // for each point, make a line
    for (int i = 0; i <= points.size(); i += 2){
        result.push_back(*(new Line(points[i], points[i+1], RED)));
    }
    return result;
}

void Ngon::draw(Vector2 position, float rot){ DrawPoly(position, this->sideCount, this->radius, rot, this->color);}