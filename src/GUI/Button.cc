/*#include "GUI/Button.hh"

Button::Button(float posX, float posY, float width, float height, float borderSize, sf::Color* fillColor, sf::Color* borderColor, sf::RenderWindow& window)
{
    this->posX = posX;
    this->posY = posY;
    this->width = width;
    this->height = height;
    this->borderSize = borderSize;
    this->fillColor = fillColor;
    this->borderColor = borderColor;
    this->window = window;
    Init();
}

void Button::Init()
{
    rectangleShape = new sf::RectangleShape();
    rectangleShape->setPosition((new sf::Vector2f(posX, posY)));
    rectangleShape->setSize((new sf::Vector2f(width, height)));
    rectangleShape->setFillColor(fillColor);
    rectangleShape->setOutlineColor(borderColor);
    rectangleShape->setOutlineThickness(borderSize);
}

Button::~Button()
{
}

void Button::OnClick()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);//captura si estamos en el area de la venta de nuestor juego
    sf::Vector2f mouseTranslate = window->mapPixelToCoords(mousePos); // este 
    if(rectangleShape->getGlobalBounds().contains(mouseTranslate))
    {
        std::cout << "mouse hover" << std::endl;
    }
}

void Button::Update()
{
    OnClick();
    window->draw(*rectangleShape);
}
*/