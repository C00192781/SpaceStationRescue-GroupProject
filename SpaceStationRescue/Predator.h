#pragma once
#include "BasicAI.h"

class Predator : public BaseAI
{
public:
	Predator();
	Predator(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f maxSpeed, sf::Texture* workerTexture);
	~Predator();

	//void PlayerCollision(sf::FloatRect playerRect);

private:

};
