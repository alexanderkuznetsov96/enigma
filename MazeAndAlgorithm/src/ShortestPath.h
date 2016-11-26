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
	string findPath(const int & xStart, const int & yStart,const int & xFinish, const int & yFinish);
	Maze maze;
	bool** mazeOutput;
	int** maze_map;
	int** nodes_closed_map; // map of closed (tried-out) nodes
	int** nodes_open_map; // map of open (not-yet-tried) nodes
	int** map_dir; // map of directions
	int sizeX;
	int sizeY;
	void generateMap();
	string shortestRoute;
	bool** shortestRouteArray;
};