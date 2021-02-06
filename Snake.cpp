#include "Snake.h"
#include <iostream>
#include "GameConfig.h"

#pragma region RectsArray
const sf::IntRect PART_RECTS[14] = {
	{3 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE},
	{4 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE},
	{3 * SPRITE_SIZE, 1 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE},
	{4 * SPRITE_SIZE, 1 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE},
	{2 * SPRITE_SIZE, 1 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE},
	{1 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE},
	{0 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE},
	{2 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE},
	{0 * SPRITE_SIZE, 1 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE},
	{2 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE},
	{3 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE},
	{4 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE},
	{3 * SPRITE_SIZE, 3 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE},
	{4 * SPRITE_SIZE, 3 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE}
};
#pragma endregion


#pragma region BodyPartConstants
const std::int8_t HEAD_UP = 0;
const std::int8_t HEAD_RIGHT = 1;
const std::int8_t HEAD_LEFT = 2;
const std::int8_t HEAD_DOWN = 3;
const std::int8_t BODY_VECTICAL = 4;
const std::int8_t BODY_HORIZONTAL = 5;
const std::int8_t BODY_RIGHT_DOWN = 6;//
const std::int8_t BODY_LEFT_DOWN = 7;//
const std::int8_t BODY_RIGHT_UP = 8;//
const std::int8_t BODY_LEFT_UP = 9;//
const std::int8_t TAIL_UP = 10;//
const std::int8_t TAIL_LEFT = 11;
const std::int8_t TAIL_RIGHT = 12;
const std::int8_t TAIL_DOWN = 13;//
#pragma endregion


namespace snake
{
	Snake::Snake(sf::Vector2f startPosition)
	{
		setPosition(startPosition);
		if (!LoadSprites(SPRITESHEET_PATH))
		{
			std::cout << "No spritesheet found!" << std::endl;
		}
		InitSnake(startPosition);
	}

	Snake::Snake()
	{
		setPosition({0, 0});
		if (!LoadSprites(SPRITESHEET_PATH))
		{
			std::cout << "No spritesheet found!" << std::endl;
		}
	}

	void Snake::SetStartPosition(sf::Vector2f position)
	{
		setPosition(position);
		m_bodyParts[0].setPosition({position});
		m_bodyParts[1].setPosition({ position.x - CELL_SIZE, position.y });
	}

	bool Snake::LoadSprites(const std::string& filePath)
	{
		if (!m_texture.loadFromFile(filePath))
		{
			return false;
		}
		for (auto& rect : PART_RECTS)
		{
			m_sprites.push_back(sf::Sprite(m_texture, rect));
		}
		return true;
	}

	std::vector<sf::Vector2f> Snake::GetSnakeCells()
	{
		std::vector<sf::Vector2f> snakeCells;
		for (const auto& part : m_bodyParts)
		{
			snakeCells.push_back(part.getPosition());
		}
		return snakeCells;
	}

	void Snake::InitSnake(sf::Vector2f startPosition)
	{
		m_bodyParts.push_back({m_sprites[HEAD_RIGHT], startPosition});
		m_bodyParts.push_back({ m_sprites[TAIL_LEFT], {startPosition.x - CELL_SIZE, startPosition.y} });
	}

	void Snake::ChangeDirection(std::int8_t direction)
	{
		sf::Vector2f head = m_bodyParts[0].getPosition();
		sf::Vector2f next = m_bodyParts[1].getPosition();

		if (direction == 1 && !(next.y < head.y))
		{
			m_direction = direction;
		}
		else if (direction == 2 && !(next.x > head.x))
		{
			m_direction = direction;
		}
		else if (direction == 3 && !(head.y < next.y))
		{
			m_direction = direction;
		}
		else if (direction == 4 && !(head.x > next.x))
		{
			m_direction = direction;
		}
	}

	std::int8_t Snake::GetDirection()
	{
		return m_direction;
	}

	sf::Vector2f Snake::GetDirectionVector()
	{
		sf::Vector2f directionVector(0, 0);
		switch (m_direction)
		{
		case DIRECT_UP:
			directionVector.y -= CELL_SIZE;
			break;
		case DIRECT_RIGHT:
			directionVector.x += CELL_SIZE;
			break;
		case DIRECT_DOWN:
			directionVector.y += CELL_SIZE;
			break;
		case DIRECT_LEFT:
			directionVector.x -= CELL_SIZE;
			break;
		}
		return directionVector;
	}

	sf::Vector2f Snake::GetNextCell()
	{
		sf::Vector2f nextPosition;
		sf::Vector2f headPosition = m_bodyParts[0].getPosition();
		for (int i = 0; i < 4; i++)
		{
			if (m_bodyParts[0].GetSprite().getTextureRect() == PART_RECTS[i])
			{
				switch (i)
				{
				case 0:
					nextPosition.x = headPosition.x;
					nextPosition.y = headPosition.y - CELL_SIZE;
					break;
				case 1:
					nextPosition.x = headPosition.x + CELL_SIZE;
					nextPosition.y = headPosition.y;
					break;
				case 2:
					nextPosition.x = headPosition.x - CELL_SIZE;
					nextPosition.y = headPosition.y;
					break;
				case 3:
					nextPosition.x = headPosition.x;
					nextPosition.y = headPosition.y + CELL_SIZE;
					break;
				}
				break;
			}
		}
		return nextPosition;
	}

	void Snake::MoveBodyParts()
	{
		if (m_direction != 0)
		{
			for (int i = m_bodyParts.size() - 1; i > 0 ; i--)
			{
				m_bodyParts[i].setPosition(m_bodyParts[i - 1].getPosition());
			}
			m_bodyParts[0].setPosition(m_bodyParts[0].getPosition() + GetDirectionVector());
		}
		UpdateSprites();
	}

	void Snake::AddBodyPart()
	{
		m_bodyParts.insert(++m_bodyParts.begin(), SnakePart(m_sprites[BODY_VECTICAL], m_bodyParts[0].getPosition()));
		m_bodyParts[0].setPosition(GetNextCell());
		UpdateSprites();
	}

	void Snake::UpdateSprites()
	{
		UpdateHeadSprite();
		for (std::size_t i = 1; i < m_bodyParts.size() - 1; i++)
		{
			UpdateBodySprite(i);
		}
		UpdateTailSprite();
	}

	void Snake::UpdateHeadSprite()
	{
		switch (m_direction)
		{
		case DIRECT_UP:
			m_bodyParts[0].SetSprite(m_sprites[HEAD_UP]);
			break;
		case DIRECT_RIGHT:
			m_bodyParts[0].SetSprite(m_sprites[HEAD_RIGHT]);
			break;
		case DIRECT_DOWN:
			m_bodyParts[0].SetSprite(m_sprites[HEAD_DOWN]);
			break;
		case DIRECT_LEFT:
			m_bodyParts[0].SetSprite(m_sprites[HEAD_LEFT]);
			break;
		}
	}

	void Snake::UpdateBodySprite(std::size_t index)
	{
		sf::Vector2f previous = m_bodyParts[index-1].getPosition();
		sf::Vector2f current = m_bodyParts[index].getPosition();
		sf::Vector2f next = m_bodyParts[index+1].getPosition();

		if (previous.x == next.x)
		{
			//BODY_VERTICAL
			m_bodyParts[index].SetSprite(m_sprites[BODY_VECTICAL]);
		}
		else if (previous.y == next.y)
		{
			//BODY_HORIZONTAL
			m_bodyParts[index].SetSprite(m_sprites[BODY_HORIZONTAL]);
		}
		else if (previous.y < current.y)
		{
			if (current.x < next.x)
			{
				// right up angle
				m_bodyParts[index].SetSprite(m_sprites[BODY_RIGHT_UP]);
			}
			else
			{
				// left up angle
				m_bodyParts[index].SetSprite(m_sprites[BODY_LEFT_UP]);
			}
		}
		else if (previous.y > current.y)
		{
			if (current.x < next.x)
			{
				// right down angle
				m_bodyParts[index].SetSprite(m_sprites[BODY_RIGHT_DOWN]);
			}
			else
			{
				// left down angle
				m_bodyParts[index].SetSprite(m_sprites[BODY_LEFT_DOWN]);
			}
		}
		else if (previous.x > current.x)
		{
			if (current.y < next.y)
			{
				// right down angle
				m_bodyParts[index].SetSprite(m_sprites[BODY_RIGHT_DOWN]);

			}
			else
			{
				// right up angle
				m_bodyParts[index].SetSprite(m_sprites[BODY_RIGHT_UP]);

			}
		}
		else
		{
			if (current.y < next.y)
			{
				// left down angle
				m_bodyParts[index].SetSprite(m_sprites[BODY_LEFT_DOWN]);

			}
			else
			{
				// left up angle
				m_bodyParts[index].SetSprite(m_sprites[BODY_LEFT_UP]);

			}
		}
	}

	sf::Vector2f Snake::GetHeadPosition()
	{
		return m_bodyParts[0].getPosition();
	}


	void Snake::UpdateTailSprite()
	{
		sf::Vector2f tail = m_bodyParts[m_bodyParts.size() - 1].getPosition();
		sf::Vector2f previous = m_bodyParts[m_bodyParts.size() - 2].getPosition();

		if (previous.y == tail.y)
		{
			if (previous.x < tail.x)
			{
				// right
				m_bodyParts[m_bodyParts.size() - 1].SetSprite(m_sprites[TAIL_RIGHT]);
			}
			else
			{
				// left
				m_bodyParts[m_bodyParts.size() - 1].SetSprite(m_sprites[TAIL_LEFT]);
			}
		}
		else
		{
			if (previous.y < tail.y)
			{
				// up
				m_bodyParts[m_bodyParts.size() - 1].SetSprite(m_sprites[TAIL_UP]);
			}
			else
			{
				// down
				m_bodyParts[m_bodyParts.size() - 1].SetSprite(m_sprites[TAIL_DOWN]);
			}
		}
	}

	void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{		
		for (auto& part : m_bodyParts)
		{
			target.draw(part, states);
		}
	}

}