#include "GameOfLife.h"
#include "BoardHandling.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

void GameOfLife::start(){
    int rectSize{20}, x{0}, y{0}, xCells={80}, yCells{45};
    int x_offset{0}, y_offset{0}; //these var are for keyboard navigation
    BoardHandling board{xCells,yCells};

    board.setBoard(this->getBoard(xCells,yCells,rectSize)); //player fill board here

    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");
    window.setFramerateLimit(10);
    sf::RectangleShape cellRect(sf::Vector2f(rectSize, rectSize));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.key.code==sf::Keyboard::W && event.type==sf::Event::KeyPressed)
                y_offset++;
            if (event.key.code==sf::Keyboard::S && event.type==sf::Event::KeyPressed)
                y_offset--;
            if (event.key.code==sf::Keyboard::D && event.type==sf::Event::KeyPressed)
                x_offset--;
            if (event.key.code==sf::Keyboard::A && event.type==sf::Event::KeyPressed)
                x_offset++;
        }

        for(auto line : board.getBoard())
        {
            for(auto cell : line)
            {
                if(cell)
                {
                    cellRect.setFillColor(sf::Color::Green);
                    cellRect.setPosition(sf::Vector2f(x*rectSize+(board.offset_x*rectSize)+x_offset*rectSize,y*rectSize+(board.offset_y*rectSize)+y_offset*rectSize));
                    window.draw(cellRect);
                }
                x++;
            }
            x=0; y++;
        }
        y=0;
        board.turn();
        window.display();
        Sleep(100);
        window.clear();
    }
}
std::vector<std::vector<bool>> GameOfLife::getBoard(int x,int y,int rectSize){
    std::vector<std::vector<bool>> tempBoard;
    std::vector<bool> line;
    for(int i{0}; i<x; i++)
        line.push_back(false);
    for(int i{0}; i<y; i++)
        tempBoard.push_back(line);

    sf::RenderWindow window(sf::VideoMode(rectSize*x, rectSize*y), "SFML works!");
    sf::RectangleShape cellRect(sf::Vector2f(rectSize, rectSize));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
                return tempBoard;
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                int tempY = sf::Mouse::getPosition(window).y/20,tempX = sf::Mouse::getPosition(window).x/20;
                if(tempBoard[tempY][tempX])
                    tempBoard[tempY][tempX]=false;
                else
                    tempBoard[tempY][tempX]=true;
            }
        }

        window.clear();
        for(auto l : tempBoard)
        {
            for(auto cell : l)
            {
                if(cell)
                {
                    cellRect.setFillColor(sf::Color::Green);
                    cellRect.setPosition(sf::Vector2f(x*rectSize,y*rectSize));
                    window.draw(cellRect);
                }
                x++;
            }
            x=0; y++;
        }
        y=0;
        window.display();
    }
}
