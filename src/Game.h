#pragma once

#include "objects/GameSprite.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Box.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Entry.hpp>
#include <set>

class Player;
class Enemy;
class Bullet;

class Game
{
public:
    void run();

    template<typename T, typename... Args>
    T* createObject(Args&&... args)
    {
        T* ptr = new T(std::forward<Args>(args)...);
        objects.push_back(std::unique_ptr<T>(ptr));
        return ptr;
    }

    template<typename T>
    T* addObject(std::unique_ptr<T> obj)
    {
        T* ptr = obj.get();
        objects.push_back(std::move(obj));
        return ptr;
    }


private:
    sf::View calculateGameView(int width, int height);
    sf::View calculateUIView(int width, int height);

    bool checkCollisions();

    void startGame();
    void openSettings();
    void closeSettings();
    void exitGame();

private:
    std::vector<std::unique_ptr<GameSprite>> objects;
    std::vector<Enemy*> enemies;
    std::vector<Bullet*> bullets;
    Player* player;

    std::unique_ptr<sf::RenderWindow> window;

    std::unique_ptr<sf::Text> pointsText;
    int points = 0;

    int pointsPerKill = 100;

    sf::Sound sound;


    sfg::SFGUI sfgui;
    sfg::Desktop desktop;
    sfg::Box::Ptr mainMenu;
    sfg::Window::Ptr settings;

    sfg::Entry::Ptr pointsPerKillEntry;
    sfg::Entry::Ptr enemyColorREntry, enemyColorGEntry, enemyColorBEntry;
};
