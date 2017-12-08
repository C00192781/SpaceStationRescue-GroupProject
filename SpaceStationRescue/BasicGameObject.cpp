#include "BasicGameObject.h"

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
