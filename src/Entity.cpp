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
        if (doesCollideWithWindow){ // check for collisions with camera
            this->collideWithCameraBorders();
        } 
        body->update(dt, forces); // update rigidbody physics
    }

}

float bounceStrength = 0.4;
void Entity::collideWithCameraBorders() {
    if (doesCollideWithWindow){
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
    }
}

void Entity::setRotation(float r){
    this->rotation = r;
    // Rotate(r);
}

float Entity::getRotation(){ return this->rotation; }


void Entity::handleCollision(vector<Entity*> entities){

    // at least 2 entities must be in the scene for collision to happen
    if (entities.size() < 2){
        return;
    }

    for (int i = 0; i < entities.size()-1; i++){
            
            Entity* entA = entities[i];
            Entity* entB = entities[i+1];

            vector<Vector2> vertsA = entA->shape->getVertices(entA->body->position);
            vector<Vector2> vertsB = entB->shape->getVertices(entB->body->position);
            
            vector<Line> linesA = entA->shape->getLines(entA->body->position);
            vector<Line> linesB = entB->shape->getLines(entB->body->position); 

            if (&entA == &entB){
                continue; // don't collide with self
            }

            // Handle collision
            
            
            // Check all of entityA's vertices
//            for (int j = 0; j < vertsA.size(); j++){
  //              Vector2 v = vertsA[j];


                // If vertex is in entityB's shape
                /*if (CheckCollisionPointPoly(vertsA[j], vertsB.data(), vertsB.size())){
                    
                    // Collision!
                    TraceLog(LOG_INFO, "Collision occured!"); 

                    // get collision direction & distance
                    Vector2 dir = Smallmath::Vector2Direction(entA->body->position, entB->body->position); 
                    float dist = 1;
                    TraceLog(LOG_INFO, string("Direction of collision: " + to_string(dir.x) + ", " + to_string(dir.y)).c_str());
                    TraceLog(LOG_INFO, string("Distance of collision: " + to_string(dist)).c_str());
                    
                    // entA immovable
                    if (entA->body->isKinematic){
                        // move entB
                        entB->body->position = Vector2Add(dir*dist, entB->body->position);
                    }else {
                        // move entA
                        entA->body->position = Vector2Add(entA->body->position, dir*dist);
                    }


                }*/

          //  }

    }

}


// draw entity shape
void Entity::draw(){
    if (shape != nullptr){
        shape->draw(body->position, this->rotation);
    }else {
        TraceLog(LOG_INFO, "Entity missing shape");
    }
}