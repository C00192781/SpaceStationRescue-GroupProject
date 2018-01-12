#pragma once
#include "BasicGameObject.h"

class PowerUp : public BasicGameObject
{
public:
	PowerUp();
	~PowerUp();
	PowerUp(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f maxSpeed, sf::Texture* powerUpTexture);
private:

};

