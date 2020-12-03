#include "Bullet.hh" 

Bullet::Bullet(sf::Texture* texture, sf::Vector2f pos)
{
    this->bullet.setTexture(*texture);
    this->bullet.setScale(0.3f,0.2f);
    this->bullet.setPosition(pos);
    this->bullet.setOrigin(32.f,32.f);
}   

Bullet::~Bullet(){}
