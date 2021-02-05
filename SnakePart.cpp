#include "SnakePart.h"
#include "GameConfig.h"

namespace snake
{
	SnakePart::SnakePart(sf::Sprite& sprite, sf::Vector2f position)
	{		
		SetSprite(sprite);		
		setPosition(position);
	}
	void SnakePart::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = m_sprite.getTexture();
		target.draw(m_sprite, states);
	}
	void SnakePart::SetSprite(sf::Sprite& sprite)
	{
		m_sprite = sprite;
		int rectWidth = m_sprite.getTextureRect().width;
		int rectHeight = m_sprite.getTextureRect().height;
		m_sprite.setOrigin(rectWidth / 2, rectHeight / 2);
		m_sprite.setScale((float)CELL_SIZE / (float)rectWidth, (float)CELL_SIZE / (float)rectHeight);
	}
	sf::Sprite SnakePart::GetSprite()
	{
		return m_sprite;
	}
}