#pragma once
#include <SFML/Audio.hpp>

class SFX
{
private:
    const char** soundsList;
    sf::SoundBuffer* soundBuffer;
    sf::Sound* sound;

public:
    SFX(/* args */);
    ~SFX();

    void PlaySFX(int);
};