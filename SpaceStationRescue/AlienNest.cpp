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
}

AlienNest::~AlienNest()
{
}

void AlienNest::Update(std::vector<Interceptor>* interceptors, sf::Vector2f position, sf::Texture * interceptorTexture)
{
	if (m_alive == true)
	{
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

		for (int i = 0; i < interceptors->size(); i++)
		{
			if (interceptors->at(i).getTimeAlive() == range) // 5 seconds
			{
				//setAlive(false);
				//interceptors->erase(interceptors->begin() + i);
				interceptors->at(i).SetPosition(sf::Vector2f(-3000, -3000));
				interceptors->at(i).setAlive(false);
				missileCounter = 0;
			}
		}
	}
}
