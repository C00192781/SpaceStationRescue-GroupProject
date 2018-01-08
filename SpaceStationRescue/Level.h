#pragma once

#pragma once
#include "BasicGameObject.h"
#include "Wall.h"

class Level : public BasicGameObject
{
public:
	Level();
	//Level(std::vector<Wall> * walls);
	~Level();

	//void PlayerCollision(sf::FloatRect playerRect);

	void levelHandler(std::vector<Wall> *walls, sf::Texture *wallTexture);


private:

	void Top(std::vector<Wall> * walls, sf::Texture *wallTexture);
	void Left(std::vector<Wall> * walls, sf::Texture *wallTexture);
	void Right(std::vector<Wall> * walls, sf::Texture *wallTexture);
	void Bottom(std::vector<Wall> * walls, sf::Texture *wallTexture);

	void Walls1(std::vector<Wall> * walls, sf::Texture *wallTexture);
	void Walls2(std::vector<Wall> * walls, sf::Texture *wallTexture);
	void Walls3(std::vector<Wall> * walls, sf::Texture *wallTexture);
	void Walls4(std::vector<Wall> * walls, sf::Texture *wallTexture);
	void Walls5(std::vector<Wall> * walls, sf::Texture *wallTexture);
	void Walls6(std::vector<Wall> * walls, sf::Texture *wallTexture);
	void Walls7(std::vector<Wall> * walls, sf::Texture *wallTexture);
	void Walls8(std::vector<Wall> * walls, sf::Texture *wallTexture);
	void Walls9(std::vector<Wall> * walls, sf::Texture *wallTexture);
	void Walls10(std::vector<Wall> * walls, sf::Texture *wallTexture);

};

