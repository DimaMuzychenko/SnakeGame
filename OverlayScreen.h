#pragma once
#include <SFML/Graphics.hpp>
#include "GameConfig.h"

namespace snake
{
	class OverlayScreen : public sf::Drawable, public sf::Transformable
	{
	public:
		OverlayScreen(std::string text);
		OverlayScreen(std::string text, sf::Vector2f textPosition);
		void SetText(const std::string text);
		std::string GetText() const;
		void InitBG();
		void InitText(std::string text);
		void SetEnable(bool value);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		bool IsEnable;
		sf::Text m_text;
		sf::RectangleShape m_bg;
	};
}

