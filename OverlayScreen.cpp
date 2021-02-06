#include "OverlayScreen.h"

namespace snake
{
	OverlayScreen::OverlayScreen(std::string text, sf::Color bgColor)
	{
		InitBG(bgColor);
		InitText(text);
		m_isEnable = true;
	}

	OverlayScreen::OverlayScreen(std::string text, sf::Vector2f textPosition, sf::Color bgColor)
	{
		InitBG(bgColor);
		InitText(text);
		m_text.setPosition(textPosition);
		m_bg.setFillColor(bgColor);
		m_isEnable = true;
	}

	void OverlayScreen::SetEnable(bool value)
	{
		m_isEnable = value;
	}

	bool OverlayScreen::IsEnable()
	{
		return m_isEnable;
	}

	void OverlayScreen::InitBG(sf::Color bgColor)
	{
		m_bg.setSize({X_WINDOW_SIZE, Y_WINDOW_SIZE });
		m_bg.setFillColor(bgColor);
		m_bg.setOrigin({ X_WINDOW_SIZE / 2, Y_WINDOW_SIZE / 2 });
		m_bg.setPosition({ X_WINDOW_SIZE / 2, Y_WINDOW_SIZE / 2 });
	}

	void OverlayScreen::InitText(std::string text)
	{
		m_text.setFillColor(sf::Color::White);
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