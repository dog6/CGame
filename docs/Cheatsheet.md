# __Classes__

  # Game (Non-static class)

  __methods__
  - <void> run()      // Initializes the game loop
  - <void> start()    // called once at start of game
  - <void> update()   // called every frame
  - <void> draw()     // called every frame between `BeginDraw()` and `EndDraw()` raylib methods
  - <void> close()    // called once before game close
  # Scene (Non-static class)

  __methods__
  - <void> render()                   // renders all entities in scene to screen
  - <void> update()                   // updates all entities in scene
  - <void> addEntity()                // adds entity to scene
  - <void> addEntities()              // adds multiple entites to scene
  - <void> setGravity(Vector2 force)  // sets gravity for scene
  - <int> getEntityCount()            // returns number of entities in scene
  # Entity (Non-static class)
  __methods__
  - <void> draw()                                   // draw entity to screen
  - <void> update(float dt, Vector2 gravity)        // update entity
  - <void> handleCollision(vector<Entity> entities) // handle entity collisions

  __properties__
  - <string> name             // name of entity (for logging)
  - <EntityType> entityType   // type of entity (unused atm)
  - <Rigidbody*> body         // pointer to rigidbody
  - <IShape*> shape           // pointer to shape
  # IShape (Interface)
  
  __methods__
  - <void> setVisible(bool visible) // set visible property
  - <bool> isVisible()              // get visible property
  - <void> draw(Vector2 position)   // draw shape at given position
  - <void> setSize(Vector2 size)    // set size of shape
  - <Vector2> getSize()             // get size of shape
  - <Color> getColor()              // get color of shape
  - <float> sizeToRadius()          // convert `<vector2> size` to `<float> radius`
  # Rigidbody (Non-static class)
  
  __methods__
  - <void> update(float dt, Vector2 force)  // update physics of body

  __properties__
  - <bool> isKinematic              // set to true if body is not affected by external forces
  - <float> mass                    // mass of body
  - <Vector2> position              // position of body
  - <Vector2> velocity              // velocity of body
  - <Vector2> acceleration          // acceleration of body
  - <Vector2> force                 // forces acting on body

# __Helper Classes__

  # Smallmath (static class)

  __methods__
  <float> sizeToRadius(Vector2 v) // converts width and height to radius ( for equidistant shapes )
  <Vector2> radiusToSize(float r) // converts radius to width and height ( x == y )

# __Shapes__

  # Rectangle (Rect)
  - Uses `DrawRectangleV()` from raylib
  - <Vector2> size
  - <Color> color
  - <bool> isVisible
  # Box
  - Uses `DrawPoly()` from raylib
  - <float> size
  - <Color> color
  - <bool> isVisible
  # Ellipse
  - Uses `DrawEllipse()` from raylib
  - Vector2 size, Color color, bool isVisible
  # Circle
  - Uses `DrawPoly()` from raylib
  - <float> radius
  - <Color> color
  - <bool> isVisible
  # Tile (could use second look)
  - Uses rect.Draw() from `rectangle.hpp` (Rect)
  - <float> size
  - <Vector2> position
  - <bool> isVisible
  # Tilemap
  - Uses `tile.Draw()` from `tile.hpp` (Tile)
  - <Vector2> position
  - <Vector2> size
  - <Vector2> tileSize
  - <vector<Tile>> tileData
  - <vector<bool>> tileVisible
