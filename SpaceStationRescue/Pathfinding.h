#pragma once

#include "Graph.h"


#include <iostream>
#include <string>

#include "SFML\Graphics.hpp"

class Pathfinding
{
public:
	Pathfinding();
	~Pathfinding();
	typedef GraphArc<string, int> Arc;
	typedef GraphNode<pair<string, int>, int> Node;
	sf::Vector2f RunAStar(Graph<pair<string, int>, int>* graph, std::vector<sf::Vector2f>* waypoints);

private:

};


//
//void Game::RunAStar(Graph<pair<string, int>, int> graph)
//{
//	// Now traverse the graph.
//	std::vector<Node *> thepath;
//	graph.aStar(graph.nodeArray()[0], graph.nodeArray()[2], thepath);//13 1
//	for (int i = thepath.size() - 1; i > -1; i--)
//	{
//		std::cout << "Location : " << thepath.at(i)->data().first << " Cost : " << thepath.at(i)->data().second << " h(n) : " << thepath.at(i)->getEstimatedDistToDest() << std::endl;
//		if (thepath.at(i) == graph.nodeArray()[1])
//		{
//			std::cout << std::endl;
//		}
//	}
//
//	string temp = thepath.at(1)->data().first;
//	int tempInt = std::stoi(temp);
//	tempTarget = waypoints.at(tempInt);
//}