#include "PathFinder.h"
#include <iostream>
#include <algorithm>


PathFinder::PathFinder(int h, int w, Point start, Point end, bool** map)
{
	width = w;
	height = h;
	initializeNodes(map, end);
	startNode = &nodes[start.first][start.second];
	startNode->setState(OPEN);
	endNode = &nodes[end.first][end.second];
}

std::vector<Point> PathFinder::findPath()
{
	std::vector<Point> points;
	bool success = search(startNode);
	if (success)
	{
		// If a path was found, follow the parents from the end node to build a list of locations
		Node *node = endNode;
		while (node->getParentNode() != nullptr)
		{
			points.push_back(node->getLocation());
			node = node->getParentNode();
		}

	}
	return points;
}

PathFinder::~PathFinder()
{
}

void PathFinder::initializeNodes(bool **map, Point end)
{
	nodes = new Node*[height];
	for (int i = 0; i < height; ++i)
		nodes[i] = new Node[width];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			nodes[i][j] = Node(j, i, map[i][j], end);
		}
	}
}

bool myComparison(Node & a,Node & b)
{
	return (a.getF()) < (b.getF());
}

bool PathFinder::search(Node* currentNode)
{
	// Set the current node to Closed since it cannot be traversed more than once
	currentNode->setState(CLOSED);

	//sort
	std::vector<Node> nextNodes = getAdjacents(currentNode);
	std::sort(nextNodes.begin(), nextNodes.end(), myComparison);
	//nextNodes = Node::sortNodes(nextNodes);


	// Sort by F-value so that the shortest possible routes are considered first
	//nextNodes.Sort((node1, node2) = > node1.F.CompareTo(node2.F));
	for (int i = 0; i < nextNodes.size(); i++)
	{
		Node* nextNode = &(nextNodes.at(i));
		// Check whether the end node has been reached
		if (nextNode->getLocation() == endNode->getLocation())
		{
			return true;
		}
		else
		{
			// If not, check the next set of nodes
			if (search(nextNode)) // Note: Recurses back into Search(Node)
				return true;
		}
	}

	// The method returns false if this path leads to be a dead end
	return false;
}

std::vector<Node> PathFinder::getAdjacents(Node* fromNode)
{
	std::vector<Node> walkableNodes;
	std::vector<Point> nextLocations = getAdjacentLocations(fromNode->getLocation());

	for (int i = 0; i < nextLocations.size(); i++)
	{
		Point location = nextLocations.at(i);
		int y = location.first;
		int x = location.second;

		// Stay within the grid's boundaries
		if (x < 0 || x >= width || y < 0 || y >= height)
			continue;

		Node* node = &nodes[y][x];
		// Ignore non-walkable nodes
		if (!node->isWalkable())
			continue;

		// Ignore already-closed nodes
		if (node->getState() == CLOSED)
			continue;

		if(y==4 && x==2){
			std::cout << "(x: " << x << ", y: " << y << ")"<< std::endl;
		}

		// Already-open nodes are only added to the list if their G-value is lower going via this route.
		if (node->getState() == OPEN)
		{
			if (node->getParentNode()!=nullptr)
			{
				float traversalCost = Node::getTraversalCost(node->getLocation(), node->getParentNode()->getLocation());
				float gTemp = fromNode->getG() + traversalCost;
				if (gTemp < node->getG())
				{
					(&nodes[y][x])->setParentNode(fromNode);
					//nodes[node->getLocation().first][node->getLocation().second].setParentNode(&fromNode);
					std::cout << "set parent of " << "(" << (&nodes[y][x])->getLocation().first << "," << (&nodes[y][x])->getLocation().second << ") to " << "(" << fromNode->getLocation().first << "," << fromNode->getLocation().second << ")" << fromNode << std::endl;
					walkableNodes.push_back(*node);
				}
			}

		}
		else
		{
			// If it's untested, set the parent and flag it as 'Open' for consideration
			(&nodes[y][x])->setParentNode(fromNode);
			//nodes[node->getLocation().first][node->getLocation().second].setParentNode(&fromNode);
			std::cout << "set parent of " << "(" << (&nodes[y][x])->getLocation().first << "," << (&nodes[y][x])->getLocation().second << ") to " << "(" << fromNode->getLocation().first << "," << fromNode->getLocation().second << ")" <<  fromNode << std::endl;
			node->setState(OPEN);
			walkableNodes.push_back(*node);
		}
	}

	return walkableNodes;
}

std::vector<Point> PathFinder::getAdjacentLocations(Point point)
{
	std::vector<Point> adj;
	int i = point.first;
	int j = point.second;
	if (i - 1 >= 0 && j - 1 >= 0)
		adj.push_back(Point(i - 1, j - 1));
	if (i - 1 >= 0 && j >= 0)
		adj.push_back(Point(i - 1, j));
	if (i - 1 >= 0 && j + 1 < width)
		adj.push_back(Point(i - 1, j + 1));
	if (i >= 0 && j + 1 < width)
		adj.push_back(Point(i, j + 1));
	if (i + 1 < height && j + 1 < width)
		adj.push_back(Point(i + 1, j + 1));
	if (i + 1 < height  && j >= 0)
		adj.push_back(Point(i + 1, j));
	if (i + 1 < height  && j - 1 >= 0)
		adj.push_back(Point(i + 1, j - 1));
	if (i >= 0 && j - 1 >= 0)
		adj.push_back(Point(i, j - 1));

	return  adj;
}
