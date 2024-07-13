#ifndef GAME_H
#define GAME_H

namespace Game
{
    struct State
    {
        int p1_y, p2_y;
        int p1_dy, p2_dy;
        int bx, by;
        int bdx, bdy;
        int p1_score, p2_score;
    };

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

    void resetPositions();
    void init();
    void loop();
    void update();
    void render();
    void close();

    void handleInputs();
    void checkForCollisions();
    void updatePositions();
};

#endif
