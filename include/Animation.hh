#pragma once
#include<SFML/Graphics.hpp>

class Animation
{
    private:
        int cropPosY;
        int startFrame;
        int endFrame;
        sf::Sprite* sprite;
        float delay;
        int currentFrame;
        float timer{};
        Animation** animations;
    public:
        sf::Sprite* GetSprite();
        void SetPosition(float, float);
        Animation(int, int, int, sf::Sprite*, float);
        ~Animation();
        void Play(float&);
        void SetAnimations(Animation**);
        Animation* GetAnimation(int) const;
};
