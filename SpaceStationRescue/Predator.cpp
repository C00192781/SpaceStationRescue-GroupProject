#include "Predator.h"

Predator::Predator() : BaseAI(1)
{ 

}

Predator::Predator(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f maxSpeed, sf::Texture *predatorTexture)
{
	m_position = position;
	m_velocity = velocity;
	currentState = (AIState)1;
	m_maxSpeed = maxSpeed;
	SetupSprite(predatorTexture);
}

Predator::~Predator()
{

}