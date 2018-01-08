#include "Bullet.h"

#include <iostream>

Bullet::Bullet()
{
}

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f maxSpeed, float orientation, sf::Texture *bulletTexture)
{
	conversion = 180 / 3.14159265359;
	m_position = pos;
	m_velocity = vel;
	m_maxSpeed = maxSpeed;
	m_orientation = orientation;
	SetupSprite(bulletTexture);
	
}

Bullet::~Bullet()
{
}

void Bullet::BulletHandler(std::vector<Bullet> *bullets, sf::Vector2f screenBounds)
{
	m_position = m_sprite.getPosition();
	m_velocity = velocityHandler(m_orientation);
	m_velocity.x = m_velocity.x * m_maxSpeed.x; 
	m_velocity.y = m_velocity.y * m_maxSpeed.y;
	m_sprite.move(m_velocity);

	m_sprite.setOrigin(m_sprite.getTexture()->getSize().x, m_sprite.getTexture()->getSize().y);
	m_sprite.setRotation(m_orientation * conversion);
	Bounds(bullets, screenBounds);
}

sf::Vector2f Bullet::velocityHandler(float orientation)
{
	sf::Vector2f temp;
	temp.x = sin(orientation);
	temp.y = -cos(orientation);
	return temp;
}

void Bullet::Bounds(std::vector<Bullet> *bullets, sf::Vector2f screenBounds)
{
	for (int i = 0; i < bullets->size(); i++)
	{
		if (m_position.x > 17280 || m_position.x < 0 
			|| m_position.y > 9720 || m_position.y < 0)
		{
			// erase element that has gone out of bounds 
			bullets->erase(bullets->begin() + i);
		}
	}
}
