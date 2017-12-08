#include "Game.h"


Game::Game()
{
	m_window = new sf::RenderWindow(sf::VideoMode{ 1920, 1080, 32 }, "Space Station Rescue 2!!!");
	m_exitGame = false;
	m_window->setFramerateLimit(60);
}

Game::~Game()
{
}

void Game::run()
{
	while (m_window->isOpen())
	{
		processEvents(); // as many as possible
		update();
		render();
	}
}

void Game::processEvents()
{

}

void Game::update()
{
	if (m_exitGame == true)
	{
		m_window->close();
	}
}

void Game::render()
{
	m_window->clear(sf::Color::White);

	m_window->display();
}
