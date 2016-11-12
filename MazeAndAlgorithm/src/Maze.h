/*
 * Maze.h
 *
 *  Created on: Nov 7, 2016
 *      Author: Sasha
 */

#ifndef MAZE_H_
#define MAZE_H_

#pragma once
#include <iostream>
#include <random>

// enumerate directions to be powers of 2, can use for bitwise AND and OR
enum {N=1,E=4,S=2,W=8};
//			  {0, 1, 2, 3, 4, 5, 6, 7, 8}
//            {0, N, S, 0, E, 0, 0, 0, W}
int DirX[9] = {0, 0, 0, 0, 1, 0, 0, 0, -1};	// x direction, positive is east
int DirY[9] = {0, -1, 1, 0, 0, 0, 0, 0, 0};	// y direction, positive is south
int OppD[9] = {0, S, N, 0, W, 0, 0, 0, E};	// opposite

class Maze {
public:
	Maze(int size);
	// fills the maze using recursive backtracking
	void RecursiveBacktrack(int startX, int startY);
	// display the maze
	void printMaze();
	void printOutput();
	// turns the maze into a boolean array
	bool** outputMaze();

private:
	void shuffleArray(int *array, int size);
	int size;		// dimension of the maze
	int** maze;		// the pointer to the maze
	int* storage;	// storage for easy access to maze
	bool** output;
	bool* outStorage;
};

#endif /* MAZE_H_ */
