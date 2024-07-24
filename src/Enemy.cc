#include "Enemy.hh" 

Enemy::Enemy(sf::Texture* texture, sf::Vector2u windowSize)
{
    this->HPMax = rand() % 3 + 1;
    this->HP = this->HPMax;

    this->enemy.setTexture(*texture);

    this->enemy.setScale(0.4f,0.4f);
    this->enemy.setRotation(-90);
    this->enemy.setPosition(windowSize.x - this->enemy.getGlobalBounds().width, rand()% (int)(windowSize.y - this->enemy.getGlobalBounds().height));
}

Enemy::~Enemy(){}
