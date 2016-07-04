#pragma once

#include <SFML/Graphics.hpp>

class GameSprite : public sf::Sprite
{
public:
    virtual ~GameSprite() {};

    virtual void update(sf::Time gameTime, sf::Time frameDelta) {};
};


