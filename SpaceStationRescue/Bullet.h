#pragma once
#include "BasicGameObject.h"

class Bullet : public BasicGameObject
{
public:
	Bullet();
	Bullet(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f maxSpeed, float orientation, sf::Texture* bulletTexture);
	~Bullet();

	//void PlayerCollision(sf::FloatRect playerRect);

	void BulletHandler(std::vector<Bullet> *bullets, sf::Vector2f screenBounds);
	std::string shooter;

private:
	float conversion;

	sf::Vector2f velocityHandler(float orientation); 
	void Bounds(std::vector<Bullet> *bullets, sf::Vector2f screenBounds);

};
