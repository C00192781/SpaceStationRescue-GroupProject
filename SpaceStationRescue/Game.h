#pragma once

#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Bullet.h"
#include "Worker.h"
#include "Wall.h"
#include "Level.h"
#include "Predator.h"

#include "Graph.h"

#include <iostream>

#include <fstream>
#include <string>
#include <utility>
#include "SFML\Main.hpp"
#include "SFML\Window.hpp"


class Game
{
public:
	Game();
	~Game();
	void run();

private:
	unsigned int screenWidth = 1920;
	unsigned int screenHeight = 1080;

	int timer;

	void processEvents();
	void update();
	void render();



	// AStar + Graph
	
	typedef GraphArc<string, int> Arc;
	typedef GraphNode<pair<string, int>, int> Node;
	void GraphSetUp();
	sf::Vector2f GetTarget();
	Graph<pair<string, int>, int>* graph;



	std::vector<sf::Vector2f> waypoints; 






	sf::RenderWindow *m_window;

	bool m_exitGame;

	sf::Texture playerTexture; 

	sf::Texture bulletTexture;
	std::vector<Bullet> * bullets;

	sf::Texture workerTexture;
	std::vector<Worker> * workers;

	sf::Texture predatorTexture;
	std::vector<Predator> * predators;

	sf::Texture wallTexture;
	std::vector<Wall> * walls;

	Player player;

	Level levels; 

	sf::View view;
	sf::Vector2f tempTarget;





};