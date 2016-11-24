#pragma once

#include <string>
#include "Maze.h"

using namespace std;

class ShortestPath {
public:
	ShortestPath(Maze maze);
	string getShortestRouteString();
	bool** getShortestRouteArray();
private:
	// A-star algorithm.
	// The route returned is a string of direction digits.
	string pathFind(const int & xStart, const int & yStart,const int & xFinish, const int & yFinish);
	Maze maze;
	bool** mazeOutput;
	int** map;
	int** closed_nodes_map; // map of closed (tried-out) nodes
	int** open_nodes_map; // map of open (not-yet-tried) nodes
	int** dir_map; // map of directions
	int sizeX;
	int sizeY;
	void generateMap();
	string shortestRoute;
	bool** shortestRouteArray;
};