#include<SFML/Graphics.hpp>

class Bullet 
{
private:
    
public:
    sf::Sprite bullet;
    sf::Texture* texture;
    
    Bullet(sf::Texture* texture, sf::Vector2f pos);
    ~Bullet();
};
