#pragma once

#include "GameSprite.h"

class Bullet : public GameSprite
{
public:
    Bullet(sf::Vector2f position, float direction);
    virtual ~Bullet() {};

    virtual void update(sf::Time gameTime, sf::Time frameDelta) override;
};


