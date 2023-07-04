#pragma once
#include <SFML/Graphics.hpp>

class Button
{
	sf::RectangleShape m_buttonShape;
	sf::Text m_buttonText;
	bool m_isPressed = false;
public:
	Button() = default;
	Button(sf::Font&, const std::string&, const unsigned int, const float);
	void init(sf::Font& font, const std::string&, const unsigned int, const float);
	void handleInput(const sf::Event, const sf::RenderWindow&);
	void setPosition(const float, const float);
	void draw(sf::RenderWindow&);
	void setBackgroundColor(const sf::Color color);
	void setForegroundColor(const sf::Color color);
	void setText(const std::string&);
	bool isPressed();
};