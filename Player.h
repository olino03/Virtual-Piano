#pragma once
#include <SFML/Window.hpp>
#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <mutex>
#include <queue>

class Player
{
	//Input provided
	std::vector<std::tuple<char, sf::Keyboard::Key, sf::Time>> m_input;
	sf::Clock m_clock;

public:
	std::mutex m_eventMutex;
	std::queue<sf::Event> m_eventQueue;
	
	Player() = default;
	Player(const std::string&);
	void readFromFile(const std::string&);
	const sf::Event simulateKeyPress(sf::Keyboard::Key);
	const sf::Event simulateKeyRelease(sf::Keyboard::Key);
	void playback();
	void stopPlayback();
};