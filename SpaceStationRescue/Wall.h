#pragma once
#include "BasicGameObject.h"

class Wall : public BasicGameObject
{
public:
	Wall();
	Wall(sf::Vector2f pos, sf::Vector2f size, float orientation, sf::Texture *wallTexture);
	~Wall();

	//void PlayerCollision(sf::FloatRect playerRect);

private:

};
