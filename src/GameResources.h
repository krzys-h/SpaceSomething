#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GameResources
{
public:
    static sf::Texture player;
    static sf::Texture enemy;
    static sf::Texture bullet;
    static sf::Font font;
    static sf::SoundBuffer popSound;

    static void load();
};


