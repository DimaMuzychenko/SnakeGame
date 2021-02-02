#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Apple.h"


namespace snake
{
	class GameField : public sf::Drawable
	{
	public:
		GameField(unsigned int xFieldSize, unsigned int yFieldSize, unsigned int cellSize,
			float borderThickness, float statusBarHight);
		void OccupyCell(sf::Vector2f position);
		void FreeCell(sf::Vector2f position);
		bool IsOccupied(sf::Vector2f position);
		std::vector<sf::Vector2f> GetFreeCells();
		sf::Vector2f GetRandomFreeCell();
		void RespawnApple();
		sf::Vector2f GetCellPosition(size_t x, size_t y);
		std::pair<size_t, size_t> GetCellIndex(sf::Vector2f position);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void InitBorder(unsigned int xFieldSize, unsigned int yFieldSize,
			float borderThickness, float statusBarHight);
		void InitCells(unsigned int xFieldSize, unsigned int yFieldSize);

		unsigned int cellSize;
		snake::Apple apple;
		sf::Vector2f zeroCellPosition;
		std::vector<std::vector<bool>> occupiedCells;
		sf::RectangleShape border;
	};
}

