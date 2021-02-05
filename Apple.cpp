#include "Apple.h"
#include <SFML/Graphics.hpp>
#include "GameConfig.h"
#include <iostream>

const sf::IntRect APPLE_RECT = {0 * SPRITE_SIZE, 3 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE};

namespace snake
{
	Apple::Apple()
	{
		if (!LoadSprite(SPRITESHEET_PATH))
		{
			std::cout << "No spritesheet found!" << std::endl;
		}
	}

	Apple::Apple(const sf::Vector2f& position)
	{
		if (!LoadSprite(SPRITESHEET_PATH))
		{
			std::cout << "No spritesheet found!" << std::endl;
		}	
		SetPosition(position);
	}

	bool Apple::LoadSprite(const std::string& filePath)
	{
		if (!m_texture.loadFromFile(filePath))
		{
			return false;
		}
		m_sprite.setTexture(m_texture);
		m_sprite.setTextureRect(APPLE_RECT);
		m_sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
		m_sprite.setScale((float)CELL_SIZE / (float)SPRITE_SIZE, (float)CELL_SIZE / (float)SPRITE_SIZE);
		return true;
	}

	void Apple::SetPosition(const sf::Vector2f& position)
	{
		m_sprite.setPosition((sf::Vector2f)position);
	}

	sf::Vector2f Apple::GetPosition()
	{
		return m_sprite.getPosition();
	}

	void Apple::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.texture = &m_texture;
		target.draw(m_sprite, states);
	}
}