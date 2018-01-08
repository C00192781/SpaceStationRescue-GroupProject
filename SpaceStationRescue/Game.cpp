#include "Game.h"

Game::Game()
{
	srand(time(NULL));

	m_window = new sf::RenderWindow(sf::VideoMode{ 1920, 1080, 32 }, "Space Station Rescue 2!!!");
	m_exitGame = false;
	m_window->setFramerateLimit(60);

	timer = 0.0f; 

	playerTexture.loadFromFile("Assets\\Images\\Player.png");
	bulletTexture.loadFromFile("Assets\\Images\\Bullet.png");
	workerTexture.loadFromFile("worker.png");
	wallTexture.loadFromFile("Assets\\Images\\BasicWall.png");
	
	player = Player(sf::Vector2f(300, 300), sf::Vector2f(0, 0), sf::Vector2f(8, 8), 0, &playerTexture);

	bullets = new std::vector<Bullet>();

	workers = new std::vector<Worker>();
	workers->push_back(Worker(sf::Vector2f(200, 200), sf::Vector2f(0, 0), sf::Vector2f(3, 3), &workerTexture));
	workers->push_back(Worker(sf::Vector2f(500, 700), sf::Vector2f(0, 0), sf::Vector2f(3, 3), &workerTexture));
	workers->push_back(Worker(sf::Vector2f(1000, 600), sf::Vector2f(0, 0), sf::Vector2f(3, 3), &workerTexture));

	walls = new std::vector<Wall>();
	//walls->push_back(Wall(sf::Vector2f(500, 200), sf::Vector2f(100, 100), 0, &wallTexture));
	// sf::Vector2f pos, sf::Vector2f size, float orientation, sf::Texture *wallTexture

	levels.levelHandler(walls, &wallTexture);
	walls->push_back(Wall(sf::Vector2f(500, 200), sf::Vector2f(100, 100), 0, &wallTexture));
	// sf::Vector2f pos, sf::Vector2f size, float orientation, sf::Texture *wallTexture

	view = m_window->getDefaultView();
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
	player.movementHandler(sf::Vector2f(1920, 1080));
	player.Update();

	// ADDING BULLETS 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{ 
		if (timer == 0)
		{
			bullets->push_back(Bullet(sf::Vector2f(player.getPosition().x, player.getPosition().y), player.getVelocity(), sf::Vector2f(15, 15), player.getOrientation(), &bulletTexture));
			timer++;
		}
		timer++;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		timer = 0.0f;
	}
	if (timer >= 10)
	{
		timer = 0;
	}


	for (int i = 0; i < bullets->size(); i++)
	{
		bullets->at(i).BulletHandler(bullets, sf::Vector2f(1920, 1080));
	}

	for (int i = 0; i < bullets->size(); i++)
	{
		bullets->at(i).Update();
	}

	for (int i = 0; i < workers->size(); i++)
	{
		workers->at(i).Update(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	}

	for (int i = 0; i < walls->size(); i++)
	{
		walls->at(i).Update();
	}

	view.setCenter(sf::Vector2f(player.getPosition().x, player.getPosition().y));
	//view.setViewport(sf::FloatRect(0.25f, 0.25, 0.1f, 0.1f));

	if (m_exitGame == true)
	{
		m_window->close();
	}
}

void Game::render()
{
	m_window->clear(sf::Color::Black);
	player.Draw(m_window);
	for (int i = 0; i < bullets->size(); i++)
	{
		bullets->at(i).Draw(m_window);
	}

	for (int i = 0; i < workers->size(); i++)
	{
		workers->at(i).Draw(m_window);
	}

	for (int i = 0; i < walls->size(); i++)
	{
		walls->at(i).Draw(m_window);
	}

	m_window->setView(view);

	m_window->display();
}
