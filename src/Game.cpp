#include "Game.h"

#include "GameResources.h"
#include "objects/Player.h"
#include "objects/Enemy.h"
#include "objects/Bullet.h"
#include "stringutils.h"

#include <SFGUI/Button.hpp>
#include <SFGUI/Table.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/Spinner.hpp>
#include <iomanip>
#include <sstream>

void Game::run()
{
    {
        mainMenu = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
        auto startGameButton = sfg::Button::Create(L"Rozpocznij grę");
        startGameButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&Game::startGame, this));
        mainMenu->Pack(startGameButton);
        auto settingsButton = sfg::Button::Create(L"Ustawienia");
        settingsButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&Game::openSettings, this));
        mainMenu->Pack(settingsButton);
        auto exitButton = sfg::Button::Create(L"Wyjście");
        exitButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&Game::exitGame, this));
        mainMenu->Pack(exitButton);
        desktop.Add(mainMenu);
    }

    {
        settings = sfg::Window::Create(sfg::Window::Style::TOPLEVEL | sfg::Window::Style::CLOSE);
        settings->GetSignal(sfg::Window::OnCloseButton).Connect(std::bind(&Game::closeSettings, this));
        settings->SetTitle(L"Ustawienia");
        settings->Show(false);

        auto table = sfg::Table::Create();
        settings->Add(table);

        table->Attach(sfg::Label::Create(L"Ilość punktów za przeciwnika:"), sf::Rect<sf::Uint32>(0, 0, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(3.f, 3.f));
        pointsPerKillEntry = sfg::Entry::Create(L"100");
        pointsPerKillEntry->SetRequisition(sf::Vector2f(90.0f, 0.0f));
        table->Attach(pointsPerKillEntry, sf::Rect<sf::Uint32>(1, 0, 3, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(3.f, 3.f));

        table->Attach(sfg::Label::Create(L"Kolor przeciwników:"), sf::Rect<sf::Uint32>(0, 1, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(3.f, 3.f));
        enemyColorREntry = sfg::Entry::Create(L"0");
        enemyColorREntry->SetRequisition(sf::Vector2f(30.0f, 0.0f));
        table->Attach(enemyColorREntry, sf::Rect<sf::Uint32>(1, 1, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(3.f, 3.f));
        enemyColorGEntry = sfg::Entry::Create(L"255");
        enemyColorGEntry->SetRequisition(sf::Vector2f(30.0f, 0.0f));
        table->Attach(enemyColorGEntry, sf::Rect<sf::Uint32>(2, 1, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(3.f, 3.f));
        enemyColorBEntry = sfg::Entry::Create(L"0");
        enemyColorBEntry->SetRequisition(sf::Vector2f(30.0f, 0.0f));
        table->Attach(enemyColorBEntry, sf::Rect<sf::Uint32>(3, 1, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(3.f, 3.f));

        desktop.Add(settings);
    }

    GameResources::load();

    window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(500, 1000), "game"));
    window->setVerticalSyncEnabled(true);
    window->setKeyRepeatEnabled(false);
    sf::View gameView = calculateGameView(500, 1000);
    sf::View uiView = calculateUIView(500, 1000);

    sf::Clock gameTimeClock;
    sf::Clock frameTimeClock;

    while (window->isOpen())
    {
        sf::Time gameTime = gameTimeClock.getElapsedTime();
        sf::Time frameDelta = frameTimeClock.restart();

        sf::Event event;
        while (window->pollEvent(event))
        {
            desktop.HandleEvent(event);

            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::Resized)
            {
                gameView = calculateGameView(event.size.width, event.size.height);
                uiView = calculateUIView(event.size.width, event.size.height);
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    bullets.push_back(addObject(player->createBullet()));
                }
            }
        }

        desktop.Update(frameDelta.asSeconds());

        for (auto& s : objects) s->update(gameTime, frameDelta);

        while(checkCollisions());

        if (pointsText)
        {
            std::stringstream ss;
            ss << std::setfill('0') << std::setw(10) << points;
            pointsText->setString(ss.str());
        }


        window->clear(sf::Color::Black);

        window->setView(gameView);
        for (const auto& s : objects) window->draw(*s.get());

        window->setView(uiView);
        window->resetGLStates();
        if (pointsText)
        {
            window->draw(*pointsText);
        }
        sfgui.Display(*window);

        window->display();
    }
}

bool Game::checkCollisions()
{
    for (auto bullet = bullets.begin(); bullet != bullets.end(); ++bullet)
    {
        for (auto enemy = enemies.begin(); enemy != enemies.end(); ++enemy)
        {
            if ((*bullet)->getGlobalBounds().intersects((*enemy)->getGlobalBounds()))
            {
                objects.erase(remove_if(objects.begin(), objects.end(), [&](const std::unique_ptr<GameSprite>& x) { return x.get() == *enemy; }));
                objects.erase(remove_if(objects.begin(), objects.end(), [&](const std::unique_ptr<GameSprite>& x) { return x.get() == *bullet; }));
                enemies.erase(enemy);
                bullets.erase(bullet);

                sound.setBuffer(GameResources::popSound);
                sound.play();

                points += pointsPerKill;

                return true;
            }
        }
    }
    return false;
}

sf::View Game::calculateGameView(int width, int height)
{
    float x = 1000.f/height * width;
    float y = 1000.f;
    if (x < 500)
    {
        float factor = 500.f/x;
        x *= factor;
        y *= factor;
    }
    return sf::View(
        sf::Vector2f(0, 500),
        sf::Vector2f(x, y)
    );
}

sf::View Game::calculateUIView(int width, int height)
{
    return sf::View(sf::FloatRect(0, 0, width, height));
}

void Game::startGame()
{
    settings->Show(false);
    mainMenu->Show(false);

    pointsPerKill = from_string<int>(pointsPerKillEntry->GetText());
    sf::Color enemyColor(
            from_string<int>(enemyColorREntry->GetText()),
            from_string<int>(enemyColorGEntry->GetText()),
            from_string<int>(enemyColorBEntry->GetText())
    );

    player = createObject<Player>();

    for (int y = 100; y <= 300; y += 50)
    {
        for (int x = -175; x <= 175-25; x += 50)
        {
            sf::Vector2f pos(x+((y % 100) == 0 ? 25 : 0), y);
            enemies.push_back(createObject<Enemy>(pos, enemyColor));
        }
    }

    pointsText = std::unique_ptr<sf::Text>(new sf::Text());
    pointsText->setFont(GameResources::font);
    pointsText->setString("?????????");
    pointsText->setCharacterSize(24);
    pointsText->setColor(sf::Color::White);
    pointsText->setPosition(5, 5);
}

void Game::openSettings()
{
    settings->Show(true);
    desktop.BringToFront(settings);
}

void Game::closeSettings()
{
    settings->Show(false);
}

void Game::exitGame()
{
    window->close();
}



