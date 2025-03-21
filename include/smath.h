#pragma once
#include <iostream>

using namespace std;
struct Vector2 {
    int X;
    int Y;

public:
    void Print() {
        std::cout << "(" << this->X << ", " << this->Y << ")";
    }
    
    void Println() {
        std::cout << "(" << this->X << ", " << this->Y << ")" << endl;
    }
    
    Vector2 Add(Vector2 a) {
        return Vector2{this->X+a.X, this->Y+a.Y};
    }

    Vector2 Multiply(Vector2 a) {
        return Vector2{this->X*a.X, this->Y*a.Y};
    }

    Vector2 Subtract(Vector2 a) {
        return Vector2{this->X-a.X, this->Y-a.Y};
    }

    Vector2 CrossMultiply(Vector2 a) {
        return Vector2{this->X*a.Y, this->Y*a.X};
    }
};