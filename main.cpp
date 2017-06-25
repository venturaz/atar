
#include "Node.h"
#include "PathFinder.h"
#include <iostream>

#define HEIGHT 5
#define WIDTH 7

using namespace  std;
int main()
{
	Point startLocation(1, 2);
	Point endLocation(4, 2);
	bool** map;
	map = new bool*[HEIGHT];
	for (int i = 0; i < HEIGHT; ++i)
		map[i] = new bool[WIDTH];

	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			map[i][ j] = true;



	//this.searchParameters = new SearchParameters(startLocation, endLocation, map);
	PathFinder path_finder(HEIGHT, WIDTH, startLocation, endLocation, map);
	vector<Point> path = path_finder.findPath();
	for (int i = 0; i < path.size(); i++)
		cout << path.at(i).first << "," << path.at(i).second << endl;

}

