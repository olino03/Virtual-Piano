#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Keys.h"
#include "Button.h"
#include "Recorder.h"
#include "Player.h"

class Piano
{
    sf::RenderWindow m_window;
    std::vector<WhiteKey> m_whiteKeys;
    std::vector<BlackKey> m_blackKeys;
    sf::SoundBuffer m_baseSound;
    sf::RectangleShape m_background;
    sf::Event m_event;
    sf::Font m_font;
    Button m_recordButton;
    Button m_playbackButton;
    Recorder m_recorder;
    Player m_player;
    bool m_isRecording = false;
    bool m_isPlaying = false;
    bool m_shouldIgnoreKeypress = false;
public:
    Piano();
    void handleInput(const sf::Event);
    void update();
    void display();
};

