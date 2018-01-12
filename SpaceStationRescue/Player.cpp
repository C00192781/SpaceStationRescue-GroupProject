#include "Player.h"

Player::Player()
{
	//Player(sf::Vector2f(100.0f, 100.0f), sf::Vector2f(100.0f, 100.0f), sf::Vector2f(100.0f, 100.0f), 0, m_texture.loadFromFile("")); 
}

Player::Player(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f maxSpeed, float orientation, sf::Texture* playerTexture, sf::Texture& bulletTex)
{
	speed = 0.0f;
	conversion = 180 / 3.14159265359;
	m_position = pos;
	m_velocity = vel;
	m_maxSpeed = maxSpeed;
	m_orientation = orientation;
	bulletTexture = bulletTex;
	SetupSprite(playerTexture);
	m_sprite.setOrigin(29, 30.5);

	m_alive = true;
	m_health = 100;
	bullets = new std::vector<Bullet>();
	collected = 0;

	radarImage = sf::CircleShape(75);
	radarImage.setFillColor(sf::Color::White);
	radarImage.setOrigin(radarImage.getLocalBounds().width / 2, radarImage.getLocalBounds().height / 2);
}

Player::~Player()
{
}

void Player::movementHandler()
{
	m_position = m_sprite.getPosition();
	m_velocity = velocityHandler(m_orientation);
	m_velocity = m_velocity * speed;
	m_sprite.move(m_velocity);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_orientation -= 0.1f;
		m_sprite.setRotation(m_orientation * conversion);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_orientation += 0.1f;
		m_sprite.setRotation(m_orientation * conversion);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (speed < 8.0f) /// < maxSpeed   
		{
			speed += 0.5f;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (speed > 0)
		{
			speed -= 0.5f;
		}
	}
}

sf::Vector2f Player::velocityHandler(float orientation)
{
	sf::Vector2f temp;
	temp.x = sin(orientation);
	temp.y = -cos(orientation);
	return temp;
}


void Player::bulletHandler()
{
	// ADDING BULLETS 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (bulletTimer == 0)
		{
			bullets->push_back(Bullet(sf::Vector2f(getPosition().x, getPosition().y), getVelocity(), sf::Vector2f(15, 15), getOrientation(), &bulletTexture));
			bulletTimer++;
		}
		bulletTimer++;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		bulletTimer = 0.0f;
	}
	if (bulletTimer >= 10)
	{
		bulletTimer = 0;
	}

	for (int i = 0; i < bullets->size(); i++)
	{
		bullets->at(i).BulletHandler(bullets, sf::Vector2f(1920, 1080));
	}

	for (int i = 0; i < bullets->size(); i++)
	{
		bullets->at(i).Update();
	}
}

void Player::Draw(sf::RenderWindow *window)
{
	window->draw(m_sprite);
	for (int i = 0; i < bullets->size(); i++)
	{
		window->draw(bullets->at(i).getSprite());
	}
}

void Player::Update(std::vector<Worker>* workers, std::vector<Predator>* predators, std::vector<Sweeper>* sweepers, std::vector<Wall>* walls)
{



	movementHandler();
	bulletHandler();

	for (int i = 0; i < walls->size(); i++)
	{
		if (CollisionDetection(walls->at(i).getSprite()))
		{
				m_sprite.setPosition(m_sprite.getPosition() - (m_velocity*speed));
				speed = 0;
		}
		for (int b = 0; b < bullets->size(); b++)
		{
			if (bullets->at(b).CollisionDetection(walls->at(i).getSprite()) == true)
			{
				if (b != bullets->size() - 1)
				{
					std::swap(bullets->at(b), bullets->at(bullets->size() - 1));
				}
				bullets->pop_back();
			}
		}
	}

	for (int i = 0; i < workers->size(); i++)
	{
		if (CollisionDetection(workers->at(i).getSprite()) == true)
		{
			workers->at(i).SetMaxSpeed(sf::Vector2f(0.0f, 0.0f));
			workers->at(i).SetPosition(sf::Vector2f(-1000.0f, -1000.0f));
			collected++;
			m_alive = false;
		}
	}

	for (int i = 0; i < predators->size(); i++)
	{
		if (CollisionDetection(predators->at(i).getSprite()) == true && predators->at(i).getAlive() == true)
		{
			predators->at(i).setAlive(false);
			setHealth(m_health - 30);
		}
	}

	for (int i = 0; i < sweepers->size(); i++)
	{
		if (CollisionDetection(sweepers->at(i).getSprite()) == true && sweepers->at(i).getAlive() == true)
		{
			sweepers->at(i).setAlive(false);
			setHealth(m_health - 15);
		}
	}
	radarImage.setPosition(m_position);
}


void Player::RadarDraw(sf::RenderWindow* window)
{
	window->draw(radarImage);
}












/*
void Player::WorkerCollision(std::vector<Worker*> workers)
{
	for (int i = 0; i < workers.size(); i++)
	{
		if (m_sprite.getGlobalBounds().intersects(workers.at(i)->getSprite().getGlobalBounds()))
		{
			//Add 1 Rescued Point to player
			workers.erase(workers.begin() + (i - 1));
		}
	}
}
*/
