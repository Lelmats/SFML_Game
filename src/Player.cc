#include "Player.hh" 

Player::Player(sf::Texture* texture) 
{
    this->HPMax = 3;
    this->HP = this->HPMax;

    this->texture=texture;
    this->shape.setTexture(*texture);

    this->shape.setScale(.3f,0.3f);
    this->shape.setOrigin(90.f,0.f);
    this->shape.setPosition(650,600);
}

Player::~Player(){}

