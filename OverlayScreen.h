#pragma once
#include <SFML/Graphics.hpp>
#include "GameConfig.h"

namespace snake
{
	class OverlayScreen : public sf::Drawable, public sf::Transformable
	{
	public:
		OverlayScreen(std::string text, sf::Color bgColo);
		OverlayScreen(std::string text, sf::Vector2f textPosition);
		OverlayScreen(std::string text, sf::Vector2f textPosition, sf::Color bgColor);
		void SetText(const std::string text);
		std::string GetText() const;
		void InitBG(sf::Color bgColor);
		void InitText(std::string text);
		void SetEnable(bool value);
		bool IsEnable();

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		bool m_isEnable;
		sf::Text m_text;
		sf::RectangleShape m_bg;
	};
}

