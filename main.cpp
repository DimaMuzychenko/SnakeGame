#include <SFML/Graphics.hpp>
#include "GameConfig.h"
#include "Game.h"



int main()
{
    sf::RenderWindow mainWindow(sf::VideoMode(X_WINDOW_SIZE, Y_WINDOW_SIZE), "Snake", sf::Style::Close);
    while (mainWindow.isOpen())
    {
        snake::Game game(mainWindow);
        game.StartNewGame();
    }
    return 0;
}