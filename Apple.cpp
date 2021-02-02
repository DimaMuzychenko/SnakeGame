#include "Apple.h"
#include <SFML/Graphics.hpp>

namespace snake
{
	Apple::Apple()
	{
		m_appleShape.setFillColor(sf::Color::Red);
	}

	Apple::Apple(const sf::Vector2f& position, unsigned int cellSize)
	{
		SetCellSize(cellSize);
		m_appleShape.setFillColor(sf::Color::Red);
		SetPosition(position);
	}

	void Apple::SetCellSize(unsigned int cellSize)
	{
		float radius = cellSize / 2 * 0.8;
		m_appleShape.setRadius(radius);
		m_appleShape.setOrigin(radius, radius);
	}

	void Apple::SetPosition(const sf::Vector2f& position)
	{
		m_appleShape.setPosition((sf::Vector2f)position);
	}

	sf::Vector2f Apple::GetPosition()
	{
		return m_appleShape.getPosition();
	}

	void Apple::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_appleShape, states);
	}
}