#include "Game.h"


Game::Game()
{
	srand(time(NULL));

	m_window = new sf::RenderWindow(sf::VideoMode{ 1920, 1080, 32 }, "Space Station Rescue 2!!!");
	m_exitGame = false;
	m_window->setFramerateLimit(60);

	workerTexture.loadFromFile("worker.png");

	workers = new std::vector<Worker>();
	workers->push_back(Worker(sf::Vector2f(200, 200), sf::Vector2f(0, 0), sf::Vector2f(3, 3), &workerTexture));
	workers->push_back(Worker(sf::Vector2f(500, 700), sf::Vector2f(0, 0), sf::Vector2f(3, 3), &workerTexture));
	workers->push_back(Worker(sf::Vector2f(1000, 600), sf::Vector2f(0, 0), sf::Vector2f(3, 3), &workerTexture));
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
	for (int i = 0; i < workers->size(); i++)
	{
		workers->at(i).Update(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	}
	if (m_exitGame == true)
	{
		m_window->close();
	}
}

void Game::render()
{
	m_window->clear(sf::Color::White);
	for (int i = 0; i < workers->size(); i++)
	{
		workers->at(i).Draw(m_window);
	}
	m_window->display();
}
