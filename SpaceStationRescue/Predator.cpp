#include "Predator.h"

Pathfinding pathfinding;

Predator::Predator() : BaseAI(1)
{ 
	startPoint = 0;
}

Predator::Predator(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f maxSpeed, sf::Texture *predatorTexture, sf::Texture& bulletTex)
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

	bulletTexture = bulletTex;
	predatorBullets = new std::vector<Bullet>();
	bulletTimer = 0;

	m_alive = true;
	m_health = 100;

	radarImage = sf::CircleShape(75);
	radarImage.setFillColor(sf::Color::Red);
	radarImage.setOrigin(radarImage.getLocalBounds().width / 2, radarImage.getLocalBounds().height / 2);
}

Predator::~Predator()
{

}

void Predator::Update(Graph<pair<string, int>, int>* graph, std::vector<sf::Vector2f> *waypoints, std::vector<Wall>* walls, sf::Vector2f playerPos, std::vector<Bullet>* bullets)
{
	bulletHandler();
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
		radarImage.setPosition(m_position);
	}

	for (int i = 0; i < bullets->size(); i++)
	{
		if (CollisionDetection(bullets->at(i).getSprite()) == true)
		{
			if (i != bullets->size() - 1)
			{
				std::swap(bullets->at(i), bullets->at(bullets->size() - 1));
			}
			bullets->pop_back();
			m_health -= 25;
		}
	}

	//for (int i = 0; i < predatorBullets->size(); i++)
	//{
	//	if (CollisionDetection(player.getSprite()) == true)
	//	{
	//		if (i != predatorBullets->size() - 1)
	//		{
	//			std::swap(predatorBullets->at(i), predatorBullets->at(predatorBullets->size() - 1));
	//		}
	//		predatorBullets->pop_back();
	//		m_health -= 25;
	//	}
	//}

	// predatorBullets

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

void Predator::RadarDraw(sf::RenderWindow * window)
{
	if (m_alive == true)
	{
		window->draw(radarImage);
	}
}

void Predator::bulletHandler()
{
	// ADDING BULLETS 
	if (states == PathfindingStates::Following)
	{
		bulletTimer++;
		if (bulletTimer == 10)
		{
			predatorBullets->push_back(Bullet(sf::Vector2f(getPosition().x, getPosition().y), getVelocity(), sf::Vector2f(15, 15), getSprite().getRotation() * 3.14159265359 / 180, &bulletTexture));
			bulletTimer = 0;
		}
	}

	for (int i = 0; i < predatorBullets->size(); i++)
	{
		predatorBullets->at(i).BulletHandler(predatorBullets, sf::Vector2f(1920, 1080));
	}

	for (int i = 0; i < predatorBullets->size(); i++)
	{
		predatorBullets->at(i).Update();
	}
}


void Predator::Draw(sf::RenderWindow * window)
{
	window->draw(m_sprite);
	for (int i = 0; i < predatorBullets->size(); i++)
	{
		window->draw(predatorBullets->at(i).getSprite());
	}
}
