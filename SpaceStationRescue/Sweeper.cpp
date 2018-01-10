#include "Sweeper.h"

Sweeper::Sweeper() : BaseAI(1)
{
	startPoint = 0;
}

Sweeper::Sweeper(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f maxSpeed, sf::Texture *predatorTexture)
{
	m_position = position;
	m_velocity = velocity;
	currentState = (AIState)1;
	m_maxSpeed = maxSpeed;
	SetupSprite(predatorTexture);
	m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
	timer = 600;
	startPoint = 0;
	states = PathfindingStates::SeekWaypoint;
}

Sweeper::~Sweeper()
{

}

void Sweeper::Update(Graph<pair<string, int>, int>* graph, std::vector<sf::Vector2f> *waypoints, std::vector<Wall>* walls, sf::Vector2f playerPos)
{


	if (states == PathfindingStates::Following)
	{
		if (((m_position.x + (m_sprite.getGlobalBounds().width / 2) + 10 > m_targetPosition.x) && (m_position.x - 10 < m_targetPosition.x))
			&& ((m_position.y + (m_sprite.getGlobalBounds().height / 2) + 10 > m_targetPosition.y) && (m_position.y - 10 < m_targetPosition.y)))
		{
			//get index of waypoint of target position and set it as start point for astar
			startPoint = pathfinding.getWaypointIndex(waypoints, m_targetPosition);
			if (startPoint != endPoint)
			{
				m_targetPosition = pathfinding.RunAStar(graph, waypoints, &startPoint, &endPoint);
				std::cout << m_targetPosition.x << " " << m_targetPosition.y << std::endl;
			}
			else
			{
				//Set new waypoint
				endPoint = GetRandomWaypoint(startPoint, waypoints->size());
			}
		}
	}
	else if (states == PathfindingStates::SeekWaypoint)
	{
		m_targetPosition = pathfinding.searchNearestWaypoint(waypoints, m_position);
		if (((m_position.x + (m_sprite.getGlobalBounds().width / 2) + 10 > m_targetPosition.x) && (m_position.x - 10 < m_targetPosition.x))
			&& ((m_position.y + (m_sprite.getGlobalBounds().height / 2) + 10 > m_targetPosition.y) && (m_position.y - 10 < m_targetPosition.y)))
		{
			//get index of waypoint of target position and set it as start point for astar
			startPoint = pathfinding.getWaypointIndex(waypoints, m_targetPosition);
			endPoint = GetRandomWaypoint(startPoint,waypoints->size());
			states = PathfindingStates::Following;
		}
	}
	Seek();
	WallAvoidance(walls);

	m_sprite.move(m_velocity);
	m_position = m_sprite.getPosition();
}

int Sweeper::GetRandomWaypoint(int currentWaypoint, int numWaypoints)
{
	int randomWaypoint = currentWaypoint;
	while (randomWaypoint == currentWaypoint)
	{
		randomWaypoint = rand() % numWaypoints;
	}
	return randomWaypoint;
}
