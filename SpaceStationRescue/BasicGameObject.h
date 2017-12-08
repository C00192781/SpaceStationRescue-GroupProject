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
	sf::Texture m_texture;
	sf::Sprite m_sprite;

public:
	BasicGameObject();
	BasicGameObject(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f maxSpeed, float orientation, sf::Texture tex);
	~BasicGameObject();
	void Update();
	void Draw(sf::RenderWindow *window);
};