#include "Floor.h"

#include <iostream>

Floor::Floor()
{
}

Floor::Floor(sf::Vector2f pos, sf::Vector2f size, float orientation, sf::Texture *floorTexture)
{
	m_position = pos;
	m_size = size;
	m_orientation = orientation;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(sf::Vector2f(m_size.x / floorTexture->getSize().x, m_size.y / floorTexture->getSize().y));
	m_sprite.setRotation(orientation);
	SetupSprite(floorTexture);
}

Floor::~Floor()
{
}
