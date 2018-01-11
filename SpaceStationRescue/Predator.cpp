#include "Predator.h"

Pathfinding pathfinding;

Predator::Predator() : BaseAI(1)
{ 
	startPoint = 0;
}

Predator::Predator(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f maxSpeed, sf::Texture *predatorTexture)
{
	m_position = position;
	m_velocity = velocity;
	currentState = (AIState)1;
	m_maxSpeed = maxSpeed;
	SetupSprite(predatorTexture);
	m_sprite.setOrigin(m_sprite.getTexture()->getSize().x/2, m_sprite.getTexture()->getSize().y/2);
	timer = 600;
	startPoint = 0;
	states = PathfindingStates::SeekWaypoint;

	m_alive = true;
	m_health = 100;
}

Predator::~Predator()
{

}

void Predator::Update(Graph<pair<string, int>, int>* graph, std::vector<sf::Vector2f> *waypoints, std::vector<Wall>* walls, sf::Vector2f playerPos, std::vector<Bullet>* bullets)
{
	if (m_alive == true)
	{
		if (states == PathfindingStates::Following)
		{
			if (((m_position.x + (m_sprite.getGlobalBounds().width / 2) + 10 > m_targetPosition.x) && (m_position.x - 10 < m_targetPosition.x))
				&& ((m_position.y + (m_sprite.getGlobalBounds().height / 2) + 10 > m_targetPosition.y) && (m_position.y - 10 < m_targetPosition.y)))
			{
				//get index of waypoint of target position and set it as start point for astar
				startPoint = pathfinding.getWaypointIndex(waypoints, m_targetPosition);
				sf::Vector2f waypointPlayer = pathfinding.searchNearestWaypoint(waypoints, playerPos);
				endPoint = pathfinding.getWaypointIndex(waypoints, waypointPlayer);
				if (startPoint != endPoint)
				{
					m_targetPosition = pathfinding.RunAStar(graph, waypoints, &startPoint, &endPoint);
					std::cout << m_targetPosition.x << " " << m_targetPosition.y << std::endl;
				}
				else
				{
					states = PathfindingStates::SeekPlayer;
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
				sf::Vector2f waypointPlayer = pathfinding.searchNearestWaypoint(waypoints, playerPos);
				endPoint = pathfinding.getWaypointIndex(waypoints, waypointPlayer);
				states = PathfindingStates::Following;
			}
		}
		else if (states == PathfindingStates::SeekPlayer)
		{
			m_targetPosition = playerPos;

			sf::Vector2f nearestWaypoint = pathfinding.searchNearestWaypoint(waypoints, m_position);
			sf::Vector2f waypointPlayer = pathfinding.searchNearestWaypoint(waypoints, playerPos);
			startPoint = pathfinding.getWaypointIndex(waypoints, nearestWaypoint);
			endPoint = pathfinding.getWaypointIndex(waypoints, waypointPlayer);
			if (startPoint != endPoint)
			{
				states = PathfindingStates::SeekWaypoint;
			}
		}
		Seek();
		WallAvoidance(walls);

		m_sprite.move(m_velocity);
		m_position = m_sprite.getPosition();
	}

	for (int i = 0; i < bullets->size(); i++)
	{
		if (CollisionDetection(bullets->at(i).getSprite()) == true)
		{
			bullets->erase(bullets->begin() + i);
			m_health -= 25;
		}
	}

	if (m_health <= 0)
	{
		setAlive(false);
	}

	if (getAlive() == false)
	{
		SetPosition(sf::Vector2f(-1000, -1000));
	}
	//if (((m_position.x+(m_sprite.getGlobalBounds().width/2) + 10 > m_targetPosition.x) && (m_position.x - 10 < m_targetPosition.x))
	//	&& ((m_position.y+(m_sprite.getGlobalBounds().height / 2) + 10 > m_targetPosition.y) && (m_position.y - 10 < m_targetPosition.y)))
	//{
	//	if (startPoint == 0)
	//	{
	//		startPoint = 1;
	//	}
	//	else if (startPoint == 1)
	//	{
	//		startPoint = 2;
	//	}
	//	m_targetPosition = pathfinding.RunAStar(graph, waypoints, &startPoint, 3);
	//	std::cout << m_targetPosition.x << " " << m_targetPosition.y << std::endl;
	//	Seek();
	//}

	//WallAvoidance(walls);

}
