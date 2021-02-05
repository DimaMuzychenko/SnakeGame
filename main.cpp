#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "GameField.h"
#include "Snake.h"
#include "GameConfig.h"
#include "CollisionManager.h"
#include "OverlayScreen.h"
#include <chrono>
#include <thread>



int main()
{
    sf::RenderWindow mainWindow(sf::VideoMode(X_WINDOW_SIZE, Y_WINDOW_SIZE), "Snake", sf::Style::Close);
    sf::Keyboard kb;
    snake::GameField gf(X_FIELD_SIZE, Y_FIELD_SIZE, CELL_SIZE, BORDER_THICKNESS, STATUS_BAR_HIGHT);
    snake::Snake snake(gf.GetStartPosition());
    snake::Apple apple(gf.GetRandomFreeCell());
    snake::CollisionManager cm;
    sf::Clock clock;

    snake::OverlayScreen gameOverScreen("Game over!");
    snake::OverlayScreen pauseScreen("Pause");
    snake::OverlayScreen guideScreen("Press any arrow to start", 
        {X_WINDOW_SIZE / 2.f, Y_WINDOW_SIZE / 4.f * 3});

    bool pause = false;
    bool guide = false;
    bool gameOver = false;

    while (mainWindow.isOpen())
    {
        sf::Event mwEvent;
        while (mainWindow.pollEvent(mwEvent))
        {
            if (mwEvent.type == sf::Event::Closed)
            {
                mainWindow.close();
            }
            if (mwEvent.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {

                    if (!pause && !guide && !gameOver)
                    {
                        snake.ChangeDirection(DIRECT_UP);
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    if (!pause && !guide && !gameOver)
                    {
                        snake.ChangeDirection(DIRECT_RIGHT);
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    if (!pause && !guide && !gameOver)
                    {
                        snake.ChangeDirection(DIRECT_DOWN);
                    }                    
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    if (!pause && !guide && !gameOver)
                    {
                        snake.ChangeDirection(DIRECT_LEFT);
                    }                    
                }
            }            
        }
        if (cm.AppleCollision(snake, apple))
        {
            apple.SetPosition(gf.GetRandomFreeCell());
            snake.AddBodyPart();
        }
        if (cm.BorderCollision(snake, gf) || cm.SnakeCollision(snake))
        {
            gameOver = true;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(125));
        snake.MoveBodyParts();

        mainWindow.clear(sf::Color::Black);
        mainWindow.draw(gf);
        mainWindow.draw(apple);
        mainWindow.draw(snake);

        if (pause)
        {
            mainWindow.draw(pauseScreen);
        }
        if (gameOver)
        {
            mainWindow.draw(gameOverScreen);
        }
        if (guide)
        {
            mainWindow.draw(guideScreen);
        }

        mainWindow.display();
    }
    return 0;
}