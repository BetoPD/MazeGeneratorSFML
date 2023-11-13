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
        myCells[i] = new Cell *[10];
        for (int j = 0; j < SIZE; j++)
        {
            myCells[i][j] = new Cell;
        }
    }
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
