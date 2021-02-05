#include "OverlayScreen.h"

namespace snake
{
	OverlayScreen::OverlayScreen(std::string text)
	{
		InitBG();
		InitText(text);
		IsEnable = false;
	}

	OverlayScreen::OverlayScreen(std::string text, sf::Vector2f textPosition)
	{
		InitBG();
		InitText(text);
		m_text.setPosition(textPosition);
		IsEnable = false;
	}

	void SetEnable(bool value)
	{

	}

	void OverlayScreen::InitBG()
	{
		m_bg.setSize({ X_WINDOW_SIZE, Y_FIELD_SIZE });
		m_bg.setFillColor(sf::Color(255, 255, 255, 100));
		m_bg.setOrigin({ X_WINDOW_SIZE / 2, Y_WINDOW_SIZE / 2 });
		m_bg.setPosition({ X_WINDOW_SIZE / 2, Y_WINDOW_SIZE / 2 });
	}

	void OverlayScreen::InitText(std::string text)
	{
		m_text.setColor(sf::Color::White);
		m_text.setPosition({ X_WINDOW_SIZE / 2, Y_WINDOW_SIZE / 2 });
		SetText(text);
	}

	void OverlayScreen::SetText(const std::string text)
	{
		m_text.setString(text);
	}

	std::string OverlayScreen::GetText() const
	{
		return m_text.getString();
	}

	void OverlayScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_bg, states);
		target.draw(m_text, states);
	}
}