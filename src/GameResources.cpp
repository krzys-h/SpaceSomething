#include "GameResources.h"

sf::Texture GameResources::player;
sf::Texture GameResources::enemy;
sf::Texture GameResources::bullet;
sf::Font GameResources::font;
sf::SoundBuffer GameResources::popSound;

void GameResources::load()
{
    player.loadFromFile("player.png");
    enemy.loadFromFile("enemy.png");
    bullet.loadFromFile("bullet.png");
    font.loadFromFile("dvu_sans.ttf");
    popSound.loadFromFile("pop.wav");
}
