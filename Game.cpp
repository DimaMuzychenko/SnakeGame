#include "Game.h"
#include "GameConfig.h"
#include <chrono>
#include <thread>



namespace snake
{
	Game::Game(sf::RenderWindow& mainWindow)
	{
        m_mainWindow = &mainWindow;
        gameOver = false;
        gameStarted = false;
        clockRestarted = false;
        firstDirection = 0;
        gf = new GameField(X_FIELD_SIZE, Y_FIELD_SIZE, CELL_SIZE, BORDER_THICKNESS, STATUS_BAR_HIGHT);
		snake = new Snake(gf->GetStartPosition());
		apple = new Apple(gf->GetRandomFreeCell());

        gameObjects.push_back(&(*gf));
        gameObjects.push_back(&(*snake));
        gameObjects.push_back(&(*apple));
	}

    void Game::Pause()
    {
        snake::OverlayScreen pauseScreen("Pause", sf::Color(0, 0, 255, 100));
        m_mainWindow->draw(pauseScreen);
        m_mainWindow->display();
        while (m_mainWindow->isOpen())
        {
            while (m_mainWindow->pollEvent(m_event))
            {
                if (m_event.type == sf::Event::Closed)
                {
                    m_mainWindow->close(); 
                }
                if (m_event.type == sf::Event::KeyPressed)
                {
                    if (kb.isKeyPressed(sf::Keyboard::Escape))
                    {
                        return;
                    }
                }
            }
        }
    }
    void Game::GameOver()
    {
        gameOver = true;
        snake::OverlayScreen gameOverScreen("Game over!", sf::Color(255, 0, 0, 100));
        m_mainWindow->draw(gameOverScreen);
        m_mainWindow->display();
        while (m_mainWindow->isOpen())
        {
            while (m_mainWindow->pollEvent(m_event))
            {
                if (m_event.type == sf::Event::Closed)
                {
                    m_mainWindow->close();
                }
                if (m_event.type == sf::Event::KeyPressed)
                {
                    if (kb.isKeyPressed(sf::Keyboard::Enter))
                    {
                        return;
                    }
                }
            }
        }
    }
    void Game::Guide()
    {
        snake::OverlayScreen guideScreen("Press any arrow to start", sf::Color(255, 0, 0, 50));
        m_mainWindow->draw(guideScreen);
        m_mainWindow->display();
        while (m_mainWindow->isOpen())
        {
            while (m_mainWindow->pollEvent(m_event))
            {
                if (m_event.type == sf::Event::Closed)
                {
                    m_mainWindow->close();
                }
                if (m_event.type == sf::Event::KeyPressed)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    {
                        firstDirection = DIRECT_UP;
                        return;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    {
                        firstDirection = DIRECT_RIGHT;
                        return;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    {
                        firstDirection = DIRECT_DOWN;
                        return;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    {
                        firstDirection = DIRECT_LEFT;
                        return;
                    }
                }
            }
        }
    }

	void Game::StartNewGame()
	{
        UpdateScene();
        //Guide();
        //snake->ChangeDirection(firstDirection);

        while (m_mainWindow->isOpen())
        {
            while (m_mainWindow->pollEvent(m_event))
            {
                if (m_event.type == sf::Event::Closed)
                {
                    m_mainWindow->close();
                }
                if (m_event.type == sf::Event::KeyPressed)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    {
                        snake->ChangeDirection(DIRECT_UP);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    {
                        snake->ChangeDirection(DIRECT_RIGHT);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    {
                        snake->ChangeDirection(DIRECT_DOWN);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    {
                        snake->ChangeDirection(DIRECT_LEFT);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    {
                        Pause();
                    }
                }
            }

            if (!clockRestarted)
            {
                delay = delay.Zero;
                clock.restart();
                clockRestarted = true;
            }
            if (clockRestarted && clock.getElapsedTime() - delay > sf::milliseconds(200))
            {
                clockRestarted = !clockRestarted;
                
                if (cm.BorderCollision(*snake, *gf))
                {
                    snake->MoveBodyParts();
                    if (cm.BorderCollision(*snake, *gf))
                    {
                        GameOver();
                    }
                }

                snake->MoveBodyParts();

                if (cm.AppleCollision(*snake, *apple))
                {
                    apple->SetPosition(gf->GetRandomFreeCell());
                    snake->AddBodyPart();
                }
                if (cm.SnakeCollision(*snake))
                {
                    GameOver();
                }
            }          

            UpdateScene();

            if (gameOver)
                return;
        }        
	}

    void Game::UpdateScene()
    {
        m_mainWindow->clear(sf::Color::Black);
        for (const auto& obj : gameObjects)
        {
            m_mainWindow->draw(*obj);
        }
        m_mainWindow->display();
    }
}