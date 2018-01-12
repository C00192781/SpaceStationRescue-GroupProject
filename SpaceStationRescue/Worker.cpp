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
	radarImage = sf::CircleShape(75);
	radarImage.setFillColor(sf::Color(0,127,14));
	radarImage.setOrigin(radarImage.getLocalBounds().width / 2, radarImage.getLocalBounds().height / 2);
}

Worker::~Worker()
{

}


void Worker::RadarDraw(sf::RenderWindow* window)
{
	radarImage.setPosition(m_position);
	window->draw(radarImage);
}
