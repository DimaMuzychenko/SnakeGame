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
		m_firstCellPosition.x = borderThickness + cellSize / 2.f;
		m_firstCellPosition.y = statusBarHight + borderThickness + cellSize / 2.f;
		m_lastCellPosition.x = borderThickness + xFieldSize * cellSize - cellSize / 2.f;
		m_lastCellPosition.y = statusBarHight + borderThickness + yFieldSize * cellSize - cellSize / 2.f;
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
		std::pair<std::size_t, std::size_t> index;
		index = GetCellIndex(position);
		occupiedCells[index.second][index.first] = true;
	}

	void GameField::OccupyCell(const std::vector<sf::Vector2f>& positions)
	{
		std::pair<std::size_t, std::size_t> index;
		for (const auto& position : positions)
		{
			index = GetCellIndex(position);
			occupiedCells[index.second][index.first] = true;
		}
	}

	sf::Vector2f GameField::GetStartPosition()
	{
		std::size_t xIndex = occupiedCells[0].size() / 2;
		std::size_t yIndex = occupiedCells.size() / 2;
		return GetCellPosition(xIndex, yIndex);
	}

	void GameField::FreeCell(sf::Vector2f position)
	{
		std::pair<std::size_t, std::size_t> index;
		index = GetCellIndex(position);
		occupiedCells[index.second][index.first] = false;
	}

	void GameField::FreeCell(const std::vector<sf::Vector2f>& positions)
	{
		std::pair<std::size_t, std::size_t> index;
		for (const auto& position : positions)
		{
			index = GetCellIndex(position);
			occupiedCells[index.second][index.first] = false;
		}
	}

	bool GameField::IsCellExists(sf::Vector2f position)
	{
		std::pair<size_t, size_t> index;
		try
		{
			index = GetCellIndex(position);
		}
		catch (std::exception& ex)
		{
			return false;
		}
		return true;
	}

	bool GameField::IsOccupied(sf::Vector2f position)
	{
		std::pair<size_t, size_t> index = GetCellIndex(position);		
		return occupiedCells[index.second][index.first];
	}

	sf::Vector2f GameField::GetCellPosition(size_t x, size_t y)
	{
		if (x > occupiedCells[0].size() || y > occupiedCells.size())
		{
			throw std::exception("Cell's index is not correct!");
		}
		return sf::Vector2f(m_firstCellPosition.x + x * cellSize, m_firstCellPosition.y + y * cellSize);
	}

	std::pair<size_t, size_t> GameField::GetCellIndex(sf::Vector2f position)
	{
		std::pair<size_t, size_t> index;

		if (position.x >= m_firstCellPosition.x && position.y >= m_firstCellPosition.y)
		{
			if (position.x <= m_lastCellPosition.x && position.y <= m_lastCellPosition.y)
			{
				position.x -= m_firstCellPosition.x;
				position.y -= m_firstCellPosition.y;
				float x = position.x / cellSize;
				float y = position.y / cellSize;
				if ((x - trunc(x) == 0.f && y - trunc(y) == 0.f))
				{
					index.first = (std::size_t)x;
					index.second = (std::size_t)y;
					return index;
				}				
			}
		}
		throw std::exception("Cell's position is not correct!");
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
		unsigned int r = rand();
		sf::Vector2f randomCell = freeCells[freeCells.size() * r / RAND_MAX];
		return randomCell;
	}	

	void GameField::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(border, states);
	}
}