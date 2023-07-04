#include "Button.h"

Button::Button(sf::Font& font, const std::string& text, const unsigned int characterSize, const float padding = 2)
{
	m_buttonShape.setFillColor(sf::Color::Blue);
	m_buttonShape.setOutlineColor(sf::Color::Black);
	m_buttonShape.setOutlineThickness(2.0f);

	m_buttonText.setFont(font);
	m_buttonText.setString(text);
	m_buttonText.setCharacterSize(characterSize);
	m_buttonText.setFillColor(sf::Color::White);

	// Calculate button dimensions based on text size and padding
	sf::FloatRect textBounds = m_buttonText.getLocalBounds();
	m_buttonText.setOrigin(textBounds.left, textBounds.top);

	float buttonWidth = textBounds.width + padding * 2.0f;
	float buttonHeight = textBounds.height + padding * 2.0f;

	// Set button position and size
	m_buttonShape.setSize(sf::Vector2f(buttonWidth, buttonHeight));
	m_buttonText.setPosition(padding, padding);
}

void Button::handleInput(const sf::Event event, const sf::RenderWindow& window)
{
	sf::Vector2i mouseCoordonates = sf::Mouse::getPosition(window);
	if (m_buttonShape.getGlobalBounds().contains(mouseCoordonates.x, mouseCoordonates.y))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_isPressed = true;
				m_buttonShape.setFillColor(sf::Color::White);
				m_buttonText.setOutlineColor(sf::Color::White);
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_isPressed = false;
				m_buttonShape.setFillColor(sf::Color::White);
				m_buttonText.setOutlineColor(sf::Color::Black);
			}
		}
	}
}

void Button::setPosition(const float x, const float y)
{
	m_buttonShape.setPosition(x, y);
	m_buttonText.setPosition(x + m_buttonText.getPosition().x, y + m_buttonText.getPosition().y);
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(m_buttonShape);
	window.draw(m_buttonText);
}

void Button::setBackgroundColor(const sf::Color color)
{
	m_buttonShape.setFillColor(color);
	m_buttonShape.setOutlineThickness(2.0f);
	m_buttonShape.setOutlineColor(sf::Color::Black);
}

void Button::setForegroundColor(const sf::Color color)
{
	m_buttonText.setFillColor(color);
}

void Button::setText(const std::string& text)
{
	m_buttonText.setString(text);
}

void Button::init(sf::Font& font, const std::string& text, const unsigned int characterSize, const float padding = 2)
{
	m_buttonShape.setFillColor(sf::Color::White);
	m_buttonShape.setOutlineColor(sf::Color::Black);
	m_buttonShape.setOutlineThickness(2.0f);

	m_buttonText.setFont(font);
	m_buttonText.setString(text);
	m_buttonText.setCharacterSize(characterSize);
	m_buttonText.setFillColor(sf::Color::White);
	m_buttonText.setOutlineColor(sf::Color::Black);
	m_buttonText.setOutlineThickness(2.0f);

	// Calculate button dimensions based on text size and padding
	sf::FloatRect textBounds = m_buttonText.getLocalBounds();
	m_buttonText.setOrigin(textBounds.left, textBounds.top);

	float buttonWidth = textBounds.width + padding * 2.0f;
	float buttonHeight = textBounds.height + padding * 2.0f;

	// Set button position and size
	m_buttonShape.setSize(sf::Vector2f(buttonWidth, buttonHeight));
	m_buttonText.setPosition(padding, padding);
}

bool Button::isPressed()
{
	return m_isPressed;
}