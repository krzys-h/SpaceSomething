#include "Player.h"

#include "GameResources.h"
#include "Bullet.h"

const float PLAYER_ACCELERATION = 400.0f;
const float PLAYER_MAX_SPEED = 200.0f;
const float PLAYER_DRAG = 2.0f/PLAYER_MAX_SPEED;

Player::Player()
{
    setTexture(GameResources::player);
    setOrigin(16, 16);
    setPosition(0, 900);
}

void Player::update(sf::Time gameTime, sf::Time frameDelta)
{
    float acceleration = 0.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        acceleration -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        acceleration += 1.0f;
    }

    if (acceleration * velocity <= 0.0f)
    {
        if (velocity > 0) acceleration -= velocity * PLAYER_DRAG;
        if (velocity < 0) acceleration += -velocity * PLAYER_DRAG;
    }

    velocity += acceleration * frameDelta.asSeconds() * PLAYER_ACCELERATION;
    if (velocity > PLAYER_MAX_SPEED) velocity = PLAYER_MAX_SPEED;
    if (velocity < -PLAYER_MAX_SPEED) velocity = -PLAYER_MAX_SPEED;

    sf::Vector2f pos = getPosition();
    pos.x += velocity * frameDelta.asSeconds();
    setPosition(pos);

    setRotation(velocity / PLAYER_MAX_SPEED * 30.f);
}

std::unique_ptr<Bullet> Player::createBullet()
{
    sf::Transform transform = getTransform();
    transform.translate(getOrigin());
    return std::unique_ptr<Bullet>(new Bullet(transform.transformPoint(0, -16), getRotation()));
}


