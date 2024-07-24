
#include<SFML/Graphics.hpp>

class Boss
{
private:
    
public:
        sf::Sprite bossT;
        int HP;
        int HPMax;

    Boss(sf::Texture* texture);
    ~Boss();
};
