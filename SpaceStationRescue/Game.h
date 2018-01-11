#pragma once

#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Bullet.h"
#include "Worker.h"
#include "Wall.h"
#include "Level.h"
#include "Predator.h"
#include "Floor.h"

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

	sf::Texture workerTexture;
	std::vector<Worker> * workers;

	sf::Texture predatorTexture;
	std::vector<Predator> * predators;

	sf::Texture wallTexture;
	std::vector<Wall> * walls;

	sf::Texture bulletTexture;

	Player player;
	sf::Texture playerTexture;

	sf::Texture floorTexture;
	std::vector<Floor> * floor;

	Level levels; 

	sf::View view;
	sf::View radar;
	sf::Vector2f tempTarget;

	// Declare and load a font
	sf::Font collectionFont;
	sf::Text collectionText;

};