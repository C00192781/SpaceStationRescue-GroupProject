#pragma once
#include "BasicAI.h"
#include "Graph.h"
#include "Pathfinding.h"
#include "PathfindingStates.h"

class Predator : public BaseAI
{
public:
	Predator();
	Predator(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f maxSpeed, sf::Texture* workerTexture);
	~Predator();

	//void PlayerCollision(sf::FloatRect playerRect);

	void Update(Graph<pair<string, int>, int>* graph, std::vector<sf::Vector2f>* waypoints, std::vector<Wall>* walls, sf::Vector2f playerPos);


	int startPoint;
	int endPoint;

private:
	int timer;
	PathfindingStates states;
	

};
