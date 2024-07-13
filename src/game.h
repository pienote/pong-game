#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

// window constants
const int FRAMES_PER_SECOND = 60;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// game constants
const int PADDLE_WIDTH = 40;
const int PADDLE_HEIGHT = 160;
const int BALL_SIZE = 16;
const int P1_X = 64;
const int P2_X = 800 - 64 - PADDLE_WIDTH;
const int VELOCITY = 4;

struct GameState
{
    int p1y, p2y;
    int p1dy, p2dy;
    int bx, by;
    int bdx, bdy;
    int p1score, p2score;
};

class Game
{
    public:
        Game();
        ~Game();

        void init();
        void loop();
        void update();
        void render();
        void close();

        void handleInputs();
        void checkForCollisions();
        void updatePositions();
	private:
        GameState gs;
};

#endif
