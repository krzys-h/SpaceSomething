#pragma once

#include "GameSprite.h"

class Enemy : public GameSprite
{
public:
    Enemy(sf::Vector2f pos, sf::Color color = sf::Color(0, 255, 0));
    virtual ~Enemy() {};

    virtual void update(sf::Time gameTime, sf::Time frameDelta) override;

private:
    sf::Vector2f startPos;
};


