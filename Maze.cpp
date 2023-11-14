#include "Maze.h"

Maze::Maze(int Width, int Height, int D, int seed)
{
    // Dimensiones
    width = Width - 100;
    height = Height - 100;

    // Creando la Pantalla
    mWindow.create(sf::VideoMode(Width, Height, 32), "Laberinto");

    // Dificultad
    dificulty = D;

    // Llenando el vector de celdas
    myCells = new Maze::Cell **[dificulty];

    for (int i = 0; i < dificulty; i++)
    {
        myCells[i] = new Cell *[dificulty];
        for (int j = 0; j < dificulty; j++)
        {
            myCells[i][j] = new Cell(j, i);
        }
    }

    // Random Seed
    std::srand(seed);
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

    AStarAlgorithm(myCells[0][0], myCells[dificulty - 1][dificulty - 1]);
}

void Maze::render()
{
    mWindow.clear();
    Draw();
    mWindow.display();
}

void Maze::Draw()
{
    int cellWidth = width / dificulty;
    int cellHeight = height / dificulty;
    int tempX, tempY;
    int borderWidth = ((3 * 10) / dificulty) * width / 400;
    borderWidth = borderWidth > 1 ? borderWidth : 1;

    for (int y = 0; y < dificulty; y++)
    {
        for (int x = 0; x < dificulty; x++)
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

    // Dibujar el camino de A* Star

    Maze::Cell *caminito = myCells[dificulty - 1][dificulty - 1];

    while (caminito->parent != NULL)
    {
        caminito->rectangle.setFillColor(sf::Color::Red);
        caminito->SetDimentions(cellWidth / 4, cellHeight / 4);
        caminito->SetPosition(caminito->rectangle.getPosition().x + cellWidth / 2, caminito->rectangle.getPosition().y + cellHeight / 2);
        mWindow.draw(caminito->rectangle);
        caminito = caminito->parent;
    }
}

Maze::Cell *Maze::getRandomNeighbor(int x, int y)
{

    std::vector<Maze::Cell *> neighbors;

    if (y - 1 >= 0 && y - 1 < dificulty)
    {
        Maze::Cell *top = myCells[y - 1][x];

        if (!top->visited)
        {
            neighbors.push_back(top);
        }
    }

    if (y + 1 < dificulty && y + 1 >= 0)
    {
        Maze::Cell *bottom = myCells[y + 1][x];
        if (!bottom->visited)
        {
            neighbors.push_back(bottom);
        }
    }

    if (x + 1 < dificulty && x + 1 >= 0)
    {
        Maze::Cell *right = myCells[y][x + 1];
        if (!right->visited)
        {
            neighbors.push_back(right);
        }
    }

    if (x - 1 < dificulty && x - 1 >= 0)
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

    current->neighborsAStar.push_back(next);
    next->neighborsAStar.push_back(current);

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

void Maze::AStarAlgorithm(Maze::Cell *start, Maze::Cell *goal)
{

    start->fLocalGoal = 0;
    start->fGlobalGoal = ManhattanDistance(start->x, goal->x, start->y, goal->y);

    std::vector<Maze::Cell *> listNotTestedNodes;
    listNotTestedNodes.push_back(start);

    Maze::Cell *current = NULL;

    while (!listNotTestedNodes.empty())
    {

        Maze::Cell *aux = NULL;

        bool swapped;

        for (int i = 0; i < listNotTestedNodes.size() - 1; i++)
        {
            swapped = false;

            for (int j = 0; j < listNotTestedNodes.size() - i - 1; j++)
            {
                if (listNotTestedNodes[j]->fGlobalGoal < listNotTestedNodes[j + 1]->fGlobalGoal)
                {
                    aux = listNotTestedNodes[j + 1];
                    listNotTestedNodes[j + 1] = listNotTestedNodes[j];
                    listNotTestedNodes[j] = aux;
                    swapped = true;
                }
            }

            if (!swapped)
            {
                break;
            }
        }

        while (!listNotTestedNodes.empty() && listNotTestedNodes.back()->a_visited)
            listNotTestedNodes.pop_back();

        if (listNotTestedNodes.empty())
            break;

        current = listNotTestedNodes.back();
        current->a_visited = true;

        for (auto neighbor : current->neighborsAStar)
        {
            if (!neighbor->a_visited)
                listNotTestedNodes.push_back(neighbor);

            int possiblyLowerGoal = current->fLocalGoal + 1;

            if (possiblyLowerGoal < neighbor->fLocalGoal)
            {
                neighbor->parent = current;
                neighbor->fLocalGoal = possiblyLowerGoal;
                neighbor->fGlobalGoal = neighbor->fLocalGoal + ManhattanDistance(neighbor->x, goal->x, neighbor->y, goal->y);
            }
        }
    }
}

int Maze::ManhattanDistance(int x1, int x2, int y1, int y2)
{
    int distanceX = std::abs(x2 - x1);
    int distanceY = std::abs(y2 - y1);
    return distanceX + distanceY;
}
