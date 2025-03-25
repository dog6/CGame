#include "../include/game.hpp"
#include "../include/entity.hpp"
#include "../include/shapes/rectangle.hpp"
#include "../include/shapes/ellipse.hpp"

Entity::Entity(string name, Vector2 position, float rot, bool enabled, bool hasCollider){
    TraceLog(LOG_INFO, string("Created entity named " + name).c_str());
    this->name = name;
    this->body = new Rigidbody(position);
    this->isEnabled = enabled;
    this->shape = nullptr;
    this->rotation = rot;
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

float bounceStrength = 0.4;
void Entity::collideWithCameraBorders() {

    if (collideWithCamera){
        vector<Vector2> verts = this->shape->getVertices(this->body->position);
        for (int v = 0; v < verts.size(); v++){

            if (verts[v].x >= screenWidth){
                body->position.x -= Vector2Distance(verts[v], Vector2{screenWidth, verts[v].y});
                body->velocity.x *= -bounceStrength;
            }
            if (verts[v].x <= 0){
                body->position.x += Vector2Distance(verts[v], Vector2{0, verts[v].y});
                body->velocity.x *= -bounceStrength;
            }

            if (verts[v].y >= screenHeight){
                body->position.y -= Vector2Distance(verts[v], Vector2{verts[v].x, screenHeight});
                body->velocity.y *= -bounceStrength;
            }
            if (verts[v].y <= 0){
                body->position.y += Vector2Distance(verts[v], Vector2{verts[v].x, 0});
                body->velocity.y *= -bounceStrength;
            }


        }

        /*
        // Left of camera
        if (body->position.x-(shape->getSize().x) <= 0){
            body->position.x = (shape->getSize().x);
            body->velocity.x *= -bounceStrength;
        }

        // Right of camera
        if (body->position.x+(shape->getSize().x) >= screenWidth){
            body->position.x = screenWidth-(shape->getSize().x);
            body->velocity.x *= -bounceStrength;
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
        */
    }

}

void Entity::setRotation(float r){
    this->rotation = r;
    // Rotate(r);
}

float Entity::getRotation(){ return this->rotation; }


void Entity::handleCollision(vector<Entity> entities){

    // for each entity
    for (int i = 0; i < entities.size(); i++){
        // Logically, only things with positions (therefore rigidbodies) can have collisions
        if (&entities[i] == this|| entities[i].body == nullptr) {
            continue; // don't collide with self
        }

        DrawLineV(entities[i].body->position, this->body->position, RED);
        // Handle collision (SAT)
        // Draw ray
        // colA = this->body->position;
        // colB = entities[i].body->position;
        // DrawLineV(entities[i].body->position, this->body->position, RED);

   
    }

}


// draw entity shape
void Entity::draw(){
    // DrawLineV(colA, colB, RED); // draw line between entites being checked for collision
    if (shape != nullptr){
        shape->draw(body->position, this->rotation);
    }else {
        TraceLog(LOG_INFO, "Entity missing shape");
    }
}