#include "Piano.h"
#include "Button.h"
#include "Config.h"
#include <iostream>

Piano::Piano() : m_window(sf::VideoMode(defaultWindowWidth, defaultWindowHeight), "Virtual Piano")
{
    m_font.loadFromFile(fontPath);
    //TODO: display buttons dinamically instead of in fixed pixel positions
    m_playbackButton.init(m_font, "Playback", buttonCharacterSize, buttonPadding);
    m_recordButton.init(m_font, "Record", buttonCharacterSize, buttonPadding);
    m_recordButton.setPosition(350, 100);
    m_playbackButton.setPosition(550, 100);

    //Window settings
    m_window.setKeyRepeatEnabled(false);
    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);

    //Basesound settings
    m_baseSound.loadFromFile(baseSoundPath);

    //Background settings
    m_background.setSize(sf::Vector2f(defaultWindowWidth, defaultWindowHeight));
    m_background.setFillColor(sf::Color(std::get<0>(backgroundColor),
        std::get<1>(backgroundColor),
        std::get<2>(backgroundColor)));
    m_background.setPosition(0, 0);

    const size_t leftPadding = (defaultWindowWidth - whiteKeySize.first * 17) / 2;
    //White keys
    for (size_t offset = 0; offset < 17; offset++)
    {

        m_whiteKeys.push_back(
            WhiteKey(m_baseSound,
                std::make_pair<float, float>(leftPadding + offset * whiteKeySize.first,
                    defaultWindowHeight / 2 - (whiteKeySize.second / 2)),
                whiteFrequencies[offset] / baseFrequency));
    }

    //Black keys
    const double middleOffset = whiteKeySize.first - (blackKeySize.first / 2);
    const double blackOffset[] =
    {
            middleOffset,
            middleOffset + whiteKeySize.first,
            middleOffset + whiteKeySize.first * 3,
            middleOffset + whiteKeySize.first * 4,
            middleOffset + whiteKeySize.first * 5,
            middleOffset + whiteKeySize.first * 7,
            middleOffset + whiteKeySize.first * 8,
            middleOffset + whiteKeySize.first * 10,
            middleOffset + whiteKeySize.first * 11,
            middleOffset + whiteKeySize.first * 12,
            middleOffset + whiteKeySize.first * 14,
            middleOffset + whiteKeySize.first * 15,
            middleOffset + whiteKeySize.first * 16,

            middleOffset + whiteKeySize.first * 15,
    };  
    for (size_t offset = 0; offset < 12; offset++)
    {
        m_blackKeys.push_back(
            BlackKey(m_baseSound,
                std::make_pair<float, float>(leftPadding + blackOffset[offset],
                    defaultWindowHeight / 2 - (whiteKeySize.second / 2)),
                blackFrequencies[offset] / baseFrequency));
    }
}

void Piano::handleInput(sf::Event event)
{
    m_playbackButton.handleInput(event, m_window);
    m_recordButton.handleInput(event, m_window);


    // Handle record button
    {
        bool pressed = m_recordButton.isPressed();
        if (pressed)
        {
            m_isRecording = !m_isRecording;
            if (m_isRecording)
            {
                m_recorder.startRecording();
                std::cout << "inregistrez\n";
            }
            else
            {
                m_recorder.stopRecording();
                m_recorder.saveToFile(defaultSavePath);
                std::cout << "nu mai inregistrez\n";
            }
        }

        if (m_isRecording)
        {
            m_recorder.handleInput(event);
        }
    }
    // Handle playback button
    {
        bool pressed = m_playbackButton.isPressed();
        if (pressed)
        {
            m_isPlaying = !m_isPlaying;
            if (m_isPlaying)
            {
                m_player.readFromFile(defaultSavePath);
                std::thread t(&Player::playback, &m_player);
                t.detach();
            }
            else
            {
                // TODO: Make sure we don't create a data race while trying to clear the queue
                // m_player.stopPlayback();
            }
        }
    }
    sf::Event simulatedEvent;
    bool thereIsAnEvent = false;
    if(m_isPlaying)
    {
        std::lock_guard<std::mutex> lock(m_player.m_eventMutex);
        if (!m_player.m_eventQueue.empty())
        {
            simulatedEvent = m_player.m_eventQueue.front();
            m_player.m_eventQueue.pop();
            thereIsAnEvent = true;
            std::cout << "I consumed an event\n";
        }
    }
    if (event.type == sf::Event::KeyPressed && !m_isPlaying)
    {
        switch (event.key.code)
        {
            //Whitekeys
        case sf::Keyboard::Q:  m_whiteKeys[0].press(); break;
        case sf::Keyboard::W:  m_whiteKeys[1].press(); break;
        case sf::Keyboard::E:  m_whiteKeys[2].press(); break;
        case sf::Keyboard::R:  m_whiteKeys[3].press(); break;
        case sf::Keyboard::T:  m_whiteKeys[4].press(); break;
        case sf::Keyboard::Y:  m_whiteKeys[5].press(); break;
        case sf::Keyboard::U:  m_whiteKeys[6].press(); break;
        case sf::Keyboard::I:  m_whiteKeys[7].press(); break;
        case sf::Keyboard::O:  m_whiteKeys[8].press(); break;
        case sf::Keyboard::P:  m_whiteKeys[9].press(); break;
        case sf::Keyboard::Z:  m_whiteKeys[10].press(); break;
        case sf::Keyboard::X:  m_whiteKeys[11].press(); break;
        case sf::Keyboard::C:  m_whiteKeys[12].press(); break;
        case sf::Keyboard::V:  m_whiteKeys[13].press(); break;
        case sf::Keyboard::B:  m_whiteKeys[14].press(); break;
        case sf::Keyboard::N:  m_whiteKeys[15].press(); break;
        case sf::Keyboard::M:  m_whiteKeys[16].press(); break;
            // Blackkeys
        case sf::Keyboard::Num2:  m_blackKeys[0].press(); break;
        case sf::Keyboard::Num3:  m_blackKeys[1].press(); break;
        case sf::Keyboard::Num5:  m_blackKeys[2].press(); break;
        case sf::Keyboard::Num6:  m_blackKeys[3].press(); break;
        case sf::Keyboard::Num7:  m_blackKeys[4].press(); break;
        case sf::Keyboard::Num9:  m_blackKeys[5].press(); break;
        case sf::Keyboard::Num0:  m_blackKeys[6].press(); break;
        case sf::Keyboard::S:  m_blackKeys[7].press(); break;
        case sf::Keyboard::D:  m_blackKeys[8].press(); break;
        case sf::Keyboard::F:  m_blackKeys[9].press(); break;
        case sf::Keyboard::H:  m_blackKeys[10].press(); break;
        case sf::Keyboard::J:  m_blackKeys[11].press(); break;
        default: break;
        };
    }
    if (event.type == sf::Event::KeyReleased)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Q:  m_whiteKeys[0].stopPlaying(); break;
        case sf::Keyboard::W:  m_whiteKeys[1].stopPlaying(); break;
        case sf::Keyboard::E:  m_whiteKeys[2].stopPlaying(); break;
        case sf::Keyboard::R:  m_whiteKeys[3].stopPlaying(); break;
        case sf::Keyboard::T:  m_whiteKeys[4].stopPlaying(); break;
        case sf::Keyboard::Y:  m_whiteKeys[5].stopPlaying(); break;
        case sf::Keyboard::U:  m_whiteKeys[6].stopPlaying(); break;
        case sf::Keyboard::I:  m_whiteKeys[7].stopPlaying(); break;
        case sf::Keyboard::O:  m_whiteKeys[8].stopPlaying(); break;
        case sf::Keyboard::P:  m_whiteKeys[9].stopPlaying(); break;
        case sf::Keyboard::Z:  m_whiteKeys[10].stopPlaying(); break;
        case sf::Keyboard::X:  m_whiteKeys[11].stopPlaying(); break;
        case sf::Keyboard::C:  m_whiteKeys[12].stopPlaying(); break;
        case sf::Keyboard::V:  m_whiteKeys[13].stopPlaying(); break;
        case sf::Keyboard::B:  m_whiteKeys[14].stopPlaying(); break;
        case sf::Keyboard::N:  m_whiteKeys[15].stopPlaying(); break;
        case sf::Keyboard::M:  m_whiteKeys[16].stopPlaying(); break;
            // Blackkeys
        case sf::Keyboard::Num2:  m_blackKeys[0].stopPlaying(); break;
        case sf::Keyboard::Num3:  m_blackKeys[1].stopPlaying(); break;
        case sf::Keyboard::Num5:  m_blackKeys[2].stopPlaying(); break;
        case sf::Keyboard::Num6:  m_blackKeys[3].stopPlaying(); break;
        case sf::Keyboard::Num7:  m_blackKeys[4].stopPlaying(); break;
        case sf::Keyboard::Num9:  m_blackKeys[5].stopPlaying(); break;
        case sf::Keyboard::Num0:  m_blackKeys[6].stopPlaying(); break;
        case sf::Keyboard::S:  m_blackKeys[7].stopPlaying(); break;
        case sf::Keyboard::D:  m_blackKeys[8].stopPlaying(); break;
        case sf::Keyboard::F:  m_blackKeys[9].stopPlaying(); break;
        case sf::Keyboard::H:  m_blackKeys[10].stopPlaying(); break;
        case sf::Keyboard::J:  m_blackKeys[11].stopPlaying(); break;
        default: break;

        };
    }
    if (m_isPlaying && thereIsAnEvent)
    {
        if (simulatedEvent.type == sf::Event::KeyPressed)
        {
            switch (simulatedEvent.key.code)
            {
                //Whitekeys
            case sf::Keyboard::Q:  m_whiteKeys[0].press(); break;
            case sf::Keyboard::W:  m_whiteKeys[1].press(); break;
            case sf::Keyboard::E:  m_whiteKeys[2].press(); break;
            case sf::Keyboard::R:  m_whiteKeys[3].press(); break;
            case sf::Keyboard::T:  m_whiteKeys[4].press(); break;
            case sf::Keyboard::Y:  m_whiteKeys[5].press(); break;
            case sf::Keyboard::U:  m_whiteKeys[6].press(); break;
            case sf::Keyboard::I:  m_whiteKeys[7].press(); break;
            case sf::Keyboard::O:  m_whiteKeys[8].press(); break;
            case sf::Keyboard::P:  m_whiteKeys[9].press(); break;
            case sf::Keyboard::Z:  m_whiteKeys[10].press(); break;
            case sf::Keyboard::X:  m_whiteKeys[11].press(); break;
            case sf::Keyboard::C:  m_whiteKeys[12].press(); break;
            case sf::Keyboard::V:  m_whiteKeys[13].press(); break;
            case sf::Keyboard::B:  m_whiteKeys[14].press(); break;
            case sf::Keyboard::N:  m_whiteKeys[15].press(); break;
            case sf::Keyboard::M:  m_whiteKeys[16].press(); break;
                // Blackkeys
            case sf::Keyboard::Num2:  m_blackKeys[0].press(); break;
            case sf::Keyboard::Num3:  m_blackKeys[1].press(); break;
            case sf::Keyboard::Num5:  m_blackKeys[2].press(); break;
            case sf::Keyboard::Num6:  m_blackKeys[3].press(); break;
            case sf::Keyboard::Num7:  m_blackKeys[4].press(); break;
            case sf::Keyboard::Num9:  m_blackKeys[5].press(); break;
            case sf::Keyboard::Num0:  m_blackKeys[6].press(); break;
            case sf::Keyboard::S:  m_blackKeys[7].press(); break;
            case sf::Keyboard::D:  m_blackKeys[8].press(); break;
            case sf::Keyboard::F:  m_blackKeys[9].press(); break;
            case sf::Keyboard::H:  m_blackKeys[10].press(); break;
            case sf::Keyboard::J:  m_blackKeys[11].press(); break;
            default: break;
            };
        }
        if (simulatedEvent.type == sf::Event::KeyReleased)
        {
            switch (simulatedEvent.key.code)
            {
            case sf::Keyboard::Q:  m_whiteKeys[0].stopPlaying(); break;
            case sf::Keyboard::W:  m_whiteKeys[1].stopPlaying(); break;
            case sf::Keyboard::E:  m_whiteKeys[2].stopPlaying(); break;
            case sf::Keyboard::R:  m_whiteKeys[3].stopPlaying(); break;
            case sf::Keyboard::T:  m_whiteKeys[4].stopPlaying(); break;
            case sf::Keyboard::Y:  m_whiteKeys[5].stopPlaying(); break;
            case sf::Keyboard::U:  m_whiteKeys[6].stopPlaying(); break;
            case sf::Keyboard::I:  m_whiteKeys[7].stopPlaying(); break;
            case sf::Keyboard::O:  m_whiteKeys[8].stopPlaying(); break;
            case sf::Keyboard::P:  m_whiteKeys[9].stopPlaying(); break;
            case sf::Keyboard::Z:  m_whiteKeys[10].stopPlaying(); break;
            case sf::Keyboard::X:  m_whiteKeys[11].stopPlaying(); break;
            case sf::Keyboard::C:  m_whiteKeys[12].stopPlaying(); break;
            case sf::Keyboard::V:  m_whiteKeys[13].stopPlaying(); break;
            case sf::Keyboard::B:  m_whiteKeys[14].stopPlaying(); break;
            case sf::Keyboard::N:  m_whiteKeys[15].stopPlaying(); break;
            case sf::Keyboard::M:  m_whiteKeys[16].stopPlaying(); break;

                // Blackkeys
            case sf::Keyboard::Num2:  m_blackKeys[0].stopPlaying(); break;
            case sf::Keyboard::Num3:  m_blackKeys[1].stopPlaying(); break;
            case sf::Keyboard::Num5:  m_blackKeys[2].stopPlaying(); break;
            case sf::Keyboard::Num6:  m_blackKeys[3].stopPlaying(); break;
            case sf::Keyboard::Num7:  m_blackKeys[4].stopPlaying(); break;
            case sf::Keyboard::Num9:  m_blackKeys[5].stopPlaying(); break;
            case sf::Keyboard::Num0:  m_blackKeys[6].stopPlaying(); break;
            case sf::Keyboard::S:  m_blackKeys[7].stopPlaying(); break;
            case sf::Keyboard::D:  m_blackKeys[8].stopPlaying(); break;
            case sf::Keyboard::F:  m_blackKeys[9].stopPlaying(); break;
            case sf::Keyboard::H:  m_blackKeys[10].stopPlaying(); break;
            case sf::Keyboard::J:  m_blackKeys[11].stopPlaying(); break;
            default: break;
            };
        }
    }
}

void Piano::update()
{
    while (m_window.isOpen())
    {
        while (m_window.pollEvent(m_event))
        {
            //Handle resizing this doesnt draw properly have to investigate why
            //if (m_event.type == sf::Event::Resized)
            //{
            //    windowHeight = m_event.size.height;
            //    windowWidth = m_event.size.width;
            //}
            if (m_event.type == sf::Event::Closed)
            {
                m_window.close();
            }
            handleInput(m_event);
        }
        display();
    }
}

void Piano::display()
{
    m_window.clear();
    m_window.draw(m_background);
    for (auto& iter : m_whiteKeys)
        iter.draw(m_window);
    for (auto& iter : m_blackKeys)
        iter.draw(m_window);
    m_playbackButton.draw(m_window);
    m_recordButton.draw(m_window);
    m_window.display();
}
