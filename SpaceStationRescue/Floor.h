#pragma once
#include "BasicGameObject.h"

class Floor : public BasicGameObject
{
public:
	Floor();
	Floor(sf::Vector2f pos, sf::Vector2f size, float orientation, sf::Texture *floorTexture);
	~Floor();

private:

};

