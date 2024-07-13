#include "game.h"
#include "raylib.h"

Game::Game()
{
    
}

Game::~Game()
{

}

void Game::init()
{
    // initialize game state
    // draw this in Figma first
    gs.p1y = 220;
    gs.p2y = 220;
    gs.p1dy = 0;
    gs.p2dy = 0;
    gs.bx = 392;
    gs.by = 292;

    // starts in upper left direction 
    gs.bdx = -VELOCITY/2;
    gs.bdy = -VELOCITY/2;

    gs.p1score = 0;
    gs.p2score = 0;

    // raylib init
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong Game");
    SetTargetFPS(FRAMES_PER_SECOND);

    loop();
}

void Game::loop()
{
    while(!WindowShouldClose())
    {
        update();
        render();
    }
    close();
}

void Game::update()
{
    handleInputs();
    checkForCollisions();
    updatePositions();
}

void Game::render()
{
    BeginDrawing();
        ClearBackground(BLACK);

        // score
        DrawText(TextFormat("%d", gs.p1score), P1_X + (PADDLE_WIDTH * 2), 64, PADDLE_WIDTH, WHITE);
        DrawText(TextFormat("%d", gs.p2score), P2_X - (PADDLE_WIDTH * 2), 64, PADDLE_WIDTH, WHITE);

        // paddles
        DrawRectangle(P1_X, gs.p1y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
        DrawRectangle(P2_X, gs.p2y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);

        // ball
        DrawRectangle(gs.bx, gs.by, BALL_SIZE, BALL_SIZE, WHITE);


    EndDrawing();
}

void Game::close()
{
    CloseWindow();
}

void Game::handleInputs()
{
    if(IsKeyDown(KEY_W))
        gs.p1dy = -VELOCITY;
    else if(IsKeyDown(KEY_S))
        gs.p1dy = VELOCITY;
    else
        gs.p1dy = 0;

    if(IsKeyDown(KEY_UP))
        gs.p2dy = -VELOCITY;
    else if(IsKeyDown(KEY_DOWN))
        gs.p2dy = VELOCITY;
    else
        gs.p2dy = 0;
}

void Game::checkForCollisions()
{
    // hits top or bottom side
    if(gs.by < 0 || gs.by + BALL_SIZE > SCREEN_HEIGHT) gs.bdy *= -1;

    Rectangle player1 = { P1_X, gs.p1y + gs.p1dy, PADDLE_WIDTH, PADDLE_HEIGHT };
    Rectangle player2 = { P2_X, gs.p2y + gs.p1dy, PADDLE_WIDTH, PADDLE_HEIGHT };
    Rectangle ball = { gs.bx, gs.by, BALL_SIZE, BALL_SIZE };

    // paddle can't be out of bounds
    if(gs.p1y + gs.p1dy < 0 || gs.p1y + gs.p1dy + PADDLE_HEIGHT > SCREEN_HEIGHT) gs.p1dy = 0;
    if(gs.p2y + gs.p2dy < 0 || gs.p2y + gs.p2dy + PADDLE_HEIGHT > SCREEN_HEIGHT) gs.p2dy = 0;

    // ball bounces off of paddle when hit from the left or right
    if(CheckCollisionRecs(player1, ball) || CheckCollisionRecs(player2, ball))
    {
        gs.bdx *= -1;
    }
}

void Game::updatePositions()
{
    gs.bx += gs.bdx;
    gs.by += gs.bdy;

    gs.p1y += gs.p1dy;
    gs.p2y += gs.p2dy;
}