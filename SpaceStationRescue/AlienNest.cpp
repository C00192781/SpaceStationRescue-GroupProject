#include "AlienNest.h"

AlienNest::AlienNest()
{
}

AlienNest::AlienNest(sf::Vector2f pos, sf::Vector2f size, float orientation, sf::Texture * alienNestTexture)
{
	m_position = pos;
	m_size = size;
	m_orientation = orientation;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(sf::Vector2f(m_size.x / alienNestTexture->getSize().x, m_size.y / alienNestTexture->getSize().y));
	m_sprite.setRotation(orientation);
	SetupSprite(alienNestTexture);

	missileCounter = 0;
	range = 500.0f;
	missileInitiated = false;
	startingPosition = pos;
	m_health = 100;
	m_alive = true;

	predatorCounter = 0;
	predatorMax = 3;
	predatorSpawnTimer = 0;

	predatorsCreated = 0;
	predatorIndex = std::vector<int>();
}

AlienNest::~AlienNest()
{
}

void AlienNest::Update(std::vector<Interceptor>* interceptors, sf::Vector2f position, sf::Texture * interceptorTexture,std::vector<Predator>* predators, sf::Texture * predatorTexture)
{
	if (getHealth() <= 0)
	{
		setAlive(false);
	}
	if (m_alive == true)
	{
		if (predatorCounter < predatorMax && predatorSpawnTimer > 180)
		{
			if (predatorsCreated < predatorMax)
			{
				predators->push_back(Predator(sf::Vector2f(getPosition()), sf::Vector2f(0, 0), sf::Vector2f(8, 8), predatorTexture));
				predatorIndex.push_back(predators->size() - 1);
				predatorsCreated++;
			}
			else
			{
				for (int i = 0; i < predatorIndex.size(); i++)
				{
					if (predators->at(predatorIndex.at(i)).getAlive() == false)
					{
						predators->at(predatorIndex.at(i)).setAlive(true);
						predators->at(predatorIndex.at(i)).states = PathfindingStates::SeekWaypoint;
						predators->at(predatorIndex.at(i)).setHealth(100);
						predators->at(predatorIndex.at(i)).SetPosition(getPosition());
						predators->at(predatorIndex.at(i)).SetVelocity(sf::Vector2f(0, 0));
						predators->at(predatorIndex.at(i)).SetMaxSpeed(sf::Vector2f(8, 8));
						break;
					}
				}
			}
			predatorCounter++;
			predatorSpawnTimer = 0;
		}
		predatorSpawnTimer++;
		for (int i = 0; i < predatorIndex.size(); i++)
		{
			if (predators->at(predatorIndex.at(i)).getAlive() == false)
			{
				predatorCounter--;
			}
		}

		float differenceValue = std::numeric_limits<int>::max() - 10000;

		sf::Vector2f difference;

		difference.x = position.x - getPosition().x;
		difference.y = position.y - getPosition().y;

		float diff = sqrtf((difference.x*difference.x) + (difference.y*difference.y));
		if (diff < differenceValue)
		{
			differenceValue = diff;
		}

		if (missileCounter == 0 && differenceValue <= 500 && missileInitiated == false)
		{
			interceptors->push_back(Interceptor(sf::Vector2f(getPosition()), sf::Vector2f(0, 0), sf::Vector2f(8, 8), interceptorTexture));
			missileInitiated = true;
			missileCounter = 1;
		}
		else if (missileCounter == 0 && differenceValue <= 500 && missileInitiated == true)
		{
			for (int i = 0; i < interceptors->size(); i++)
			{
				interceptors->at(i).setTimeAlive(0);
				interceptors->at(i).SetPosition(sf::Vector2f(startingPosition));
				interceptors->at(i).setAlive(true);
			}
			missileCounter = 1;
		}
	}
	for (int i = 0; i < interceptors->size(); i++)
	{
		if (interceptors->at(i).getTimeAlive() == range) // 5 seconds
		{
			interceptors->at(i).SetPosition(sf::Vector2f(-3000, -3000));
			interceptors->at(i).setAlive(false);
			interceptors->at(i).states = PathfindingStates::SeekWaypoint;
			missileCounter = 0;
		}
	}
}
