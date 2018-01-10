#pragma once

#ifndef PLAYER
#define PLAYER


#include "BasicGameObject.h"
#include "Bullet.h"

#include <iostream>

using namespace std;

class Player : public BasicGameObject
{
public:
	Player();
	Player(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f maxSpeed, float orientation, sf::Texture* tex, sf::Texture& bulletTex);
	~Player();

	void movementHandler();
	void bulletHandler();
	void Draw(sf::RenderWindow *window);
	float speed;

	std::vector<Bullet> * bullets;
	int bulletTimer;
	
private:
	sf::Vector2f velocityHandler(float orientation);
	float conversion;
	sf::Texture bulletTexture;

};

#endif 