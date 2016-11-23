/*
 * Testing.cpp
 *
 *  Created on: Nov 21, 2016
 *      Author: Sasha
 */
#include "Maze.h"
#include "ShortestPath.h"

// main function for testing
int main(){
	Maze maze(5); // set to any desired size
	maze.printMaze();
	maze.outputMaze();
	maze.printOutput();
	ShortestPath sp(maze);
	Vector start(0,0,0);
	Vector dest(5,0,5);
	sp.FindPath(start, dest);
	return 0;
}
