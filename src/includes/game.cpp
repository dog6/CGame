#include "../headers/game.h"
#include "../external/physac/physac.h"

int Game::bodiesCount = 0;

// Initialize physics bodies
PhysicsBody circle, ground;

/* Game start */
void Game::Start(){

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, screenTitle);
    SetTargetFPS(60);
    
    InitPhysics();
    if (!IsPhysicsEnabled()) {
        TraceLog(LOG_ERROR, "Physics failed to initialize - Check dependencies or memory allocation");
        exit(1);
    }else {
        TraceLog(LOG_INFO, "Physac initialized successfully. Bodies count: %d", GetPhysicsBodiesCount());
    }

    SetPhysicsGravity(0, 9.81);

    
    circle = CreatePhysicsBodyCircle(Vector2{screenWidth/2, screenHeight/2}, 24, 10);
    ground = CreatePhysicsBodyRectangle((Vector2){ screenWidth/2, screenHeight }, 500, 100, 10);
    ground->enabled = false;
    circle->enabled = false; // disable body state to convert it to static (no dynamics, but collisions)

}


/* Update loop */
void Game::Update(){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        CreatePhysicsBodyPolygon(GetMousePosition(), GetRandomValue(20, 80), GetRandomValue(3, 8), 10);
    else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        CreatePhysicsBodyCircle(GetMousePosition(), GetRandomValue(10, 45), 10);

    // Destroy falling physics bodies
    int bodiesCount = GetPhysicsBodiesCount();
    for (int i = bodiesCount - 1; i >= 0; i--)
    {
        PhysicsBody body = GetPhysicsBody(i);
        
        if ((body != NULL) && (body->position.y > screenHeight*2))
            DestroyPhysicsBody(body);
    }
}


/* Draw loop */
void Game::Draw(){
    ClearBackground(RAYWHITE);
    DrawFPS(20, 20);

    bodiesCount = GetPhysicsBodiesCount();
    for (int i = 0; i < bodiesCount; i++)
    {
        // Draw created physics bodies
        PhysicsBody body = GetPhysicsBody(i);

        if (body != NULL)
        {
            int vertexCount = GetPhysicsShapeVerticesCount(i);
            for (int j = 0; j < vertexCount; j++)
            {
                // Get physics bodies shape vertices to draw lines
                // Note: GetPhysicsShapeVertex() already calculates rotation transformations
                Vector2 vertexA = GetPhysicsShapeVertex(body, j);

                int jj = (((j + 1) < vertexCount) ? (j + 1) : 0);   // Get next vertex or first to close the shape
                Vector2 vertexB = GetPhysicsShapeVertex(body, jj);

                DrawLineV(vertexA, vertexB, GREEN);     // Draw a line between two vertex positions
            }
        }
    }

}


/* Game close */
void Game::Close(){
    ClosePhysics();
    CloseWindow();        // Close window and OpenGL context
}


/* Game Loop */
void Game::Run(){
    // Initialization
    Game::Start();


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        Game::Update();

        // Draw
        BeginDrawing();
        Game::Draw();
        EndDrawing();
    }

    // De-Initialization
    Game::Close();
}
