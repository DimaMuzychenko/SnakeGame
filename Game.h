#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionManager.h"
#include "OverlayScreen.h"


namespace snake
{
	class Game
	{
	public:
		Game(sf::RenderWindow& mainWindow);
		void StartNewGame();
		void Pause();
		void GameOver();
		void Guide();

	private:
		void UpdateScene();

		sf::RenderWindow* m_mainWindow;
		sf::Keyboard kb;
		sf::Clock clock;
		CollisionManager cm;
		sf::Event m_event;
		bool gameOver;
		bool gameStarted;
		bool clockRestarted;
		sf::Time delay;
		std::int8_t firstDirection;
		std::vector<sf::Drawable*> gameObjects;
		snake::GameField* gf;
		snake::Snake* snake;
		snake::Apple* apple;
	};
}

