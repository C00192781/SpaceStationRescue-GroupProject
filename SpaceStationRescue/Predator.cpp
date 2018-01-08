#include "Predator.h"

Pathfinding pathfinding;

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
	m_sprite.setOrigin(m_sprite.getTexture()->getSize().x/2, m_sprite.getTexture()->getSize().y/2);
}

Predator::~Predator()
{

}

void Predator::Update(Graph<pair<string, int>, int>* graph, std::vector<sf::Vector2f> *waypoints, std::vector<Wall>* walls)
{
	pathfinding.RunAStar(graph, waypoints);
}
