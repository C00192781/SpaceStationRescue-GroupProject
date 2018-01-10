#pragma once
#include <random>
#include "BasicAI.h"
#include "Graph.h"
#include "Pathfinding.h"
#include "PathfindingStates.h"

class Sweeper : public BaseAI
{
public:
	Sweeper();
	Sweeper(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f maxSpeed, sf::Texture* workerTexture);
	~Sweeper();

	//void PlayerCollision(sf::FloatRect playerRect);

	void Update(Graph<pair<string, int>, int>* graph, std::vector<sf::Vector2f>* waypoints, std::vector<Wall>* walls, sf::Vector2f playerPos);
	int GetRandomWaypoint(int currentWaypoint, int numWaypoints);

	int startPoint;
	int endPoint;

private:
	int timer;
	PathfindingStates states;
	int workerCount;
	Pathfinding pathfinding;


};