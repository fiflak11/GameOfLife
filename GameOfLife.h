#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H
#include <vector>

class GameOfLife{
    std::vector<std::vector<bool>> getBoard(int,int,int); // xSize, ySize, rectSize. There you can create the starting board
        public:
    void start();
};

#endif
