#include "Pathfinding.h"

Pathfinding::Pathfinding()
{

}

Pathfinding::~Pathfinding()
{

}

sf::Vector2f Pathfinding::RunAStar(Graph<pair<string, int>, int>* graph, std::vector<sf::Vector2f>* waypoints)
{
	// Now traverse the graph.
 		std::vector<Node *> thepath;
		graph->aStar(graph->nodeArray()[0], graph->nodeArray()[3], thepath);//13 1
		for (int i = thepath.size() - 1; i > -1; i--)
		{
			std::cout << "Location : " << thepath.at(i)->data().first << " Cost : " << thepath.at(i)->data().second << " h(n) : " << thepath.at(i)->getEstimatedDistToDest() << std::endl;
			if (thepath.at(i) == graph->nodeArray()[1])
			{
				std::cout << std::endl;
			}
		}
	
		string temp = thepath.at(1)->data().first;
		int tempInt = std::stoi(temp);
		return waypoints->at(tempInt);
}
