#include "Pathfinding.h"

Pathfinding::Pathfinding()
{

}

Pathfinding::~Pathfinding()
{

}

sf::Vector2f Pathfinding::RunAStar(Graph<pair<string, int>, int>* graph, std::vector<sf::Vector2f>* waypoints, int *start, int *end)
{
	// Now traverse the graph.
 		std::vector<Node *> thepath;
		graph->aStar(graph->nodeArray()[*start], graph->nodeArray()[*end], thepath);//13 1
		for (int i = thepath.size() - 1; i > -1; i--)
		{
			std::cout << "Location : " << thepath.at(i)->data().first << " Cost : " << thepath.at(i)->data().second << " h(n) : " << thepath.at(i)->getEstimatedDistToDest() << std::endl;
			if (thepath.at(i) == graph->nodeArray()[1])
			{
				std::cout << std::endl;
			}
		}
	
		string temp = thepath.at(thepath.size() - 2)->data().first;
		int tempInt = std::stoi(temp);
		return waypoints->at(tempInt);
}

sf::Vector2f Pathfinding::searchNearestWaypoint(std::vector<sf::Vector2f>* waypoints, sf::Vector2f position)
{
	float differenceValue = std::numeric_limits<int>::max() - 10000;
	int differenceIndex;

	for (int i = 0; i < waypoints->size(); i++)
	{
		sf::Vector2f difference;
		difference.x = position.x - waypoints->at(i).x;
		difference.y = position.y - waypoints->at(i).y;

		float diff = sqrtf((difference.x*difference.x) + (difference.y*difference.y));
		if (diff < differenceValue)
		{
			differenceValue = diff;
			differenceIndex = i;
		}

	}

	return waypoints->at(differenceIndex);
}

int Pathfinding::getWaypointIndex(std::vector<sf::Vector2f>* waypoints, sf::Vector2f pos)
{
	int index;
	for (int i = 0; i < waypoints->size(); i++)
	{
		if (waypoints->at(i) == pos)
		{
			index = i;
		}
	}
	return index;
}

