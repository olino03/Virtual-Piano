#pragma once
#include <tuple>
#include <string>

constexpr std::pair<float, float> blackKeySize = std::make_pair(30.f, 120.f);
constexpr std::pair<float, float> whiteKeySize = std::make_pair(50.f, 200.f);
constexpr double baseFrequency = 261.63;
constexpr double whiteFrequencies[] = { 261.630, 293.665, 329.628, 349.228, 391.995, 440.000, 493.883, 523.251, 587.329, 659.255, 698.4565, 783.9909, 880.0000, 987.7666, 1046.502, 1174.659,1318.510 };
constexpr double blackFrequencies[] = { 277.183, 311.127, 369.994, 415.305, 466.160, 554.365, 622.254, 739.9888, 830.6094, 932.3275, 1108.731, 1244.508 };
constexpr std::tuple<int, int, int> backgroundColor = std::make_tuple(0, 0, 0);
constexpr int defaultWindowHeight = 700;
constexpr int defaultWindowWidth = 1000;
constexpr const char* fontPath = "Arial.ttf";
constexpr const char* baseSoundPath = "Base.wav";
constexpr const char* defaultSavePath = "Save.txt";
constexpr int buttonCharacterSize = 20;
constexpr int buttonPadding = 10;
