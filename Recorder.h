#pragma once
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include <tuple>
#include <fstream>

class Recorder
{
	std::vector<std::tuple<char, sf::Keyboard::Key, sf::Time>> m_input;
	sf::Clock m_time;
	bool m_isRecording = false;
public:
	Recorder() = default;
	void handleInput(const sf::Event);
	void startRecording();
	void stopRecording();
	void saveToFile(const std::string&);
};