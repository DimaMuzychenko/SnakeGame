#pragma once
#include <SFML/Graphics.hpp>
namespace snake
{
	class Snake : sf::Drawable, sf::Transformable
	{
	public:


	private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::VertexArray m_vertices;
        sf::Texture m_tileset;
	};
}