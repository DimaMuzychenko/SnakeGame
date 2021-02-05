#pragma once
#include<SFML/Graphics.hpp>

namespace snake
{
	class Apple : public sf::Drawable
	{
	public:
		Apple();
		Apple(const sf::Vector2f& position);
		void SetPosition(const sf::Vector2f& position);
		sf::Vector2f GetPosition();

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		bool LoadSprite(const std::string& filePath);

		sf::Texture m_texture;
		sf::Sprite m_sprite;
	};
}