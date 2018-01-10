#include "BasicGameObject.h"

#include <iostream>



BasicGameObject::BasicGameObject()
{

}

BasicGameObject::BasicGameObject(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f maxSpeed, float orientation, sf::Texture tex)
{
	m_position = pos;
	m_velocity = vel;
	m_maxSpeed = maxSpeed;
	m_orientation = orientation;
	m_texture = tex;
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
}

BasicGameObject::~BasicGameObject()
{
}

void BasicGameObject::Update()
{
	m_position += m_velocity;
}

void BasicGameObject::Draw(sf::RenderWindow *window)
{
	window->draw(m_sprite);
}

bool BasicGameObject::CollisionDetection(sf::Sprite sprite)
{
	if (sprite.getLocalBounds().intersects(m_sprite.getLocalBounds()))
	{
		return true;
	}
	else
	{
		return false;
	}

}

void BasicGameObject::SetupSprite(sf::Texture* texture)
{
	m_sprite.setTexture(*texture);

	//m_sprite.getTexture();
	m_sprite.setPosition(m_position);
	
}


sf::Vector2f BasicGameObject::getPosition()
{
	return m_position;
}

void BasicGameObject::SetPosition(sf::Vector2f newPosition)
{
	m_position = newPosition;
	m_sprite.setPosition(m_position);
}

sf::Vector2f BasicGameObject::getVelocity()
{
	return m_velocity;
}

void BasicGameObject::SetVelocity(sf::Vector2f newVelocity)
{
	m_velocity = newVelocity;
}

sf::Vector2f BasicGameObject::getMaxSpeed()
{
	return m_maxSpeed;
}

void BasicGameObject::SetMaxSpeed(sf::Vector2f newMaxSpeed)
{
	m_maxSpeed = newMaxSpeed;
}

float BasicGameObject::getOrientation()
{
	return m_orientation;
}

sf::Sprite& BasicGameObject::getSprite()
{
	return m_sprite;
}
