#pragma once

#include "GameSprite.h"

class Bullet;

class Player : public GameSprite
{
public:
    Player();
    virtual ~Player() {};

    std::unique_ptr<Bullet> createBullet();

    virtual void update(sf::Time gameTime, sf::Time frameDelta) override;

private:
    float velocity = 0.0f;
};


