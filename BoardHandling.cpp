#include "BoardHandling.h"
#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>

BoardHandling::BoardHandling(int x, int y){
    std::vector<std::vector<bool>> b;
    std::vector<bool> line;
    for(int i{0}; i<x; i++)
        line.push_back(false);
    for(int i{0}; i<y; i++)
        b.push_back(line);
    this->board = std::make_unique<std::vector<std::vector<bool>>>(b);
    this->offset_x=0;
    this->offset_y=0;
}
void BoardHandling::printBoard(){
    std::cout<<"= = = = = = ="<<std::endl;
    for(auto line : *(this->board))
    {
        for(auto cell : line)
            std::cout<<cell<<" ";
        std::cout<<std::endl;
    }
}
std::vector<bool> BoardHandling::checkSurroundingCells(std::unique_ptr<std::vector<std::vector<bool>>>& tempBoard, int x, int y){
    std::vector<bool> surrCells;
    int xB[8] = {x-1, x, x+1, x-1, x+1, x-1, x, x+1}, yB[8] = {y-1, y-1, y-1, y, y, y+1, y+1, y+1};
    for(int i{0}; i<8; i++){
        try{surrCells.push_back((*tempBoard).at(yB[i]).at(xB[i]));}
        catch (const std::out_of_range& e) {}
    }
    return surrCells;
}
void BoardHandling::boardResize(){
    for(auto cell : (*(this->board))[0]) //ADD TOP ROW
    {
        if(cell)
        {
            std::vector<bool> line;
            for(int i{0}; i<((*(this->board))[0]).size();i++)
                line.push_back(false);
            (*(this->board)).insert((*(this->board)).begin(),line);
            (this->offset_y)--;
            break;
        }
    }
    for(auto cell : (*(this->board))[(*(this->board)).size()-1]) //ADD BOTTOM ROW
    {
        if(cell)
        {
            std::vector<bool> line;
            for(int i{0}; i<((*(this->board))[0]).size();i++)
                line.push_back(false);
            (*(this->board)).push_back(line);
            break;
        }
    }
    for(auto line : *(this->board))//ADD LEFT COLUMN
    {
        if(line[0])
        {
            for(int i{0}; i<(*(this->board)).size();i++)
                (*(this->board))[i].insert(((*(this->board))[i]).begin(),false);
            (this->offset_x)--;
            break;
        }
    }
    for(auto line : *(this->board))//ADD RIGHT COLUMN
    {
        if(line[(*(this->board))[0].size()-1])
        {
            for(int i{0}; i<(*(this->board)).size();i++)
                (*(this->board))[i].push_back(false);
            break;
        }
    }
    if( (*(this->board)).size()>2 )
    {
        //REMOVE TOP ROW
        if(!(std::count((*(this->board))[1].begin(),(*(this->board))[1].end(),true) || std::count((*(this->board))[0].begin(),(*(this->board))[0].end(),true)))
        {
            (*(this->board)).erase((*(this->board)).begin());
            (this->offset_y)++;
        }
        //REMOCE BOTTOM ROW
        if(!(std::count((*(this->board))[(*(this->board)).size()-1].begin(),(*(this->board))[(*(this->board)).size()-1].end(),true) || std::count((*(this->board))[(*(this->board)).size()-2].begin(),(*(this->board))[(*(this->board)).size()-2].end(),true)))
        {
            (*(this->board)).pop_back();
        }
    }
    if( (*(this->board))[0].size()>2 )
    {
        //REMOVE LEFT COLUMN
        std::vector<bool> temp;
        for(auto line : *(this->board)){
            temp.push_back(line[0]); temp.push_back(line[1]);}
        if(!(std::count(temp.begin(),temp.end(),true)))
        {
            for(int i{0}; i<(*(this->board)).size();i++)
                (*(this->board))[i].erase((*(this->board))[i].begin());
            (this->offset_x)++;
        }
        temp.clear();
        //REMOVE RIGHT COLUMN
        for(auto line : *(this->board)){
            temp.push_back(line[(*(this->board))[0].size()-1]); temp.push_back(line[(*(this->board))[0].size()-2]);}
        if(!(std::count(temp.begin(),temp.end(),true)))
        {
            for(int i{0}; i<(*(this->board)).size();i++)
                (*(this->board))[i].pop_back();
        }
    }
}
void BoardHandling::turn(){
    this->boardResize();
    std::vector<std::vector<bool>> newBoard = *(this->board);
    int x{0},y{0};
    for(auto line : *(this->board))
    {
        for(auto cell : line)
        {
            std::vector<bool> surrCells = this->checkSurroundingCells(this->board,x,y);
            int aliveCells {0};
            for(auto c : surrCells)
            {
                if(c)
                    aliveCells++;
            }
            if(cell && (aliveCells==2 || aliveCells==3))
                newBoard[y][x]=true;
            else if(!cell && aliveCells==3)
                newBoard[y][x]=true;
            else
                newBoard[y][x]=false;
            x++;
        }
        y++; x=0;
    }
    this->board=std::make_unique<std::vector<std::vector<bool>>>(newBoard);
}
std::vector<std::vector<bool>> BoardHandling::getBoard(){
    return *(this->board);
}
void BoardHandling::setBoard(std::vector<std::vector<bool>> newBoard){
    this->board = std::make_unique<std::vector<std::vector<bool>>>(newBoard);
}
