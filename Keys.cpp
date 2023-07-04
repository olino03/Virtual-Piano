#include "Keys.h"
#include "Config.h"

static std::queue<sf::Sound> pendingStopping;
static std::mutex pendingQueue;

Key::Key()
{
	m_rectangle.setOutlineColor(sf::Color::Black);
	m_rectangle.setOutlineThickness(2);
}

void Key::draw(sf::RenderWindow& window)
{
	window.draw(m_rectangle);
}

void Key::press()
{
	if (!m_playing)
	{
		if (m_wasMoved)
		{
			m_sound = sf::Sound(m_buffer);
			m_sound.setPitch(m_pitch);
		}
		m_sound.stop();
		m_sound.play();
		m_playing = true;
		m_rectangle.setFillColor(sf::Color(200, 200, 200));
	}
}

BlackKey::BlackKey(const sf::SoundBuffer& soundBuffer, const std::pair<float, float> position, const double pitch)
{
	m_pitch = pitch;
	m_buffer = soundBuffer;
	m_sound.setBuffer(soundBuffer);
	m_sound.setPitch(pitch);
	m_rectangle.setFillColor(sf::Color::Black);
	m_rectangle.setSize(sf::Vector2f(blackKeySize.first, blackKeySize.second));
	m_rectangle.setPosition(position.first, position.second);
}

WhiteKey::WhiteKey(const sf::SoundBuffer& soundBuffer, const std::pair<float, float> position, const double pitch)
{
	m_pitch = pitch;
	m_buffer = soundBuffer;
	m_sound.setBuffer(soundBuffer);
	m_sound.setPitch(pitch);
	m_rectangle.setFillColor(sf::Color::White);
	m_rectangle.setSize(sf::Vector2f(whiteKeySize.first, whiteKeySize.second));
	m_rectangle.setPosition(position.first, position.second);
}

void WhiteKey::stopPlaying()
{
	{
		std::lock_guard<std::mutex> lock(pendingQueue);
		pendingStopping.push(m_sound);
		m_wasMoved = true;
	}
	m_rectangle.setFillColor(sf::Color::White);
	m_playing = false;
};

void BlackKey::stopPlaying()
{
	{
		std::lock_guard<std::mutex> lock(pendingQueue);
		pendingStopping.push(m_sound);
		m_wasMoved = true;
	}
	m_rectangle.setFillColor(sf::Color::Black);
	m_playing = false;
}