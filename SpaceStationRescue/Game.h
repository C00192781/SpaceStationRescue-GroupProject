#pragma once

#include "SFML/Graphics.hpp"

#include <iostream>

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	int screenWidth = 1980;
    int screenHeight = 1080;

	void processEvents();
	void update();
	void render();

	sf::RenderWindow *m_window;

	bool m_exitGame;
};