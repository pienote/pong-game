#include <stdlib.h>
#include <time.h>

#include "game.h"

int main(int argc, char** argv)
{
    srand(time(NULL));
    Game::init();
    return 0;
}
