#include "GameField.h"
#include <cstdlib>
#include <ctime>

namespace snake
{
	GameField::GameField(unsigned int xFieldSize, unsigned int yFieldSize, 
		unsigned int cellSize, float borderThickness, float statusBarHight)
	{
		std::srand(time(0));
		this->cellSize = cellSize;
		InitBorder(xFieldSize, yFieldSize, borderThickness, statusBarHight);
		InitCells(xFieldSize, yFieldSize);		
		zeroCellPosition.x = borderThickness + cellSize / 2.f;
		zeroCellPosition.y = statusBarHight + borderThickness + cellSize / 2.f;
		apple.SetCellSize(cellSize);
		RespawnApple();
		
	}

	void GameField::InitBorder(unsigned int xFieldSize, unsigned int yFieldSize,
		float borderThickness, float statusBarHight)
	{
		float xSize = xFieldSize * cellSize;
		float ySize = yFieldSize * cellSize;
		float xOrigin = xSize / 2;
		float yOrigin = ySize;
		float xPosition = xSize / 2 + borderThickness;
		float yPosition = ySize + borderThickness + statusBarHight;
		border.setSize(sf::Vector2f(xSize, ySize));
		border.setFillColor(sf::Color::Transparent);
		border.setOutlineThickness(borderThickness);
		border.setOutlineColor(sf::Color::White);
		border.setOrigin({ xOrigin, yOrigin });
		border.setPosition({ xPosition, yPosition });
	}

	void GameField::InitCells(unsigned int xFieldSize, unsigned int yFieldSize)
	{
		occupiedCells.resize(yFieldSize);
		for (auto& v : occupiedCells)
		{
			v.resize(xFieldSize, false);
		}
	}

	void GameField::OccupyCell(sf::Vector2f position)
	{
		float m = position.x / cellSize;
		float n = position.y / cellSize;
		if (m - trunc(m) == 0.5f && n - trunc(n) == 0.5f)
		{
			occupiedCells[trunc(n)][trunc(m)] = true;
		}
		else
		{
			std::string msg = "No cell with coordinates x = " + std::to_string(position.x) + ", y = " + std::to_string(position.y);
			throw std::exception(msg.c_str());
		}
	}

	void GameField::FreeCell(sf::Vector2f position)
	{
		float m = position.x / cellSize;
		float n = position.y / cellSize;
		if (m - trunc(m) == 0.5f && n - trunc(n) == 0.5f)
		{
			occupiedCells[trunc(n)][trunc(m)] = false;
		}
		else
		{
			std::string msg = "No cell with coordinates x = " + std::to_string(position.x) + ", y = " + std::to_string(position.y);
			throw std::exception(msg.c_str());
		}
	}

	bool GameField::IsOccupied(sf::Vector2f position)
	{
		float m = position.x / cellSize;
		float n = position.y / cellSize;
		if (m - trunc(m) == 0.5f && n - trunc(n) == 0.5f)
		{
			return occupiedCells[trunc(n)][trunc(m)];
		}
		else
		{
			std::string msg = "No cell with coordinates x = " + std::to_string(position.x) + ", y = " + std::to_string(position.y);
			throw std::exception(msg.c_str());
		}
	}

	sf::Vector2f GameField::GetCellPosition(size_t x, size_t y)
	{
		return sf::Vector2f(zeroCellPosition.x + x * cellSize, zeroCellPosition.y + y * cellSize);
	}

	std::pair<size_t, size_t> GameField::GetCellIndex(sf::Vector2f position)
	{
		std::pair<size_t, size_t> index;
		index.first = trunc(position.x / cellSize);
		index.second = trunc(position.y / cellSize);
		return index;
	}

	std::vector<sf::Vector2f> GameField::GetFreeCells()
	{
		std::vector<sf::Vector2f> freeCells;
		for (int y = 0; y < occupiedCells.size(); y++)
		{
			for (int x = 0; x < occupiedCells[0].size(); x++)
			{
				if (!occupiedCells[y][x])
				{
					freeCells.push_back(GetCellPosition(x, y));
				}
			}
		}
		return freeCells;
	}

	sf::Vector2f GameField::GetRandomFreeCell()
	{
		std::vector<sf::Vector2f> freeCells = GetFreeCells();
		rand();
		unsigned int r = rand();
		sf::Vector2f randomCell = freeCells[freeCells.size() * r / RAND_MAX];
		return randomCell;
	}

	void GameField::RespawnApple()
	{
		apple.SetPosition(GetRandomFreeCell());
	}

	void GameField::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(border, states);
		target.draw(apple, states);
	}
}