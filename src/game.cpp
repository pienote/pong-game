#include <raylib.h>
#include <stdlib.h>

#include "game.h"


Game::State gs; // State of the game
Rectangle topClip, bottomClip, leftGoal, rightGoal;

void Game::resetPositions()
{
    // draw this in Figma first
    gs.p1_y = 220;
    gs.p2_y = 220;
    gs.p1_dy = 0;
    gs.p2_dy = 0;
    gs.bx = 392;
    gs.by = 292;

    // starts in upper left direction 
    gs.bdx = ((rand()%VELOCITY)-(VELOCITY/2))+VELOCITY;
    gs.bdy = ((rand()%VELOCITY)-(VELOCITY/2))+VELOCITY;
}

void Game::init()
{
    // always the same for every game
    topClip.x = 0;
    topClip.y = -16;
    topClip.width = SCREEN_WIDTH;
    topClip.height = 16;

    bottomClip.x = 0;
    bottomClip.y = SCREEN_HEIGHT;
    bottomClip.width = SCREEN_WIDTH;
    bottomClip.height = 16;

    leftGoal.x = -16;
    leftGoal.y = 0;
    leftGoal.width = 16;
    leftGoal.height = SCREEN_HEIGHT;

    rightGoal.x = SCREEN_WIDTH;
    rightGoal.y = 0;
    rightGoal.width = 16;
    rightGoal.height = SCREEN_HEIGHT;


    // initialize game state
	resetPositions();

    gs.p1_score = 0;
    gs.p2_score = 0;

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
    updatePositions();
    checkForCollisions();
}

void Game::render()
{
    BeginDrawing();
        ClearBackground(BLACK);


        // paddles
        DrawRectangle(P1_X, gs.p1_y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
        DrawRectangle(P2_X, gs.p2_y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);

        // ball
        DrawRectangle(gs.bx, gs.by, BALL_SIZE, BALL_SIZE, RED);

        // score
        DrawText(TextFormat("%d", gs.p1_score), P1_X + (PADDLE_WIDTH * 2), 64, PADDLE_WIDTH, GREEN);
        DrawText(TextFormat("%d", gs.p2_score), P2_X - (PADDLE_WIDTH * 2), 64, PADDLE_WIDTH, GREEN);


    EndDrawing();
}

void Game::close()
{
    CloseWindow();
}

void Game::handleInputs()
{
    if(IsKeyDown(KEY_W))
        gs.p1_dy = -VELOCITY;
    else if(IsKeyDown(KEY_S))
        gs.p1_dy = VELOCITY;
    else
        gs.p1_dy = 0;

    if(IsKeyDown(KEY_UP))
        gs.p2_dy = -VELOCITY;
    else if(IsKeyDown(KEY_DOWN))
        gs.p2_dy = VELOCITY;
    else
        gs.p2_dy = 0;
}

void Game::checkForCollisions()
{
    Rectangle player1 = { 
		(float) P1_X,
		(float) gs.p1_y, 
		(float) PADDLE_WIDTH,
		(float) PADDLE_HEIGHT 
	};

    Rectangle player2 = {
		(float) P2_X,
		(float) gs.p2_y,
		(float) PADDLE_WIDTH,
		(float) PADDLE_HEIGHT
	};

    Rectangle ball = {
		(float) gs.bx,
		(float) gs.by,
		(float) BALL_SIZE,
		(float) BALL_SIZE
	};

    if(CheckCollisionRecs(ball, leftGoal))
    {
        gs.p2_score += 1;
        resetPositions();
        return;
    }

    if(CheckCollisionRecs(ball, rightGoal))
    {
        gs.p1_score += 1;
        resetPositions();
        return;
    }

	if(ball.y < 0 || ball.y + ball.height > SCREEN_HEIGHT)
    {
        gs.by -= gs.bdy;
        gs.bdy *= -1;
    }

    if(CheckCollisionRecs(player1, topClip) || CheckCollisionRecs(player1, bottomClip)) {
        gs.p1_y -= gs.p1_dy;
    }

    if(CheckCollisionRecs(player2, topClip) || CheckCollisionRecs(player2, bottomClip)) {
        gs.p2_y -= gs.p2_dy;
    }

    // ball bounces off of paddle when hit from the left or right
    if(CheckCollisionRecs(player1, ball) || CheckCollisionRecs(player2, ball))
    {
        gs.bx -= gs.bdx;
        int vel = ((rand()%VELOCITY)-(VELOCITY/2))+VELOCITY;
        if(gs.bdx > 0)
            gs.bdx = -vel;
        else
            gs.bdx = vel;
    }
}

void Game::updatePositions()
{
    gs.bx += gs.bdx;
    gs.by += gs.bdy;

    gs.p1_y += gs.p1_dy;
    gs.p2_y += gs.p2_dy;
}

