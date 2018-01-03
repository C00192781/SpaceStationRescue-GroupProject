#include "Worker.h"

Worker::Worker() : BaseAI(0)
{
	
}

Worker::Worker(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f maxSpeed, sf::Texture* workerTexture)
{
	m_position = position;
	m_velocity = velocity;
	currentState = (AIState)0;
	m_maxSpeed = maxSpeed;
	wanderDistance = 300;
	SetupSprite(workerTexture);
}


Worker::~Worker()
{

}