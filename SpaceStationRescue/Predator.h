#pragma once
#include "BasicAI.h"
#include "Graph.h"
#include "Pathfinding.h"
#include "PathfindingStates.h"
#include "Bullet.h"

class Predator : public BaseAI
{
public:
	Predator();
	Predator(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f maxSpeed, sf::Texture* workerTexture, sf::Texture& bulletTex);
	~Predator();

	//void PlayerCollision(sf::FloatRect playerRect);

	void Update(Graph<pair<string, int>, int>* graph, std::vector<sf::Vector2f>* waypoints, std::vector<Wall>* walls, sf::Vector2f playerPos, std::vector<Bullet>* bullets);
	void RadarDraw(sf::RenderWindow * window);

	void Draw(sf::RenderWindow *window);


	int startPoint;
	int endPoint;

	
	void bulletHandler();
	std::vector<Bullet> * predatorBullets;
	int bulletTimer;
private:
	int timer;
	PathfindingStates states;

	sf::Texture bulletTexture;


};
