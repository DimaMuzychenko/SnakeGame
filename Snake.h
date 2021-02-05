#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "SnakePart.h"
namespace snake
{
	class Snake : public sf::Drawable, public sf::Transformable
	{
	public:
		Snake(sf::Vector2f startPosition);
		Snake();
		void SetStartPosition(sf::Vector2f position);
		std::vector<sf::Vector2f> GetSnakeCells();
		void InitSnake(sf::Vector2f startPosition);
		void ChangeDirection(std::int8_t direction);
		void MoveBodyParts();
		sf::Vector2f GetDirectionVector();
		sf::Vector2f GetNextCell();
		void AddBodyPart();
		void UpdateSprites();
		void UpdateHeadSprite();
		void UpdateBodySprite(std::size_t index);
		void UpdateTailSprite();

	private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		bool LoadSprites(const std::string& filePath);		

		sf::Texture m_texture;
		std::int8_t m_direction;;
		std::vector<sf::Sprite> m_sprites;
		std::vector<snake::SnakePart> m_bodyParts;
	};
}