#include "BasicAI.h"

BaseAI::BaseAI()
{
	m_position = sf::Vector2f(500, 700);
	m_velocity = sf::Vector2f(1.0f, 1.0f);
	currentState = AIState::WANDER;
	m_maxSpeed = sf::Vector2f(3.0f,3.0f);
	wanderDistance = 300;
}

BaseAI::BaseAI(int AISTATE)
{
	m_position = sf::Vector2f(500, 700);
	m_velocity = sf::Vector2f(1.0f, 1.0f);
	currentState = (AIState)AISTATE;
	m_maxSpeed = sf::Vector2f(3.0f, 3.0f);
	wanderDistance = 300;
}

BaseAI::~BaseAI()
{
}

void BaseAI::Update(sf::Vector2f targetPosition, sf::Vector2f targetVelocity, std::vector<Wall> * walls)
{
	SetTargetPosition(targetPosition);
	SetTargetVelocity(targetVelocity);
	if (currentState == AIState::WANDER)
	{
		Wander();
	}
	else if (currentState == AIState::SEEK)
	{
		Seek();
	}
	else if (currentState == AIState::FLEE)
	{
		Flee();
	}
	else if (currentState == AIState::ARRIVE)
	{
		Arrive();
	}
	else if (currentState == AIState::PURSUE)
	{
		Pursue();
	}
	WallAvoidance(walls);
	m_sprite.move(m_velocity);
	m_position = m_sprite.getPosition();
}

float BaseAI::GetNewOrientation()
{
	float length = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));

	if (length > 0)
	{
		return atan2(m_velocity.x, -m_velocity.y);
	}
	else
	{
		return m_currentOrientation;
	}
}

sf::Vector2f BaseAI::Normalize(sf::Vector2f &velocity)
{
	sf::Vector2f normal;

	float length = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
	if (length > 0)
	{
		normal.x = velocity.x / length;
		normal.y = velocity.y / length;
	}
	else
	{
		normal.x = 0;
		normal.y = 0;
	}

	return normal;
}

void BaseAI::Seek()
{
	m_velocity = m_targetPosition - m_position;
	m_velocity = Normalize(m_velocity);
	m_velocity.x = m_velocity.x * m_maxSpeed.x;
	m_velocity.y = m_velocity.y * m_maxSpeed.y;
	m_sprite.setRotation((GetNewOrientation()) * RadiansToDegrees);
}

void BaseAI::Wander()
{
	sf::Time timeInDirection = wanderTimer.getElapsedTime();
	if (timeInDirection.asSeconds() >= 0.3)
	{
		float radius = 100;

		direction = Normalize(m_velocity);
		sf::Vector2f point = direction * wanderDistance;
		point += m_position;

		float angle = (rand() % 361) * DegreesToRadians;
		m_targetPosition.x = radius * sin(angle) + point.x;
		m_targetPosition.y = radius * cos(angle) + point.y;

		Seek();
		wanderTimer.restart();
	}
}

void BaseAI::Flee()
{
	m_velocity = m_position - m_targetPosition;
	m_velocity = Normalize(m_velocity);
	m_velocity.x = m_velocity.x * m_maxSpeed.x;
	m_velocity.y = m_velocity.y * m_maxSpeed.y;
	m_sprite.setRotation((GetNewOrientation()) * RadiansToDegrees);
}

void BaseAI::Arrive()
{
	float timeToTarget = 0.1f;
	m_velocity = m_targetPosition - m_position;
	m_velocity *= timeToTarget;

	float length = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	float maxSpeed = sqrt((m_maxSpeed.x*m_maxSpeed.x) + (m_maxSpeed.y*m_maxSpeed.y));
	if (length > maxSpeed)
	{
		m_velocity = Normalize(m_velocity);
		m_velocity.x *= m_maxSpeed.x;
		m_velocity.y *= m_maxSpeed.y;
	}

	m_sprite.setRotation((GetNewOrientation())* RadiansToDegrees);
}

void BaseAI::Pursue()
{
	float timeToTarget = 0.0f;
	float maxTimeToTarget = 4.0f;

	direction = m_targetPosition - m_position;
	m_distance = sqrt((direction.x * direction.x) + (direction.y * direction.y));
	m_speed = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	if (m_speed <= m_distance / maxTimeToTarget)
	{
		timeToTarget = maxTimeToTarget;
	}
	else
	{
		timeToTarget = m_distance / m_speed;
	}
	m_targetPosition = m_targetPosition + m_targetVelocity * timeToTarget;

	Arrive();
}

void BaseAI::SetTargetPosition(sf::Vector2f newTargetPosition)
{
	m_targetPosition = newTargetPosition;
}

void BaseAI::SetTargetVelocity(sf::Vector2f newTargetVelocity)
{
	m_targetVelocity = newTargetVelocity;
}

void BaseAI::WallAvoidance(std::vector<Wall> * walls)
{
	float lookahead = 100;
	float avoidDistance = 50;
	sf::Vector2f rayVector = m_velocity;
	rayVector = Normalize(rayVector);
	rayVector = rayVector * lookahead;
	BasicCollision collision = WillCollideWall(rayVector, walls);
	if (collision.willCollide == true)
	{
		sf::Vector2f target = collision.position + (collision.normal * avoidDistance);
		m_targetPosition = target;
		Seek();
	}
}

BasicCollision BaseAI::WillCollideWall(sf::Vector2f rayVector, std::vector<Wall> * walls)
{
	BasicCollision coll;
	coll.willCollide = false;
	coll.position = sf::Vector2f(0, 0);
	coll.normal = sf::Vector2f(0, 0);
	sf::Vector2f vec = rayVector + m_position;
	for (int i = 0; i < walls->size(); i++)
	{
		if (walls->at(i).getSprite().getGlobalBounds().contains(vec))
		{
			coll.willCollide = true;
			coll.position = vec;
			float angle = walls->at(i).getOrientation();
			//if (walls->at(i).getPosition().x > m_position.x)
			//{
			//	angle = 360 - angle;
			//}
			angle = angle * 180 / 3.14159265359;
			if (angle == 0)//Top
			{
				angle = 180 / 3.14159265359;
			}

			coll.normal.x = tanf(angle);
			coll.normal.y = sinf(angle);

			if (m_position.x < coll.position.x && coll.normal.x > coll.normal.y)//Right
			{
				angle = -angle;
				coll.normal.x = tanf(angle);
				coll.normal.y = sinf(angle);
			}
			if (m_position.y < coll.position.y && coll.normal.y > coll.normal.x)//Bottom
			{
				angle = angle+180;
				coll.normal.x = tanf(angle);
				coll.normal.y = sinf(angle);
			}
			//coll.normal = Normalize(coll.normal);
		}
	}
	return coll;
}

void BaseAI::GetCollisionNormal(sf::Vector2f otherPosition)
{

}