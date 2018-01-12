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
	m_sprite.setOrigin(32, 32);
	SetupSprite(workerTexture);
	m_alive = true;
}


Worker::~Worker()
{

}

//void Worker::Update(sf::Sprite sprite)
//{
//
//}
