#include "Bullet.h"

#include "GameResources.h"

const float BULLET_VELOCITY = 400.f;

Bullet::Bullet(sf::Vector2f position, float direction)
{
    setTexture(GameResources::bullet);
    setPosition(position);
    setRotation(direction);
    setOrigin(8, 8);
    setScale(1.25, 1.25);
}

void Bullet::update(sf::Time gameTime, sf::Time frameDelta)
{
    // TODO: why doesn't getTransform() include getOrigin() ?
    setPosition(getTransform().transformPoint(8, 8-BULLET_VELOCITY * frameDelta.asSeconds()));
}
