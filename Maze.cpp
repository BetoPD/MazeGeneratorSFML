#include "Maze.h"

Maze::Maze(int Width, int Height)
{
    // Dimensiones
    width = Width;
    height = Height;

    // Creando la Pantalla
    mWindow.create(sf::VideoMode(Width, Height, 32), "Maze");

    // Llenando el vector de celdas
    myCells = new Maze::Cell **[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        myCells[i] = new Cell *[SIZE];
        for (int j = 0; j < SIZE; j++)
        {
            myCells[i][j] = new Cell(j, i);
        }
    }

    // Random Seed
    std::srand(10);
}

void Maze::Run()
{

    while (mWindow.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Maze::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Maze::update()
{

    int deltaX, deltaY;

    std::stack<Maze::Cell *> pila;

    Maze::Cell *current = myCells[0][0];
    Maze::Cell *next = NULL;

    current->visited = true;

    pila.push(current);

    while (!pila.empty())
    {
        next = getRandomNeighbor(current->x, current->y);

        if (next != NULL)
        {
            deltaX = next->x - current->x;
            deltaY = next->y - current->y;
            next->visited = true;
            RemoveWalls(current, next, deltaX, deltaY);
            current = next;
            pila.push(current);
        }
        else
        {
            current = pila.top();
            pila.pop();
        }
    }
}

void Maze::render()
{
    mWindow.clear();
    Draw();
    mWindow.display();
}

void Maze::Draw()
{
    int cellWidth = WIDTH / SIZE;
    int cellHeight = HEIGHT / SIZE;
    int tempX, tempY;
    int borderWidth = 3;

    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            // Pone las pocisiones en x & y de el rectángulo, luego checa si ya fue visitado, si ya fue visitado, lo pinta de un color diferente
            tempX = (x * cellWidth);
            tempY = (y * cellHeight);
            myCells[y][x]->SetPosition(tempX, tempY);
            myCells[y][x]->SetDimentions(cellWidth, cellHeight);

            if (!myCells[y][x]->visited)
            {
                myCells[y][x]->rectangle.setFillColor(sf::Color::Green);
            }
            else
            {
                myCells[y][x]->rectangle.setFillColor(sf::Color::Magenta);
            }

            mWindow.draw(myCells[y][x]->rectangle);

            // Dibujar los Muros de cada celda

            if (!myCells[y][x]->neighbors["top"])
            {
                sf::RectangleShape top(sf::Vector2f(cellWidth, borderWidth));
                top.setPosition(tempX, tempY);
                top.setFillColor(sf::Color::Blue);
                mWindow.draw(top);
            }

            if (!myCells[y][x]->neighbors["bottom"])
            {
                sf::RectangleShape bottom(sf::Vector2f(cellWidth, borderWidth));
                bottom.setPosition(tempX, tempY + cellHeight);
                bottom.setFillColor(sf::Color::Blue);
                mWindow.draw(bottom);
            }

            if (!myCells[y][x]->neighbors["right"])
            {
                sf::RectangleShape right(sf::Vector2f(cellWidth, borderWidth));
                right.setPosition(tempX + cellWidth, tempY);
                right.rotate(90);
                right.setFillColor(sf::Color::Blue);
                mWindow.draw(right);
            }

            if (!myCells[y][x]->neighbors["left"])
            {
                sf::RectangleShape left(sf::Vector2f(cellWidth, borderWidth));
                left.setPosition(tempX, tempY + cellHeight);
                left.rotate(-90);
                left.setFillColor(sf::Color::Blue);
                mWindow.draw(left);
            }
        }
    }
}

Maze::Cell *Maze::getRandomNeighbor(int x, int y)
{

    std::vector<Maze::Cell *> neighbors;

    if (y - 1 >= 0 && y - 1 < SIZE)
    {
        Maze::Cell *top = myCells[y - 1][x];

        if (!top->visited)
        {
            neighbors.push_back(top);
        }
    }

    if (y + 1 < SIZE && y + 1 >= 0)
    {
        Maze::Cell *bottom = myCells[y + 1][x];
        if (!bottom->visited)
        {
            neighbors.push_back(bottom);
        }
    }

    if (x + 1 < SIZE && x + 1 >= 0)
    {
        Maze::Cell *right = myCells[y][x + 1];
        if (!right->visited)
        {
            neighbors.push_back(right);
        }
    }

    if (x - 1 < SIZE && x - 1 >= 0)
    {
        Maze::Cell *left = myCells[y][x - 1];

        if (!left->visited)
        {
            neighbors.push_back(left);
        }
    }

    int random = 0 + (rand() % neighbors.size());

    if (neighbors.size() > 0)
    {
        return neighbors[random];
    }

    return NULL;
}

void Maze::RemoveWalls(Maze::Cell *current, Maze::Cell *next, int deltaX, int deltaY)
{
    if (deltaX == -1)
    {
        current->neighbors["left"] = true;
        next->neighbors["right"] = true;
        return;
    }
    else if (deltaX == 1)
    {
        current->neighbors["right"] = true;
        next->neighbors["left"] = true;
        return;
    }
    else if (deltaY == -1)
    {
        current->neighbors["top"] = true;
        next->neighbors["bottom"] = true;
        return;
    }
    else
    {
        current->neighbors["bottom"] = true;
        next->neighbors["top"] = true;
        return;
    }
}
