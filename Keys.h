#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <queue>
#include <mutex>

class Key
{
protected:
	sf::Sound m_sound;
	sf::RectangleShape m_rectangle;
	sf::SoundBuffer m_buffer;
	double m_pitch = 1.f;
	bool m_playing = false;
	bool m_wasMoved = false;
public:
	Key();
	~Key() = default;
	void draw(sf::RenderWindow&);
	void press();
	virtual void stopPlaying() = 0;
};

class BlackKey : public Key
{
public:
	BlackKey(const sf::SoundBuffer&, const std::pair<float, float>, const double);
	void stopPlaying() override;

};

class WhiteKey : public Key
{
public:
	WhiteKey(const sf::SoundBuffer&, const std::pair<float, float>, const double);
	void stopPlaying() override;
};
