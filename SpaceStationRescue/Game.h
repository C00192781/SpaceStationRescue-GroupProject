#pragma once

#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Bullet.h"

#include <iostream>

#include "Worker.h"

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	int screenWidth = 1980;
    int screenHeight = 1080;

	int timer;

	void processEvents();
	void update();
	void render();

	sf::RenderWindow *m_window;

	bool m_exitGame;

	sf::Texture playerTexture; 

	sf::Texture bulletTexture;
	std::vector<Bullet> * bullets;

	sf::Texture workerTexture;
	std::vector<Worker> * workers;

	sf::View view;
};