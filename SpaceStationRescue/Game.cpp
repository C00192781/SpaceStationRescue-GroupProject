#include "Game.h"

Game::Game()
{
	srand(time(NULL));

	m_window = new sf::RenderWindow(sf::VideoMode{ screenWidth, screenHeight, 32 }, "Space Station Rescue 2!!!");
	m_exitGame = false;
	m_window->setFramerateLimit(60);

	timer = 0.0f; 

	playerTexture.loadFromFile("Assets\\Images\\Player.png");
	bulletTexture.loadFromFile("Assets\\Images\\Bullet.png");
	workerTexture.loadFromFile("worker.png");
	wallTexture.loadFromFile("Assets\\Images\\BasicWall.png");
	predatorTexture.loadFromFile("Assets\\Images\\BasicWall.png");
	
	player = Player(sf::Vector2f(300, 300), sf::Vector2f(0, 0), sf::Vector2f(8, 8), 0, &playerTexture);

	bullets = new std::vector<Bullet>();

	workers = new std::vector<Worker>();
	workers->push_back(Worker(sf::Vector2f(200, 200), sf::Vector2f(0, 0), sf::Vector2f(3, 3), &workerTexture));
	workers->push_back(Worker(sf::Vector2f(500, 700), sf::Vector2f(0, 0), sf::Vector2f(3, 3), &workerTexture));
	workers->push_back(Worker(sf::Vector2f(1000, 1200), sf::Vector2f(0, 0), sf::Vector2f(3, 3), &workerTexture));

	predators = new std::vector<Predator>();
	predators->push_back(Predator(sf::Vector2f(500, 600), sf::Vector2f(0, 0), sf::Vector2f(3, 3), &predatorTexture));

	walls = new std::vector<Wall>();

	levels.levelHandler(walls, &wallTexture);

	view = m_window->getDefaultView();
	tempTarget = sf::Vector2f(0, 0);
	graph = new Graph<pair<string, int>, int>(30);
	GraphSetUp();
	//RunAStar(*graph);
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
		workers->at(i).Update(sf::Vector2f(0, 0), sf::Vector2f(0, 0), walls);
	}

	for (int i = 0; i < walls->size(); i++)
	{
		walls->at(i).Update();
	}

	for (int i = 0; i < predators->size(); i++)
	{
		predators->at(i).Update(graph, &waypoints, walls);
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

	for (int i = 0; i < predators->size(); i++)
	{
		predators->at(i).Draw(m_window);
	}

	for (int i = 0; i < walls->size(); i++)
	{
		walls->at(i).Draw(m_window);
	}

	m_window->setView(view);

	m_window->display();
}

void Game::RunAStar(Graph<pair<string, int>, int> graph)
{
	// Now traverse the graph.
	std::vector<Node *> thepath;
	graph.aStar(graph.nodeArray()[0], graph.nodeArray()[2], thepath);//13 1
	for (int i = thepath.size() - 1; i > -1; i--)
	{
		std::cout << "Location : " << thepath.at(i)->data().first << " Cost : " << thepath.at(i)->data().second << " h(n) : " << thepath.at(i)->getEstimatedDistToDest() << std::endl;
		if (thepath.at(i) == graph.nodeArray()[1])
		{
			std::cout << std::endl;
		}
	}

	string temp = thepath.at(1)->data().first;
	int tempInt = std::stoi(temp);
	tempTarget = waypoints.at(tempInt);
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
