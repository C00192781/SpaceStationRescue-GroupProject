#pragma once
#include <random>
#include "BasicAI.h"
#include "Graph.h"
#include "Worker.h"
#include "Bullet.h"
#include "Pathfinding.h"
#include "PathfindingStates.h"

class Sweeper : public BaseAI
{
public:
	Sweeper();
	Sweeper(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f maxSpeed, sf::Texture* workerTexture);
	~Sweeper();

	//void PlayerCollision(sf::FloatRect playerRect);

	void Update(Graph<pair<string, int>, int>* graph, std::vector<sf::Vector2f>* waypoints, std::vector<Wall>* walls, sf::Vector2f playerPos, std::vector<Worker>* workers, std::vector<Bullet>* bullets);
	int GetRandomWaypoint(int currentWaypoint, int numWaypoints);
	void SetupLOS();
	void Draw(sf::RenderWindow* window);
	void RadarDraw(sf::RenderWindow* window);
	bool LookForWorker(std::vector<Wall>* walls, sf::Vector2f playerPos, std::vector<Worker>* workers);

	int startPoint;
	int endPoint;
	int workerCount;
	int targetWorkerIndex;
	bool haveWorkerTargeted;
	bool searching;
	PathfindingStates states;

private:
	int timer;
	

	Pathfinding pathfinding;
	
	sf::CircleShape lineOfSight;
	float lineOfSightRadius;
	float lineOfSightAngle;
	sf::VertexArray line;
	
	
	bool fleeing;
	
};