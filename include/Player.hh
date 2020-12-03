#include<SFML/Graphics.hpp>
#include<vector>
#include "Bullet.hh"
#include "Animation.hh"

class Player 
{
private:
    
public:
    sf::Sprite shape;
    sf::Texture* texture;
    Animation** animations;
    int HP;
    int HPMax;
    
    std::vector<Bullet> bullets;

    sf::Sprite* GetSprite();
    
    Player(sf::Texture* texture);
    ~Player();
};
