/*
 * Testing.cpp
 *
 *  Created on: Nov 21, 2016
 *      Author: Sasha
 */
#include "Maze.h"

// main function for testing
int main(){
	Maze maze(5, 0, 0); // set to any desired size
	maze.printMaze();
	maze.outputMaze();
	maze.printOutput();
	return 0;
}
