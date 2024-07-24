#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<box2d/box2d.h>
#include<math.h>
#include<vector>


#include "Player.hh"
#include "SFX.hh"
#include "Enemy.hh"
#include "Boss.hh"


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define GAME_NAME "El Naves"
#define CHAR "assets/sprites/character/character1.png"
#define ENEMY "assets/sprites/character/Enemy.png"
#define ENEMY2 "assets/sprites/character/Enemy2.png"
#define VIDA "assets/sprites/character/Vida.png"
#define BOSS "assets/sprites/character/Boss.png"
#define BALA "assets/sprites/character/balazoenseco.png"
#define BACK "assets/scenes/ATMOS720.png"
#define WIN "assets/scenes/Main Menu720.png"
#define GAMEOVER "assets/scenes/Gameover720.png"
#define FONT "assets/fonts/Game Played.otf"
#define FONT2 "assets/fonts/zorque.ttf"
#define ICON "assets/cheems.ico"
#define MUSIC "assets/audio/Epic End.ogg"

#define SPRITE_SCALE 0.7f
#define FPS 144
#define PLAYER_MOVESPEED 10.0f

int main()
{
    srand(time(NULL));
    //esto es la ventana de tu grafico
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
    sf::Image* iconImage{new sf::Image()};
    iconImage->loadFromFile(ICON);
    window->setIcon(64, 64, iconImage->getPixelsPtr());
    //aqui vas a guardar los eventos dentro de la ventana, eje: teclado, mouse, etc.
    sf::Event event;

    //physics declaration
    b2Vec2* gravity{new b2Vec2(0.f, 0.f)};
    b2World* world{new b2World(*gravity)};

    //Sonido Fondo
    sf::SoundBuffer* soundBuffer{new sf::SoundBuffer()};
    sf::Sound* musicaBackground{new sf::Sound()};
    soundBuffer->loadFromFile(MUSIC);
    musicaBackground->setBuffer(*soundBuffer);
    //musicaBackground->setLoop(true);
    musicaBackground->setVolume(3.f);
    musicaBackground->play();
    /*
    sf::SoundBuffer* soundBuffer2{new sf::SoundBuffer()};
    sf::Sound* gameOverSFX{new sf::Sound()};
    soundBuffer2->loadFromFile(GAMEOVERSOUND);
    gameOverSFX->setBuffer(*soundBuffer2);
    gameOverSFX->setLoop(true);
    gameOverSFX->setVolume(10.f);*/
    SFX* sfx;
    sfx = new SFX();

    sf::Clock* clock{new sf::Clock()};
    float deltaTime{};

    window->setFramerateLimit(FPS);

    //init text
    sf::Font font;
    font.loadFromFile(FONT);

    sf::Font font2;
    font2.loadFromFile(FONT2);

    //init textures
    sf::Texture gameOverTex;
    gameOverTex.loadFromFile(GAMEOVER);

    sf::Texture backgroundTex;
    backgroundTex.loadFromFile(BACK);

    sf::Texture winnerscreenTex;
    winnerscreenTex.loadFromFile(WIN);

    sf::Texture playerTex;
    playerTex.loadFromFile(CHAR);

    sf::Texture enemyTex;
    enemyTex.loadFromFile(ENEMY);

    sf::Texture enemyTex2;
    enemyTex2.loadFromFile(ENEMY2);

    sf::Texture enemyTex3;
    enemyTex3.loadFromFile(VIDA);

    sf::Texture bossTex;
    bossTex.loadFromFile(BOSS);

    sf::Texture bulletTex;
    bulletTex.loadFromFile(BALA);
    
    //Overlays Init

    sf::Sprite background;
    background.setTexture(backgroundTex);

    sf::Sprite gameOver;
    gameOver.setTexture(gameOverTex);

    sf::Sprite winnerscreen;
    winnerscreen.setTexture(winnerscreenTex);

    //UI Init
    sf::Text scoreText;
    scoreText.setFont(font2);
    scoreText.setCharacterSize(15);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f,10.f);

    sf::Text instriccionesText;
    instriccionesText.setFont(font);
    instriccionesText.setCharacterSize(24);
    instriccionesText.setFillColor(sf::Color::Black);
    instriccionesText.setPosition(440,670);

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(120);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(100.f, window->getSize().y / 2);
    gameOverText.setString("GANASTE");

    sf::Text scoreEndText;
    scoreEndText.setFont(font);
    scoreEndText.setCharacterSize(30);
    scoreEndText.setFillColor(sf::Color::White);
    scoreEndText.setPosition(100,600);
    
    sf::Text scoreEndText2;
    scoreEndText2.setFont(font);
    scoreEndText2.setCharacterSize(40);
    scoreEndText2.setFillColor(sf::Color::White);
    scoreEndText2.setPosition(750,600);

    //Player Init
    int score = 0;
    Player player(&playerTex);
    int shootTimer = 30;
    sf::Text hpText;
    hpText.setFont(font);
    hpText.setCharacterSize(10);
    hpText.setFillColor(sf::Color::White);

    //Boss Init
    Boss boss(&bossTex);
    sf::Text BhpText;
    BhpText.setFont(font);
    BhpText.setCharacterSize(20);
    BhpText.setFillColor(sf::Color::White);

    //Enemy Init
    int enemySpawnTimer = 0;
    std::vector<Enemy> enemies;
    sf::Text EhpText;
    EhpText.setFont(font);
    EhpText.setCharacterSize(10);
    EhpText.setFillColor(sf::Color::White);

    //Enemy2 Init
    int enemySpawnTimer2 = 0;
    std::vector<Enemy> enemies2;
    sf::Text EhpText2;
    EhpText2.setFont(font);
    EhpText2.setCharacterSize(10);
    EhpText2.setFillColor(sf::Color::White);

    //Centro de vida Init
    int enemySpawnTimer3 = 0;
    std::vector<Enemy> enemies3;
    sf::Text EhpText3;
    EhpText3.setFont(font);
    EhpText3.setCharacterSize(14);
    EhpText3.setFillColor(sf::Color::White);
    
    //Animation Init

    //esto es el loop principal, mientras la ventana este abierta, esto se va ejecutar.
    while (window->isOpen())
    {
        //mientras se esten ejecutando eventos dentro de la ventana, esto se va repetir eje: teclado, joystick, mouse, etc
        while (window->pollEvent(event))
        {
            //si el evento fue la acción de cerrar la ventana, entonces termina la aplicación.
            if(event.type == sf::Event::Closed)
            {
                
                window->close();
            }
        }
        if (player.HP >= 0)
        {
        //Player
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.shape.move(0.f, -3.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.shape.move(-3.f, 0.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) player.shape.move(0.f, 3.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.shape.move(3.f, 0.f);

        hpText.setPosition(player.shape.getPosition().x, player.shape.getPosition().y - hpText.getGlobalBounds().height);
        hpText.setString("HP: " +std::to_string(player.HP) + "/" + std::to_string(player.HPMax));

        BhpText.setPosition(boss.bossT.getPosition().x, boss.bossT.getPosition().y - BhpText.getGlobalBounds().height);
        BhpText.setString("BOSS: " + std::to_string(boss.HP) + "/" + std::to_string(boss.HPMax));

        //Collision with window
        if (player.shape.getPosition().x <= 0) //Left
            player.shape.setPosition(0.f, player.shape.getPosition().y);
        if (player.shape.getPosition().x >= window->getSize().x - player.shape.getGlobalBounds().width) //Right
            player.shape.setPosition(window->getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);
        if (player.shape.getPosition().y <= 0) //Top
            player.shape.setPosition(player.shape.getPosition().x, 0.f);
        if (player.shape.getPosition().y >= window->getSize().y - player.shape.getGlobalBounds().height) //Bottom
            player.shape.setPosition(player.shape.getPosition().x, window->getSize().y - player.shape.getGlobalBounds().height);
        
        //Update Controls
        if (shootTimer < 50)
        {
            shootTimer++;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer >= 50)
        {
            player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
            shootTimer = 0;
        }
        
        //Bullets
        for (size_t i = 0; i < player.bullets.size(); i++)
        {
            //Move
            player.bullets[i].bullet.move(0.f,-10.f);

            //Fuera de la ventana
            if (player.bullets[i].bullet.getPosition().x > window->getSize().x)
            {
                player.bullets.erase(player.bullets.begin()+i);
                break;
            }

            //Enemy collision
            for (size_t k = 0; k < enemies.size(); k++)
            {
                if (player.bullets[i].bullet.getGlobalBounds().intersects(enemies[k].enemy.getGlobalBounds()))
                {
                    if (enemies[k].HP <= 1)
                    {
                        score += rand() % 15 + 1;
                        enemies.erase(enemies.begin() + k);
                    }
                        
                    else enemies[k].HP--; //Enemigo recibe daño
                    player.bullets.erase(player.bullets.begin() + i);
                    break;
                }
                
            }
            //Enemy 2 collision
            for (size_t j = 0; j < enemies2.size(); j++)
            {
                if (player.bullets[i].bullet.getGlobalBounds().intersects(enemies2[j].enemy.getGlobalBounds()))
                {
                    if (enemies2[j].HP <= 1)
                    {
                        score += rand() % 15 + 1;
                        enemies2.erase(enemies2.begin() + j);
                    }
                        
                    else enemies2[j].HP--; //Enemigo recibe daño
                    player.bullets.erase(player.bullets.begin() + i);
                    break;
                }
            }
            //Vida collision
            for (size_t l = 0; l < enemies3.size(); l++)
            {
                if (player.bullets[i].bullet.getGlobalBounds().intersects(enemies3[l].enemy.getGlobalBounds()))
                {
                    if (enemies3[l].HP <= 1)
                    {
                        score += 1;
                        enemies3.erase(enemies3.begin() + l);
                    }
                        
                    else enemies3[l].HP--; //Enemigo recibe daño
                    player.bullets.erase(player.bullets.begin() + i);
                    break;
                }
            }
        }

        //Enemy
        if (enemySpawnTimer < 80)
            enemySpawnTimer++;
    
        //Enemigo Spawnea
        if (enemySpawnTimer >= 80)
        {
            enemies.push_back(Enemy(&enemyTex, window->getSize()));
            enemySpawnTimer = 0;
        }
        
        for (size_t i = 0; i < enemies.size(); i++)
        {
            enemies[i].enemy.move(-2.5f,0.f);
            if (enemies[i].enemy.getPosition().x <= 0 - enemies[i].enemy.getGlobalBounds().width)
            {
                enemies.erase(enemies.begin() + i);
                
                break;
            }
                
            if(enemies[i].enemy.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
            {
                enemies.erase(enemies.begin() + i);
                player.HP--; //Damage
                sfx->PlaySFX(4);
                break;
            }
        }

        if (enemySpawnTimer2 < 60)
            enemySpawnTimer2++;

        //Enemigo 2 Spawnea
        if (enemySpawnTimer2 >= 60)
        {
            enemies2.push_back(Enemy(&enemyTex2, window->getSize()));
            enemySpawnTimer2 = 0;
        }
        
        for (size_t i = 0; i < enemies2.size(); i++)
        {
            enemies2[i].enemy.move(-3.f,0.f);
            if (enemies2[i].enemy.getPosition().x <= 0 - enemies2[i].enemy.getGlobalBounds().width)
            {
                enemies2.erase(enemies2.begin() + i);
                break;
            }
                
            if(enemies2[i].enemy.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
            {
                enemies2.erase(enemies2.begin() + i);
                player.HP--; //Damage
                sfx->PlaySFX(4);
                break;
            }
        }

        if (enemySpawnTimer3 < 2000)
        enemySpawnTimer3++;

        //Vida Spawnea
        if (enemySpawnTimer3 >= 2000)
        {
            enemies3.push_back(Enemy(&enemyTex3, window->getSize()));
            enemySpawnTimer3 = 0;
        }
        
        for (size_t i = 0; i < enemies3.size(); i++)
        {
            enemies3[i].enemy.move(-2.f,0.f);
            if (enemies3[i].enemy.getPosition().x <= 0 - enemies3[i].enemy.getGlobalBounds().width)
            {
                enemies3[i].HPMax=1;
                enemies3.erase(enemies3.begin() + i);
                break;
                
            }
                
            if(enemies3[i].enemy.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
            {
                enemies3.erase(enemies3.begin() + i);
                player.HP++; //Vida
                sfx->PlaySFX(6);
                break;
            }
        }

        //UI Update
       
        
        window->clear(*(new sf::Color(150, 100, 0, 255)));//limpiar la pantalla
        
        window->draw(background);

        //Player draw
        window->draw(player.shape);

        for (size_t i = 0; i < player.bullets.size(); i++)
        {
           window->draw(player.bullets[i].bullet);
        }

        //Enemy draw
        for (size_t i = 0; i < enemies.size(); i++)
        {
            EhpText.setPosition(enemies[i].enemy.getPosition().x, enemies[i].enemy.getPosition().y - EhpText.getGlobalBounds().height);
            EhpText.setString(std::to_string(enemies[i].HP) = "Enemigo/" + std::to_string(enemies[i].HPMax));
            window->draw(EhpText);
            window->draw(enemies[i].enemy);
        }
        
        //Enemy2 draw
        for (size_t i = 0; i < enemies2.size(); i++)
        {
            EhpText2.setPosition(enemies2[i].enemy.getPosition().x, enemies2[i].enemy.getPosition().y - EhpText2.getGlobalBounds().height);
            EhpText2.setString(std::to_string(enemies2[i].HP) = "Enemigo/" + std::to_string(enemies2[i].HPMax));
            window->draw(EhpText2);
            window->draw(enemies2[i].enemy);
        }
        //Vida  draw
        for (size_t i = 0; i < enemies3.size(); i++)
        {
            EhpText3.setPosition(enemies3[i].enemy.getPosition().x, enemies3[i].enemy.getPosition().y - EhpText3.getGlobalBounds().height);
            EhpText3.setString("+" + std::to_string(enemies3[i].HP));
            window->draw(EhpText3);
            window->draw(enemies3[i].enemy);
        }
        scoreText.setString("Score: " + std::to_string(score) + " /    Objetivo: Obtener 150 puntos y detener al boss" );
        instriccionesText.setString("Ataque: SPACE / Movimiento: WASD");
        scoreEndText.setString("Tu Score final fue: " + std::to_string(score));
        scoreEndText2.setString("Tu Score final fue: " + std::to_string(score));
        }
        //UI

        if (score >= 150)
        {
            window->draw(BhpText);
            window->draw(boss.bossT);
            //sfx->PlaySFX(1);
            //window->draw(gameOverText);

        for (size_t i = 0; i < player.bullets.size(); i++)
        {
            //Boss collision
            if (player.bullets[i].bullet.getGlobalBounds().intersects(boss.bossT.getGlobalBounds()))
            {
                if (boss.HP <= 0)
                {
                    player.HP = 999999;

                }
                else boss.HP--; //Enemigo recibe daño
                sfx->PlaySFX(7);
                player.bullets.erase(player.bullets.begin() + i);
                break;
            }
        }
        }
        window->draw(scoreText);
        window->draw(hpText);
        window->draw(instriccionesText);
        if (boss.HP <= 0)
        {
            player.HP = 999999;
            window->draw(winnerscreen);
            window->draw(gameOverText);

            window->draw(scoreEndText);
            player.shape.setPosition(4000,4000);
        }
        if (player.HP <= 0)
        {
            window->draw(gameOver);

            window->draw(scoreEndText2);
            musicaBackground->stop();
            player.shape.setPosition(4000,4000);
        }

        window->display(); //mostrar en pantalla lo que se va dibujar

        sf::Time timeElapsed = clock->getElapsedTime();
        deltaTime = timeElapsed.asMilliseconds();
        world->ClearForces();
        world->Step(1.f / 100 * deltaTime, 8, 8);
        clock->restart();
    }
    return 0;
}