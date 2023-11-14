#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <iostream>
#include <stack>
#include <vector>
#include <limits>

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
        int g_score;
        int f_score;
        std::map<std::string, bool> neighbors;
        sf::RectangleShape rectangle;

        Cell(int X = 0, int Y = 0)
        {
            x = X;
            y = Y;
            g_score = std::numeric_limits<int>::max();
            f_score = std::numeric_limits<int>::max();
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
    Cell *getRandomNeighbor(int, int);
    void RemoveWalls(Maze::Cell *, Maze::Cell *, int, int);
    void AStarAlgorith(Maze::Cell *, Maze::Cell *);
    int ManhattanDistance(int, int, int, int);

private:
    sf::RenderWindow mWindow;
    Maze::Cell ***myCells;
    int width, height;
};