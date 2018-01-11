#include "Game.h"

Game::Game()
{
	srand(time(NULL));

	m_window = new sf::RenderWindow(sf::VideoMode{ screenWidth, screenHeight, 32 }, "Space Station Rescue 2!!!");
	m_exitGame = false;
	m_window->setFramerateLimit(60);


	playerTexture.loadFromFile("Assets\\Images\\Player.png");
	bulletTexture.loadFromFile("Assets\\Images\\Bullet.png");
	workerTexture.loadFromFile("Assets\\Images\\Worker.png");
	wallTexture.loadFromFile("Assets\\Images\\BasicWall.png");
	predatorTexture.loadFromFile("Assets\\Images\\BasicWall.png");
	sweeperTexture.loadFromFile("Assets\\Images\\Sweeper.png");
	floorTexture.loadFromFile("Assets\\Images\\Floor.png");
	
	player = Player(sf::Vector2f(300, 300), sf::Vector2f(0, 0), sf::Vector2f(8, 8), 0, &playerTexture, bulletTexture);

	workers = new std::vector<Worker>();
	workers->push_back(Worker(sf::Vector2f(700, 300), sf::Vector2f(0, 0), sf::Vector2f(3, 3), &workerTexture));
	workers->push_back(Worker(sf::Vector2f(900, 700), sf::Vector2f(0, 0), sf::Vector2f(3, 3), &workerTexture));
	workers->push_back(Worker(sf::Vector2f(1000, 1200), sf::Vector2f(0, 0), sf::Vector2f(3, 3), &workerTexture));

	predators = new std::vector<Predator>();
	predators->push_back(Predator(sf::Vector2f(2500, 900), sf::Vector2f(0, 0), sf::Vector2f(8, 8), &predatorTexture));

	sweepers = new std::vector<Sweeper>();
	sweepers->push_back(Sweeper(sf::Vector2f(2000, 900), sf::Vector2f(0, 0), sf::Vector2f(5, 5), &sweeperTexture));

	walls = new std::vector<Wall>();

	floor = new std::vector<Floor>();

	levels.levelHandler(walls, &wallTexture, floor, &floorTexture);

	view = m_window->getDefaultView();
	radar = sf::View(sf::Vector2f(2880, 1620), sf::Vector2f(5760, 3240));
	radar.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	tempTarget = sf::Vector2f(0, 0);
	graph = new Graph<pair<string, int>, int>(30);
	GraphSetUp();
	//RunAStar(*graph);
//	text.setColor(sf::Color::Red);

	collectionFont.loadFromFile("Star_Jedi_Rounded.ttf");
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
	//cout << text.getPosition().x << endl;
	player.Update(workers, predators);

	for (int i = 0; i < workers->size(); i++)
	{
		workers->at(i).Update(sf::Vector2f(0, 0), sf::Vector2f(0, 0), walls);
	}

	for (int i = 0; i < walls->size(); i++)
	{
		walls->at(i).Update();
	}


	for (int i = 0; i < predators->size(); i++)
	{
		predators->at(i).Update(graph, &waypoints, walls, player.getPosition(), player.bullets);
	}

	for (int i = 0; i < sweepers->size(); i++)
	{
		sweepers->at(i).Update(graph, &waypoints, walls, player.getPosition(),workers);
	}

	view.setCenter(sf::Vector2f(player.getPosition().x, player.getPosition().y));

	// Create a text
	collectionText.setString("Workers Collected: " + std::to_string(player.collected));
	collectionText.setFont(collectionFont);
	collectionText.setCharacterSize(30);
	collectionText.setStyle(sf::Text::Bold);
	collectionText.setFillColor(sf::Color::White);
	collectionText.setPosition(view.getCenter().x - screenWidth/2.1, view.getCenter().y - screenHeight / 2.1);

	if (m_exitGame == true)
	{
		m_window->close();
	}
}

void Game::render()
{
	m_window->clear(sf::Color::Black);

	//Draw Full Level
	m_window->setView(view);


	for (int i = 0; i < floor->size(); i++)
	{
		floor->at(i).Draw(m_window);
	}

	player.Draw(m_window);

	for (int i = 0; i < workers->size(); i++)
	{
		workers->at(i).Draw(m_window);
	}

	for (int i = 0; i < predators->size(); i++)
	{
		predators->at(i).Draw(m_window);
	}

	for (int i = 0; i < sweepers->size(); i++)
	{
		sweepers->at(i).Draw(m_window);
	}

	for (int i = 0; i < walls->size(); i++)
	{
		walls->at(i).Draw(m_window);
	}

	m_window->draw(collectionText);

	//Draw Radar
	m_window->setView(radar);

	for (int i = 0; i < floor->size(); i++)
	{
		floor->at(i).Draw(m_window);
	}

	player.Draw(m_window);

	for (int i = 0; i < workers->size(); i++)
	{
		workers->at(i).Draw(m_window);
	}

	for (int i = 0; i < predators->size(); i++)
	{
		predators->at(i).Draw(m_window);
	}

	for (int i = 0; i < sweepers->size(); i++)
	{
		sweepers->at(i).Draw(m_window);
	}

	for (int i = 0; i < walls->size(); i++)
	{
		walls->at(i).Draw(m_window);
	}

	m_window->display();
	//m_window->setView(m_window->getDefaultView());

	
}



void Game::GraphSetUp()
{
	std::string temp;
	int i = 0;
	ifstream myfile;
	int posX = 0;
	int posY = 0;
	myfile.open("nodes.txt");

	while (myfile >> temp >> posX >> posY)
	{
		graph->addNode(pair<string, int>(temp, std::numeric_limits<int>::max() - 10000), i);
		waypoints.push_back(sf::Vector2f(posX, posY));
		i++;
	}
	myfile.close();

	myfile.open("arcs.txt");
	int from, to, weight;
	while(myfile >> from >> to >> weight)
	{
		graph->addArc(from, to, weight);
		//arcVector.push_back(ArcGraphics(graphicsVector.at(from).getScreenPosition(), graphicsVector.at(to).getScreenPosition(),weight));
	}
	myfile.close();
}
