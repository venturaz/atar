#pragma once
#include "Node.h"
#include <vector>

class PathFinder
{
public:
	PathFinder(int height, int width, Point start, Point end, bool** map);
	std::vector<Point> findPath();
	~PathFinder();
private:
	int width;
	int height;
	Node** nodes;
	Node* startNode;
	Node* endNode;
	void initializeNodes(bool **map, Point end);
	bool search(Node* current);
	std::vector<Node> getAdjacents(Node* node);
	std::vector<Point>getAdjacentLocations(Point point);
};

