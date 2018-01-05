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
	SetupSprite(wallTexture);

}

Wall::~Wall()
{
}
