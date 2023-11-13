#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <iostream>

#define WIDTH 400
#define HEIGHT 400
#define SIZE 10

class Maze
{

public:
    Maze(int, int);
    void Run();

private:
    struct Cell
    {
        int x;
        int y;
        bool visited;
        std::map<std::string, bool> neighbors;
        sf::RectangleShape rectangle;

        Cell(int X = 0, int Y = 0)
        {
            x = X;
            y = Y;
            visited = false;
            neighbors["top"] = false;
            neighbors["bottom"] = false;
            neighbors["left"] = false;
            neighbors["right"] = false;
        }

        void SetDimentions(int W, int H)
        {
            rectangle.setSize(sf::Vector2f(W, H));
        }

        void SetPosition(int X, int Y)
        {
            rectangle.setPosition(sf::Vector2f(X, Y));
        }
    };

private:
    void processEvents();
    void update();
    void render();
    void Draw();

private:
    sf::RenderWindow mWindow;
    Maze::Cell ***myCells;
    int width, height;
};