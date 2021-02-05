#pragma once
#include <SFML/Graphics.hpp>

namespace snake
{
	class SnakePart : public sf::Drawable, public sf::Transformable
	{
	public:
		SnakePart(sf::Sprite& sprite, sf::Vector2f position);
		void SetSprite(sf::Sprite& sprite);
		sf::Sprite GetSprite();
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::Sprite m_sprite;
	};
}

