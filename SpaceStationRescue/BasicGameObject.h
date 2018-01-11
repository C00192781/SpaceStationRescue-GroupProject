#pragma once

// Position, velocity. texture, sprite, orientation/rotation, max speed, draw, update

#include "SFML\Graphics.hpp"


class BasicGameObject
{
protected:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_maxSpeed;

	float m_orientation;
	int m_health;
	bool m_alive;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_size;

public:
	BasicGameObject();
	BasicGameObject(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f maxSpeed, float orientation, sf::Texture tex);
	~BasicGameObject();
	virtual void Update();
	virtual void Draw(sf::RenderWindow *window);
	bool CollisionDetection(sf::Sprite sprite);
	void SetupSprite(sf::Texture* texture);

	sf::Vector2f getPosition();
	void SetPosition(sf::Vector2f newPosition);
	sf::Vector2f getVelocity();
	void SetVelocity(sf::Vector2f newVelocity);
	sf::Vector2f getMaxSpeed();
	void SetMaxSpeed(sf::Vector2f newMaxSpeed);

	int getHealth();
	void setHealth(int health);

	bool getAlive();
	void setAlive(int alive);

	float getOrientation();

	sf::Sprite &getSprite();
};