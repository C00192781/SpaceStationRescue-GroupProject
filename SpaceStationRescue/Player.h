#pragma once

#ifndef PLAYER
#define PLAYER


#include "BasicGameObject.h"

#include <iostream>

using namespace std;

class Player : public BasicGameObject
{
public:
	Player();
	Player(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f maxSpeed, float orientation, sf::Texture* tex);
	~Player();

	void movementHandler(sf::Vector2f screenBounds);
	float speed;
	
private:
	void Bounds(sf::Vector2f screenBounds);
	sf::Vector2f velocityHandler(float orientation);
	float conversion;


};

#endif 