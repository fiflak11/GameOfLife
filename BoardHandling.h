#ifndef BOARDHANDLING_H
#define BOARDHANDLING_H
#include <vector>
#include <memory>

class BoardHandling{
    std::vector<bool> checkSurroundingCells(std::unique_ptr<std::vector<std::vector<bool>>>&, int, int);
    void boardResize();
    std::unique_ptr<std::vector<std::vector<bool>>> board;
        public:
    std::vector<std::vector<bool>> getBoard();
    void setBoard(std::vector<std::vector<bool>>);
    void printBoard();
    void turn();
    BoardHandling(int,int);
    int offset_x;
    int offset_y;
};

#endif
