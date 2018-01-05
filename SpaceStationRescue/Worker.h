#pragma once
#include "BasicAI.h"

class Worker : public BaseAI
{
public:
	Worker();
	Worker(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f maxSpeed, sf::Texture* workerTexture);
	~Worker();

	//void PlayerCollision(sf::FloatRect playerRect);

private:

};

