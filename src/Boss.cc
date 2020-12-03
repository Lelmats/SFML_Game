#include "Boss.hh" 

Boss::Boss(sf::Texture* texture)
{
    this->HPMax = 75;
    this->HP = this->HPMax;

    this->bossT.setTexture(*texture);
    this->bossT.setOrigin(30,230);
    this->bossT.setScale(2.f,2.f);
    this->bossT.setPosition(500,300);
    //this->enemy.setPosition(windowSize.x - this->enemy.getGlobalBounds().width, rand()% (int)(windowSize.y - this->enemy.getGlobalBounds().height));
}

Boss::~Boss(){}
