 #include "Level.h"

Level::Level()
{
	maxCol = 57; // x
	maxRow = 32; // y
}

Level::~Level()
{

}

void Level::levelHandler(std::vector<Wall> * walls, sf::Texture *wallTexture)
{
	pMap = (int*)map;

	CreateMap(walls, wallTexture);
	//Top(walls, wallTexture);
	//Left(walls, wallTexture);
	//Right(walls, wallTexture);
	//Bottom(walls, wallTexture);

	//Walls1(walls, wallTexture);
	//Walls2(walls, wallTexture);
	//Walls3(walls, wallTexture);
	//Walls4(walls, wallTexture);
}


void Level::CreateMap(std::vector<Wall> * walls, sf::Texture *wallTexture)
{
	maxSquares = maxRow * maxCol;

	for (int row = 0; row < maxRow; row++)
	{
		for (int column = 0; column < maxCol; column++)
		{
			if (pMap[maxCol * (row)+column] == 3)
			{
				std::cout << column << std::endl;
				walls->push_back(Wall(sf::Vector2f(column * 100, (row) * 100), sf::Vector2f(100, 100), 0.0f, wallTexture));
			}
		}
	}
}


const int Level::map[57][57]   // 39  going across, 30 going down
{
	// 30 rows, 30 columns
	{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3, },
	{ 3,5,5,5,5,5,5,5,5,5,5,5,3,5,5,5,5,5,5,3,5,5,5,5,3,3,3,3,3,3,3,3,3,3,5,5,5,5,3,3,5,5,5,5,5,5,5,5,5,5,5,3,3,5,5,5,5, },
	{ 3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,5,5,5,5,3,3,3,3,3,3,3,3,3,3,5,5,5,5,3,3,5,5,5,5,5,5,5,5,5,5,5,3,3,5,5,5,5, },
	{ 3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,5,5,5,5,3,3,3,3,3,3,3,3,3,3,5,5,5,5,3,3,5,5,5,5,5,5,5,5,5,5,5,3,3,5,5,5,5, },
	{ 3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,5,5,5,5,3,3,3,3,3,3,3,3,3,3,5,5,5,5,3,3,5,5,5,5,5,5,5,5,5,5,5,3,3,5,5,5,5, },
	{ 3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,3,5,5,5,5, },
	{ 3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,3,5,5,5,5, },
	{ 3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,3,3,3,5,5,5,5,5,5,5,5,5,3,3,5,5,5,5, },
	{ 3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,3,3,3,5,5,5,5,5,5,5,5,5,3,3,5,5,5,5, },
	{ 3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,3,3,3,5,5,5,5,5,5,5,5,5,3,3,5,5,5,5, },
	{ 3,3,3,3,3,3,3,3,5,5,5,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,5,5,5,5,5,5,5,5,5,3,3,3,3,5,5,5,5,5,5,5,5,5,3,3,5,5,5,5, },
	{ 3,3,3,3,3,3,3,3,5,5,5,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,3,3,3,3,3,3,3,5,5,5,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,3,3,3,3,3,3,3,5,5,5,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,5,5,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,5,5,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,5,5,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,5,5,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,5,5,5,5,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,5,5,5,5,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,5,5,5,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,5,5,5,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,5,5,5,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,3,5,5,5,5,5,5,5,5,5,5,5,5, },
	{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,5,5,5,5,5,5,5,5,5, }
};



// 1st, 2nd and 3rd horizontal walls from top left 
void Level::Walls1(std::vector<Wall> * walls, sf::Texture *wallTexture)
{
	int x1 = 0;
	int y1 = 1000;

	for (int y = 0; y < 4; y++)
	{
		for (int i = 0; i < 8; i++)
		{
			walls->push_back(Wall(sf::Vector2f(x1, y1), sf::Vector2f(100, 100), 0.0f, wallTexture));
			x1 += 100;
		}
		x1 = 0;
		y1 += 100;
	}

	int x2 = 1200;
	int y2 = 1000;

	for (int y = 0; y < 4; y++)
	{
		for (int i = 0; i < 14; i++)
		{
			walls->push_back(Wall(sf::Vector2f(x2, y2), sf::Vector2f(100, 100), 0.0f, wallTexture));
			x2 += 100;
		}
		x2 = 1200;
		y2 += 100;
	}



	int x3 = 2900;
	int y3 = 1000;

	for (int y = 0; y < 4; y++)
	{
		for (int i = 0; i < 16; i++)
		{
			walls->push_back(Wall(sf::Vector2f(x3, y3), sf::Vector2f(100, 100), 0.0f, wallTexture));
			x3 += 100;
		}
		x3 = 2900;
		y3 += 100;
	}
}

// 1st and 2nd vertical walls from top left
void Level::Walls2(std::vector<Wall> * walls, sf::Texture *wallTexture)
{
	int y1 = 0;
	for (int i = 0; i < 5; i++)
	{
		walls->push_back(Wall(sf::Vector2f(1900, y1), sf::Vector2f(100, 100), 0.0f, wallTexture));
		y1 += 100;
	}

	int y2 = 700;
	for (int i = 0; i < 3; i++)
	{
		walls->push_back(Wall(sf::Vector2f(1900, y2), sf::Vector2f(100, 100), 0.0f, wallTexture));
		y2 += 100;
	}
}


// Large wall 
// centre, top of map
void Level::Walls3(std::vector<Wall> * walls, sf::Texture *wallTexture)
{
	int x = 2400; 
	int y = 0;
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			walls->push_back(Wall(sf::Vector2f(x, y), sf::Vector2f(100, 100), 0.0f, wallTexture));
			x += 100;
		}
		x = 2400;
		y += 100;
	}
}

// 2 Vertical walls 
// Near Top Right of map
void Level::Walls4(std::vector<Wall> * walls, sf::Texture *wallTexture)
{
	int x = 3800;
	int y = 0;
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 2; i++)
		{
			walls->push_back(Wall(sf::Vector2f(x, y), sf::Vector2f(100, 100), 0.0f, wallTexture));
			x += 100;
		}
		x = 3800;
		y += 100;
	}

	int x2 = 3800;
	int y2 = 700;
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			walls->push_back(Wall(sf::Vector2f(x2, y2), sf::Vector2f(100, 100), 0.0f, wallTexture));
			x2 += 100;
		}
		x2 = 3800;
		y2 += 100;
	}
}


void Level::Walls5(std::vector<Wall> * walls, sf::Texture *wallTexture)
{

}


void Level::Walls6(std::vector<Wall> * walls, sf::Texture *wallTexture)
{

}

void Level::Walls7(std::vector<Wall> * walls, sf::Texture *wallTexture)
{

}


void Level::Walls8(std::vector<Wall> * walls, sf::Texture *wallTexture)
{

}


void Level::Walls9(std::vector<Wall> * walls, sf::Texture *wallTexture)
{

}


void Level::Walls10(std::vector<Wall> * walls, sf::Texture *wallTexture)
{

}




void Level::Top(std::vector<Wall> * walls, sf::Texture *wallTexture)
{
	int x = 0;

	// TOP
	for (int i = 0; i < 57; i++)
	{
		walls->push_back(Wall(sf::Vector2f(x, 0), sf::Vector2f(100, 100), 0.0f, wallTexture));
		x += 100;
	}
}

void Level::Left(std::vector<Wall> * walls, sf::Texture *wallTexture)
{
	int y = 0;
	// LEFT
	for (int i = 0; i < 32; i++)
	{
		walls->push_back(Wall(sf::Vector2f(0, y), sf::Vector2f(100, 100), 0.0f, wallTexture));
		y += 100;
	}
}



void Level::Right(std::vector<Wall> * walls, sf::Texture *wallTexture)
{
	int y = 0;
	// RIGHT
	for (int i = 0; i < 33; i++)
	{
		walls->push_back(Wall(sf::Vector2f(5700, y), sf::Vector2f(100, 100), 0.0f, wallTexture));
		y += 100;
	}
}



void Level::Bottom(std::vector<Wall> * walls, sf::Texture *wallTexture)
{
	int x = 0;

	// TOP
	for (int i = 0; i < 57; i++)
	{
		walls->push_back(Wall(sf::Vector2f(x, 3200), sf::Vector2f(100, 100), 0.0f, wallTexture));
		x += 100;
	}
}