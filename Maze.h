#pragma once
// Librería para las gráficas
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <iostream>
#include <stack>
#include <vector>
#include <limits>

class Maze
{

public:
    // Constructor de la clase Maze
    Maze(int, int, int, int);
    // Función para correr el programa
    void Run();

private:
    struct Cell
    {
        // Variables para la creación del mapa

        // Posición de nuestra celda en 2D
        int x;
        int y;
        // Saber si ha sido visitada para nuestro algoritmo de creación del mapa
        bool visited;
        // Diccionario, para saber cuales son sus vecinos, y donde dibuja los muros
        std::map<std::string, bool> neighbors;
        // Rectángulo de SFML
        sf::RectangleShape rectangle;

        // Variables para el algoritmo de A* Star

        std::vector<Cell *> neighborsAStar;

        // g(n) is the cost of the path from the start node to n, and h(n) is a
        // heuristic function that estimates the cost of the cheapest path from n to the goal
        int fLocalGoal;
        int fGlobalGoal;

        // Ya fue visitado en el algorimto
        bool a_visited;

        // Puntero a la celda la cual refirió a esta
        Cell *parent;

        // Constructor de la estructura, toma como parámetros la posición en el plano 2D de la celda
        Cell(int X = 0, int Y = 0)
        {
            x = X;
            y = Y;
            visited = false;
            neighbors["top"] = false;
            neighbors["bottom"] = false;
            neighbors["left"] = false;
            neighbors["right"] = false;
            fLocalGoal = std::numeric_limits<int>::max();
            fGlobalGoal = std::numeric_limits<int>::max();
            a_visited = false;
            parent = NULL;
        }

        // Crea las dimensiones del rectángulo
        void SetDimentions(int W, int H)
        {
            rectangle.setSize(sf::Vector2f(W, H));
        }

        // Posiciona el rectángulo en el plano 2D
        void SetPosition(int X, int Y)
        {
            rectangle.setPosition(sf::Vector2f(X, Y));
        }
    };

private:
    // Escucha a los eventos en la ventana, para poder ejecutar comandos y terminar el loop
    void processEvents();
    // Crea el mapa
    void update();
    // Renderiza el mapa por primera vez
    void render();
    // Maneja la lógica para la creación del mapa
    void Draw();
    // Devuelve un vecino válido de algun nodo
    Cell *getRandomNeighbor(int, int);
    // Remueve las paredes entre dos nodos
    void RemoveWalls(Maze::Cell *, Maze::Cell *, int, int);
    // Algoritmo de busqueda
    void AStarAlgorithm(Maze::Cell *, Maze::Cell *);
    // Calcular la distancia Manhattan entre dos puntos
    int ManhattanDistance(int, int, int, int);
    // Ordenar Priority Queue

private:
    // Ventana donde corre toda la lógica
    sf::RenderWindow mWindow;
    // Arreglo Bidimencional de punteros
    Maze::Cell ***myCells;
    // Alto y ancho de la ventana del programa
    int width, height;
    // Cantidad de "Cells" por laberinto
    int dificulty;
    // Goal cell
    Maze::Cell *goalCell;
};