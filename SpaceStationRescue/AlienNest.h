#pragma once
#include "BasicGameObject.h"
#include "Interceptor.h"
#include "Predator.h"

class AlienNest : public BasicGameObject
{
public:
	AlienNest();
	AlienNest(sf::Vector2f pos, sf::Vector2f size, float orientation, sf::Texture *alienNestTexture);
	~AlienNest();

	void Update(std::vector<Interceptor>* interceptors, sf::Vector2f position, sf::Texture * interceptorTexture, std::vector<Predator>* predators, sf::Texture * predatorTexture);
	//void Draw(); 


	int missileCounter;
	bool missileInitiated; 
	float range;
	sf::Vector2f startingPosition;
	int predatorCounter;
	int predatorSpawnTimer;
	int predatorMax;
	int predatorsCreated;
	std::vector<int> predatorIndex;
};