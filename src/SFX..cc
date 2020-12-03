#include "SFX.hh"

SFX::SFX()
{
    soundBuffer = new sf::SoundBuffer();
    sound = new sf::Sound();
    this->sound->setVolume(3.f);

    soundsList = new const char*[8]
    {
        "assets/audio/Brave Pilots (Menu Screen).ogg",
        "assets/audio/DeathMatch (Boss Theme).ogg",
        "assets/audio/Defeated (Game Over Tune).ogg",
        "assets/audio/Victory Tune.ogg",
        "assets/audio/Explosion+1.ogg",
        "assets/audio/laser3.ogg",
        "assets/audio/Powerup11.ogg",
        "assets/audio/Explosion18.ogg",
    };
}
SFX::~SFX(){}


void SFX::PlaySFX(int index)
{
    soundBuffer->loadFromFile(soundsList[index]);
    sound->setBuffer(*soundBuffer);
    sound->play();
}