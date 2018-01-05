#include "Wall.h"

#include <iostream>

Wall::Wall()
{
}

Wall::Wall(sf::Vector2f pos, sf::Vector2f size, float orientation, sf::Texture *wallTexture)
{
	m_position = pos;
	m_size = size;
	m_orientation = orientation;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(sf::Vector2f(m_size.x / wallTexture->getSize().x, m_size.y / wallTexture->getSize().y));
	m_sprite.setRotation(orientation);
	SetupSprite(wallTexture);
}

Wall::~Wall()
{
}
