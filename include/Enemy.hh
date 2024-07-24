
#include<SFML/Graphics.hpp>

class Enemy
{
private:
    
public:
        sf::Sprite enemy;
        int HP;
        int HPMax;

    Enemy(sf::Texture* texture, sf::Vector2u windowSize);
    ~Enemy();
};
