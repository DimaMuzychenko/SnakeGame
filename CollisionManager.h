#pragma once
#include "Snake.h"
#include "Apple.h"
#include "GameField.h"

namespace snake
{
	class CollisionManager
	{
	public:
		bool AppleCollision(snake::Snake& snake, snake::Apple& apple);
		bool BorderCollision(snake::Snake& snake, snake::GameField& gf);
		bool SnakeCollision(snake::Snake& snake);
	};
}

