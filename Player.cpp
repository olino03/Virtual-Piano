#include "Player.h"
#include <iostream>

Player::Player(const std::string& fileName)
{
	std::ifstream fin(fileName);
	char action;
	int actionCode;
	int time;
	while (fin >> action >> actionCode >> time)
	{
		m_input.push_back(std::make_tuple(action, sf::Keyboard::Key(actionCode), sf::milliseconds(time)));
	}
}

void Player::readFromFile(const std::string& fileName)
{
    if (!m_input.empty())
        m_input.clear();
    std::ifstream fin(fileName);
    char action;
    int actionCode;
    int time;
    while (fin >> action >> actionCode >> time)
    {
        m_input.push_back(std::make_tuple(action, sf::Keyboard::Key(actionCode), sf::milliseconds(time)));
    }
}

void Player::playback()
{
    size_t index = 0;
    m_clock.restart();
    while (index < m_input.size())
    {
        while (index < m_input.size() &&
            m_clock.getElapsedTime().asMilliseconds() > std::get<2>(m_input[index]).asMilliseconds())
        {
            if (std::get<0>(m_input[index]) == 'P')
            {
                std::lock_guard<std::mutex> lock(m_eventMutex);
                m_eventQueue.push(simulateKeyPress(std::get<1>(m_input[index])));
                std::cout << "I pushed an event\n";
            }
            if (std::get<0>(m_input[index]) == 'R')
            {
                std::lock_guard<std::mutex> lock(m_eventMutex);
                m_eventQueue.push(simulateKeyRelease(std::get<1>(m_input[index])));
                std::cout << "I pushed an event\n";
            }
            index++;
        }
    }
}

void Player::stopPlayback()
{
    m_clock.restart();
    std::lock_guard<std::mutex> lock(m_eventMutex);
    m_eventQueue = {};
}

const sf::Event Player::simulateKeyRelease(sf::Keyboard::Key key)
{
    sf::Event::KeyEvent data;
    data.code = key;
    data.alt = false;
    data.control = false;
    data.shift = false;
    data.system = false;

    sf::Event event;
    event.type = sf::Event::KeyReleased;
    event.key = data;
    return event;

}

const sf::Event Player::simulateKeyPress(sf::Keyboard::Key key)
{
    sf::Event::KeyEvent data;
    data.code = key;
    data.alt = false;
    data.control = false;
    data.shift = false;
    data.system = false;

    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key = data;
    return event;

}