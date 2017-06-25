#include "Node.h"
#include "math.h"

#include <iostream>
using namespace std;



Node::Node(int x, int y, bool isWalkable, Point endLocation)
{
	Location = Point(y, x);
	State = UNTESTED;
	IsWalkable = isWalkable;
	H = getTraversalCost(Location, endLocation);
	G = 0;
	F = G + H;
	ParentNode = nullptr;
}

Node::Node()
{
	ParentNode = nullptr;
}

float Node::getG() 
{
	return G;
}

void Node::setG(float g)
{
	G = g;
}

float Node::getH() 
{
	return H;
}

void Node::setH(float h)
{
	H = h;
}

float Node::getF() 
{
	return G+H;
}

void Node::setF(float f)
{
	F = f;
}

NodeState Node::getState() 
{
	return State;
}

void Node::setState(NodeState state)
{
	State = state;
}

Node* Node::getParentNode() 
{
	return ParentNode;
}

void Node::setParentNode(Node * node)
{
	ParentNode = node;
	//std::cout << "#### set parent of " << "(" << getLocation().first << "," << getLocation().second << ") to " << "(" << ParentNode->getLocation().first << "," << node->getLocation().second << ")" << node << std::endl;
	G = ParentNode->getG() + getTraversalCost(Location, ParentNode->getLocation());
}

Point Node::getLocation() 
{
	return Location;
}

bool Node::isWalkable()
{
	return IsWalkable;
}


Node::~Node()
{
}

float Node::getTraversalCost(Point src,Point dst)
{
	float deltaX = dst.second - src.second;
	float deltaY = dst.first - src.first;
	return float(sqrt(deltaX * deltaX + deltaY * deltaY));
}

std::vector<Node> Node::sortNodes(std::vector<Node> nodes)
{
	std::vector<Node>sorted = nodes;
	for (size_t i = 0; i < sorted.size(); i++)
	{
		for (size_t j = 0; j< sorted.size(); j++)
		{
			if (sorted.at(j).getF() > sorted.at(i).getF())
			{
				std::swap(sorted.at(i), sorted.at(j));
			}
		}
	}
	return sorted;
}
