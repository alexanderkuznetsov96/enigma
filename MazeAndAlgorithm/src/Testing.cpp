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
	int size = 5;
	Maze maze(size, 1, 1); // set to any desired size
	maze.printMaze();
	cout << endl;
	maze.outputMaze();
	cout << "Maze Output: " << endl;
	maze.printOutput();
	cout << endl;
	maze.getShortestPath();
	maze.printShortestPath();
	//getchar();
	return 0;
}
