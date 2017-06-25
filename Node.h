#pragma once
#include <utility>
#include <vector>
typedef std::pair<int, int>	Point;
enum NodeState{UNTESTED, OPEN, CLOSED };
class Node
{
public:
	Node(int x, int y, bool isWalkable, Point endLocation);
	Node();
	void setG(float g);
	float getG() ;

	float getH() ;
	void setH(float h);

	float getF() ;
	void setF(float f);

	NodeState getState() ;
	void setState(NodeState state);

	Node* getParentNode() ;
	void setParentNode(Node * node);

	Point getLocation() ;
	bool isWalkable();

	~Node();
	static float getTraversalCost(Point src, Point dst);
	static std::vector<Node> sortNodes(std::vector<Node> nodes);

	Node* ParentNode;
private:
	float G;
	float H;
	float F;
	Point Location;
	bool IsWalkable;
	NodeState State;
};

