/*
 * Maze.h
 *
 *  Created on: Nov 7, 2016
 *      Author: Sasha
 */

#ifndef MAZE_H_
#define MAZE_H_

#pragma once
#include <time.h>
#include <iostream>
#include <random>

// enumerate directions to be powers of 2, can use for bitwise AND and OR
enum {N=1,E=4,S=2,W=8};
//			  {0, 1, 2, 3, 4, 5, 6, 7, 8}
//            {0, N, S, 0, E, 0, 0, 0, W}

class Maze {
public:
	int DirX[9] = {0, 0, 0, 0, 1, 0, 0, 0, -1};	// x direction, positive is east
	int DirY[9] = {0, -1, 1, 0, 0, 0, 0, 0, 0};	// y direction, positive is south
	int OppD[9] = {0, S, N, 0, W, 0, 0, 0, E};	// opposite
	Maze(int size, int xstart, int ystart);
	// fills the maze using recursive backtracking
	void RecursiveBacktrack(int startX, int startY);
	// display the maze
	void printMaze();
	void printOutput();
	// turns the maze into a boolean array
	bool** outputMaze();
	bool** getShortestPath();
	void printShortestPath();

	// accessors
	int* getStart();
	int* getExit();
	int getOutSize();

private:
	void shuffleArray(int *array, int size);
	int size;			// dimension of the maze
	int** maze;			// the pointer to the maze
	int* storage;		// storage for easy access to maze

	int outSize;		// dimension of the output
	bool** output;		// pointer to the output
	bool* outStorage;	// storage for easy access

	int start[2];	// x and y position of maze entrance
	int exit[2];	// x and y position of maze exit
	bool** shortestPath = nullptr;
};

#endif /* MAZE_H_ */
