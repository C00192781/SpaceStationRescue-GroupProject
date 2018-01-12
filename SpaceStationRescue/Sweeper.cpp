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
	searching = true;
	lineOfSightRadius = 500;
	lineOfSightAngle = 30;
	SetupLOS();
	line = sf::VertexArray(sf::Lines, 2);
	line[0].position = sf::Vector2f(0,0);
	line[1].position = sf::Vector2f(0,0);
	fleeing = false;
	m_alive = true;
	workerCount = 0;
	radarImage = sf::CircleShape(75);
	radarImage.setFillColor(sf::Color(150, 50, 250));
	radarImage.setOrigin(radarImage.getLocalBounds().width / 2, radarImage.getLocalBounds().height / 2);
}

Sweeper::~Sweeper()
{

}

void Sweeper::Update(Graph<pair<string, int>, int>* graph, std::vector<sf::Vector2f> *waypoints, std::vector<Wall>* walls, sf::Vector2f playerPos, std::vector<Worker>* workers, std::vector<Bullet>* bullets)
{
		if (states == PathfindingStates::Following)
		{
			if (searching == true)
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
			else
			{

			}
		}
		else if (states == PathfindingStates::SeekWaypoint)
		{
			if (searching == true)
			{
				m_targetPosition = pathfinding.searchNearestWaypoint(waypoints, m_position);

				if (((m_position.x + (m_sprite.getGlobalBounds().width / 2) + 10 > m_targetPosition.x) && (m_position.x - 10 < m_targetPosition.x))
					&& ((m_position.y + (m_sprite.getGlobalBounds().height / 2) + 10 > m_targetPosition.y) && (m_position.y - 10 < m_targetPosition.y)))
				{
					//get index of waypoint of target position and set it as start point for astar
					startPoint = pathfinding.getWaypointIndex(waypoints, m_targetPosition);
					endPoint = GetRandomWaypoint(startPoint, waypoints->size());
					states = PathfindingStates::Following;
				}
			}
			else
			{

			}
		}
		else if (states == PathfindingStates::Fleeing)
		{
			if (searching == true)
			{
				if (((m_position.x + (m_sprite.getGlobalBounds().width / 2) + 10 > m_targetPosition.x) && (m_position.x - 10 < m_targetPosition.x))
					&& ((m_position.y + (m_sprite.getGlobalBounds().height / 2) + 10 > m_targetPosition.y) && (m_position.y - 10 < m_targetPosition.y)))
				{
					//get index of waypoint of target position and set it as start point for astar
					m_targetPosition = pathfinding.searchNearestWaypoint(waypoints, m_position);
					startPoint = pathfinding.getWaypointIndex(waypoints, m_targetPosition);
					if (startPoint != endPoint)
					{
						m_targetPosition = pathfinding.RunAStar(graph, waypoints, &startPoint, &endPoint);
					}
					else
					{
						//Set new waypoint
						endPoint = GetRandomWaypoint(startPoint, waypoints->size());
					}
				}
			}
		}

		if (searching == true)
		{
			if (lineOfSight.getGlobalBounds().contains(playerPos))
			{
				//plot esacpe route
				states = PathfindingStates::Fleeing;
				endPoint = 3;
			}
			else
			{
				if (LookForWorker(walls, playerPos, workers) == true)
				{
					searching = false;
				}
			}
		}
		else if(fleeing == false)
		{
			m_targetPosition = workers->at(targetWorkerIndex).getPosition();
			if (((m_position.x + (m_sprite.getGlobalBounds().width / 2) + 10 > m_targetPosition.x) && (m_position.x - 10 < m_targetPosition.x))
				&& ((m_position.y + (m_sprite.getGlobalBounds().height / 2) + 10 > m_targetPosition.y) && (m_position.y - 10 < m_targetPosition.y)))
			{
				//workers->at(targetWorkerIndex).SetMaxSpeed(sf::Vector2f(0, 0));
				//workers->at(targetWorkerIndex).SetPosition(sf::Vector2f(-1000, -1000));
				workers->erase(workers->begin() + (targetWorkerIndex));
				searching = true;
				workerCount += 1;
				states = SeekWaypoint;
			}
		}

	Seek();
	WallAvoidance(walls);

	for (int i = 0; i < bullets->size(); i++)
	{
		if (CollisionDetection(bullets->at(i).getSprite()) == true)
		{
			if (i != bullets->size() - 1)
			{
				std::swap(bullets->at(i), bullets->at(bullets->size() - 1));
			}
			bullets->pop_back();
			m_alive = false;
		}
	}
	
	m_sprite.move(m_velocity);
	m_position = m_sprite.getPosition();
	lineOfSight.setPosition(m_position);
	lineOfSight.setRotation(m_sprite.getRotation()-180);
	radarImage.setPosition(m_position);
}

bool Sweeper::LookForWorker(std::vector<Wall>* walls, sf::Vector2f playerPos, std::vector<Worker>* workers)
{
	bool workerFound = false;
	for (int i = 0; i < workers->size(); i++)
	{
		//if worker in los
		if (lineOfSight.getGlobalBounds().intersects(workers->at(i).getSprite().getGlobalBounds()))
		{
			//draw line between sweeper and worker
			line[0].position = sf::Vector2f(m_position);
			line[1].position = sf::Vector2f(workers->at(i).getPosition());
			for (int j = 0; j < walls->size(); j++)
			{
				//check to see if wall intersects with line
				if (line.getBounds().intersects(walls->at(j).getSprite().getGlobalBounds()) == true)
				{
					//ignore worker
				}
				else
				{
					//return worker as target
					targetWorkerIndex = i;
					workerFound = true;
				}
			}
		}

	}
	return workerFound;
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

void Sweeper::SetupLOS()
{
	sf::Vector2f direction = Normalize(m_velocity);
	float length = sqrt((direction.x * direction.x) + (direction.y * direction.y));
	length = length * lineOfSightRadius;


	float angleLeft = m_sprite.getRotation() - lineOfSightAngle;
	angleLeft = angleLeft *(3.1415926 / 180);
	sf::Vector2f leftView;
	leftView.x = m_position.x + length * cosf(angleLeft);
	leftView.y = m_position.y + length * sinf(angleLeft);

	float angleRight = m_sprite.getRotation() + lineOfSightAngle;
	angleRight = angleRight *(3.1415926 / 180);
	sf::Vector2f rightView;
	rightView.x = m_position.x + length * cosf(angleRight);
	rightView.y = m_position.y + length * sinf(angleRight);

	lineOfSight = sf::CircleShape(lineOfSightRadius, 3);
	lineOfSight.setFillColor(sf::Color::Green);
	lineOfSight.setOrigin(lineOfSightRadius, 0);
	lineOfSight.setPosition(m_position);
}

void Sweeper::Draw(sf::RenderWindow *window)
{
	window->draw(m_sprite);
	//window->draw(lineOfSight);
	//window->draw(line);
}

void Sweeper::RadarDraw(sf::RenderWindow * window)
{
	window->draw(radarImage);
}
