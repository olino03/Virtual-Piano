#include "Recorder.h"

void Recorder::handleInput(const sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        m_input.push_back(std::make_tuple('P', event.key.code, m_time.getElapsedTime()));
    }
    if (event.type == sf::Event::KeyReleased)
    {
        m_input.push_back(std::make_tuple('R', event.key.code, m_time.getElapsedTime()));
    }
}

void Recorder::startRecording()
{
    if (!m_input.empty())
        m_input.clear();
    m_isRecording = true;
    m_time.restart();
}

void Recorder::stopRecording()
{
    m_isRecording = false;
}

void Recorder::saveToFile(const std::string& fileName)
{
    std::ofstream fout(fileName);
    for (auto& it : m_input)
    {
        fout << std::get<0>(it) << ' ' << std::get<1>(it) << ' ' << std::get<2>(it).asMilliseconds() << '\n';
    }
}