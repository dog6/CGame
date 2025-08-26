
#ifndef CGOL_HPP
#define CGOL_HPP

#include "../../include/game.hpp"
#include "../../include/shapes/tilemap.hpp"
#include "../../include/level.hpp"


// building computers
// somehow get all the code for CGOL in here

class ConwayGameOfLife: public ILevel{

    private:
    float tileSize = 6;
    float tileGap = 1;
    float tilemapSize;// = 24; // for dev
    int generations = 0;
    float genTime;
    bool canLoadNextGeneration = true;
    
    public:
    float delayBetweenGenerations = 0.25f;
    ConwayGameOfLife();
    ~ConwayGameOfLife();
    Camera2D cam;
    Vector2 mousePos;
    int Ygenerations;
    Scene* scene;
    Tilemap* map;
    Entity* tilemap;
    bool showColors = true;
    
    void handleCameraTranslate();
    void handleCameraZoom();
    void handleInput();
    bool NeighborAlive(Vector2 pos, Vector2 offset);
    bool NotMovingTowards(Vector2 checkingDir, Vector2 possibleDir);
    template<typename... Args>
    bool NotMovingTowards(Vector2 checkingDir, Args... possibleDirs);
    int CountNeighbors(Vector2 pos, Tilemap* map);
    int IsEdgePixel(Vector2 pos, Vector2 sz);
    void NextGeneration();
    void handleMenu(); // handles CGOL menu

    /* ILevel methods */
    const char* name = "CGOL"; // name of 'level'
    void load() override; // load all game entities
    void start() override; // called once at start of game, after load
    void update() override; // update all game entities
    void render() override; // draw things to screen
    void close() override;  // uninitialize level
    const char* getLevelName() override;

};
#endif