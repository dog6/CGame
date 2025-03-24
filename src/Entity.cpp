#include "../include/game.hpp"
#include "../include/entity.hpp"
#include "../include/shapes/rectangle.hpp"
#include "../include/shapes/ellipse.hpp"

Entity::Entity(string name, Vector2 position, bool enabled, bool hasCollider){
    this->name = name;
    this->body = new Rigidbody(position);
    this->isEnabled = enabled;
    this->shape = nullptr;
    this->hasCollider = hasCollider;
}

Entity::~Entity(){
    TraceLog(LOG_INFO, string("Destructed ~Entity() named ").append(this->name).c_str());
}

// update entity logic
void Entity::update(float dt, Vector2 forces){
    if (this->body != nullptr){
        if (collideWithCamera){ // check for collisions with camera
            this->collideWithCameraBorders();
        } 
        body->update(dt, forces); // update rigidbody physics
    }
}

float bounceStrength = 0.8;
void Entity::collideWithCameraBorders() {

    if (collideWithCamera){
        // Left of camera
        if (body->position.x-(shape->getSize().x) <= 0){
            body->position.x = (shape->getSize().x);
            body->velocity.x *= -0.5;
        }

        // Right of camera
        if (body->position.x+(shape->getSize().x) >= screenWidth){
            body->position.x = screenWidth-(shape->getSize().x);
            body->velocity.x *= -0.5;
        }

        // Top of camera
        if (body->position.y-(shape->getSize().y) <= 0){
            body->position.y = (shape->getSize().y);
            body->velocity.y *= -bounceStrength;
        }
        // Bottom of camera
        if (body->position.y+(shape->getSize().y) >= screenHeight){
            body->position.y = screenHeight-(shape->getSize().y);
            body->velocity.y *= -bounceStrength;
        }
    }

}

void handleRectangleCollisions(Entity entA, Entity entB){
    Rectangle rectA = Rect(entA.shape).toRectangle(entA.body->position);
    Rectangle rectB = Rect(entB.shape).toRectangle(entB.body->position);

    if (CheckCollisionRecs(rectA, rectB)){
        // Collision
        entA.body->velocity *= -1;
        entB.body->velocity *= -1;
    }
}

void handleCircleCollisions(Entity entA, Entity entB){

}

// A = rect, B = circle
void handleRectangleOnCircleCollisions(Entity entA, Entity entB){
    Rectangle rectA = Rect(entA.shape).toRectangle(entA.body->position);
    Ellipse ellB = Ellipse(entB.shape);

    if (entB.shape->getSize().x == entB.shape->getSize().y){
        // For true circles
        if (CheckCollisionCircleRec(entB.body->position, entB.shape->getSize().x, rectA)){
            // Collision
            entA.body->velocity *= -1;
            entB.body->velocity *= -1;
        }
    }else {
        // For ovals
    }


}

void Entity::handleCollision(vector<Entity> entities){

    // for each entity
    for (int i = 0; i < entities.size(); i++){
        if (&entities[i] == this) {
            continue; // don't collide with self
        }
        if (Vector2Distance(entities[i].body->position, this->body->position) > (entities[i].shape->getSize().x+this->shape->getSize().x+10)
        && Vector2Distance(entities[i].body->position, this->body->position) > (entities[i].shape->getSize().y+this->shape->getSize().y+10)){
            continue; // skip collision check if far apart
        }

        /*

        // Handle collision
        switch(this->entityType){
            case EntityType::Box:
                switch(entities[i].entityType){
                    case EntityType::Box:
                    handleRectangleCollisions(*this, entities[i]);
                    break;
                    case EntityType::Oval:
                                                // box, circle
                    handleRectangleOnCircleCollisions(*this, entities[i]);
                    break;
                }
            break;

            case EntityType::Oval:
                switch(entities[i].entityType){
                    case EntityType::Box:
                    // box, circle
                    handleRectangleCollisions(entities[i], *this);
                    break;
                    case EntityType::Oval:
                    handleCircleCollisions(*this, entities[i]);
                    break;
                }
            break;
        }*/

    }

}


// draw entity shape
void Entity::draw(){
    if (shape != nullptr){
        shape->draw(body->position);
    }
}