#include "Enemy.h"

#include "GameResources.h"

Enemy::Enemy(sf::Vector2f pos, sf::Color color)
{
    setTexture(GameResources::enemy);
    setOrigin(8, 8);
    setPosition(pos);
    setScale(1.5f, 1.5f);
    setColor(color);
    startPos = pos;
}

void Enemy::update(sf::Time gameTime, sf::Time frameDelta)
{
    sf::Vector2f pos = startPos;
    pos.x += round(sin(gameTime.asSeconds() * 3.14 / 2) * 25);
    setPosition(pos);
}





