#pragma once
#include<SFML/Graphics.hpp>

namespace snake
{
	class Apple : public sf::Drawable
	{
	public:
		Apple();
		Apple(const sf::Vector2f& position, unsigned int cellSize);
		void SetCellSize(unsigned int cellSize);
		void SetPosition(const sf::Vector2f& position);
		sf::Vector2f GetPosition();

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::CircleShape m_appleShape;
	};
}