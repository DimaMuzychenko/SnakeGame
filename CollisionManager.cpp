#include "CollisionManager.h"
#include "Snake.h"
#include "Apple.h"
#include "GameField.h"
#include "GameConfig.h"

namespace snake
{
	bool CollisionManager::AppleCollision(snake::Snake& snake, snake::Apple& apple)
	{
		return snake.GetNextCell() == apple.GetPosition();
	}
	bool CollisionManager::BorderCollision(snake::Snake& snake, snake::GameField& gf)
	{
		return gf.IsCellExists(snake.GetNextCell());
	}
	bool CollisionManager::SnakeCollision(snake::Snake& snake)
	{
		sf::Vector2f targetCell = snake.GetNextCell();
		for (const auto& cell : snake.GetSnakeCells())
		{
			if (cell == targetCell)
			{
				return true;
			}
		}
		return false;
	}
}