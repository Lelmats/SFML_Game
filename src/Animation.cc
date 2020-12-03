#include "Animation.hh"
#include<iostream>

//constructor
Animation::Animation(int cropPosY, int startFrame, int endFrame, sf::Sprite* sprite, float delay)
{
    this->cropPosY = cropPosY;
    this->startFrame = startFrame;
    this->endFrame = endFrame;
    this->sprite = sprite;
    this->delay = delay;
    currentFrame = startFrame;
}

//destructor
Animation::~Animation(){}

void Animation::Play(float& deltaTime)
{
    timer += deltaTime;
    if(timer >= delay)
    {
        if(currentFrame + 1 > endFrame)
        {
            currentFrame = startFrame;
        }
        else
        {
            currentFrame++;
        }
        
        sprite->setTextureRect(*(new sf::IntRect( 
            sprite->getTextureRect().width * currentFrame, 
            sprite->getTextureRect().height * cropPosY,  
            sprite->getTextureRect().width,  
            sprite->getTextureRect().height)));
               
        timer = 0.f;
    }
}
void Animation::SetAnimations(Animation** animations)
{
    this->animations = animations;
}

Animation* Animation::GetAnimation(int index) const
{
    return *(animations + index);
}
sf::Sprite* Animation::GetSprite() 
{
    return sprite;
}
