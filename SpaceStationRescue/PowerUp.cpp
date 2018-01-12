#include "PowerUp.h"

PowerUp::PowerUp()
{

}

PowerUp::~PowerUp()
{

}

PowerUp::PowerUp(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f maxSpeed, sf::Texture* powerUpTexture)
{
	m_position = position;
	m_velocity = velocity;
	m_maxSpeed = maxSpeed;
	m_sprite.setOrigin(32, 32);
	SetupSprite(powerUpTexture);
	m_alive = true;

}