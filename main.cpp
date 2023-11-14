#include <iostream>
#include "Maze.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int iSecret;
    srand(time(NULL));
    iSecret = rand() % 10 + 1;

    if (argc < 4)
    {
        Maze myMaze(400, 400, 10, iSecret);
        myMaze.Run();
    }
    else
    {
        Maze myMaze(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), iSecret);
        myMaze.Run();
    }

    return 0;
}
