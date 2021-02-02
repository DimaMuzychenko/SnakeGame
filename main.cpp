#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "GameField.h"

const unsigned int X_FIELD_SIZE = 20;
const unsigned int Y_FIELD_SIZE = 20;
const unsigned int CELL_SIZE = 20;

const int STATUS_BAR_HIGHT = CELL_SIZE * 2;
const int BORDER_THICKNESS = CELL_SIZE / 2;

int main()
{
    unsigned int xWindowSize = X_FIELD_SIZE * CELL_SIZE + BORDER_THICKNESS * 2;
    unsigned int yWindowSize = Y_FIELD_SIZE * CELL_SIZE + BORDER_THICKNESS * 2 + STATUS_BAR_HIGHT;
    sf::RenderWindow mainWindow(sf::VideoMode(xWindowSize, yWindowSize), "Snake!", sf::Style::Close);
    sf::Keyboard kb;
    snake::GameField gf(X_FIELD_SIZE, Y_FIELD_SIZE, CELL_SIZE, BORDER_THICKNESS, STATUS_BAR_HIGHT);
    


    while (mainWindow.isOpen())
    {
        sf::Event mwEvent;
        while (mainWindow.pollEvent(mwEvent))
        {
            if (mwEvent.type == sf::Event::Closed)
            {
                mainWindow.close();
            }
            if (mwEvent.type == sf::Event::MouseButtonReleased)
            {
                gf.RespawnApple();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                gf.RespawnApple();
            }
        }
        mainWindow.clear(sf::Color::Black);
        mainWindow.draw(gf);
        mainWindow.display();
    }
    return 0;
}