#pragma once
#include "BasicAI.h"
#include "Graph.h"
#include "Pathfinding.h"
#include "PathfindingStates.h"
#include "Bullet.h"



class Interceptor : public BaseAI
{
public:
	Interceptor();
	Interceptor(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f maxSpeed, sf::Texture* texture);
	~Interceptor();

	//void PlayerCollision(sf::FloatRect playerRect);

	void Update(Graph<pair<string, int>, int>* graph, std::vector<sf::Vector2f>* waypoints, std::vector<Wall>* walls, sf::Vector2f playerPos, std::vector<Bullet>* bullets);
	void Draw(sf::RenderWindow * window);

	int startPoint;
	int endPoint;

	float timeAlive; 
	float timeDead;
	float getTimeAlive();
	void setTimeAlive(float time);

	float getTimeDead();
	void setTimeDead(float time);

private:
	int timer;
	PathfindingStates states;
	Pathfinding pathfinding;

};