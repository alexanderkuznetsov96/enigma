/*
 * Maze.cpp
 *
 *  Created on: Nov 7, 2016
 *      Author: Sasha
 */
#include "Maze.h"
#include "stdlib.h"
#include "ShortestPath.h"

using namespace std;

Maze::Maze(int size, int xstart, int ystart) {
	srand(time(NULL));
	start[0] = xstart;
	start[1] = ystart;

	this->size = size;
	maze = new int*[size];
	storage = new int[size * size];
	for (int i = 0; i < size*size; i++)
		storage[i] = 0;
	// each "row" points to a section of the
	for (int i = 0; i < size; i++)
		maze[i] = storage + size * i;

	this->outSize = size * 2 + 1;
	// Make the exit the opposite corner;
	exit[0] = outSize - 2;
	exit[1] = exit[0];
	output = new bool*[outSize];
	outStorage = new bool[outSize * outSize];
	for (int i = 0; i < (outSize * outSize); i++)
		outStorage[i] = true;
	for (int i = 0; i < outSize; i++)
		output[i] = outStorage + outSize * i;

	RecursiveBacktrack(xstart, ystart);
}

// returns the output, a grid that can be used to interpret the maze as
// empty space or wall, false reps wall, true reps empty space
bool** Maze::outputMaze() {
	for(int y = 0; y < size; y++){
		output[y*2][0] = false;
		output[y*2+1][0] = false;
		output[y*2][size*2] = false;
		output[y*2+1][size*2] = false;
		output[size*2][y*2] = false;
		output[size*2][y*2+1] = false;
		for(int x = 0; x < size; x++){
			output[y*2][x*2] = false;
			if((maze[y][x] & W) ==  0)
				output[y*2+1][x*2] = false;
			if((maze[y][x] & N) == 0)
				output[y*2][x*2+1] = false;
		}
	}
	output[size*2][size*2] = false;
	return output;
}

bool** Maze::getShortestPath()
{
	if (shortestPath == nullptr) {
		ShortestPath sp(*this);
		shortestPath = sp.getShortestRouteArray();
	}
	return shortestPath;
}

void Maze::printShortestPath()
{
	cout<< "Printing Shortest Path" << endl;

	if (shortestPath == nullptr) {
		getShortestPath();
	}
	for (int i = 0; i < outSize; i++) {
		for (int j = 0; j < outSize; j++) {
			cout << ((shortestPath[i][j]) ? "1" : "0");
		}
		cout << endl;
	}
	cout << endl;
}

void Maze::printOutput(){
	for(int i = 0; i < size*2+1; i++){
		for(int j = 0; j < size*2+1; j++){
			cout << ((output[i][j])?" ":"0");
		}
		cout << endl;
	}
	cout << endl;
}

void Maze::printMaze() {
	for(int x = 0; x < (size * 2); x++) {
		cout << "_";
	}
	cout << endl;

	// this code displays an ASCII representation of the maze
	// useful for seeing how the maze looks visually
	// shows how the bits are accessed to check where passages lie
	for(int y = 0; y < size; y++) {
		cout << "|";
		for(int x = 0; x < size; x++) {
			// if bitwise AND gives 0 then there is no path to the south
			if((maze[y][x] & S) !=  0)
				cout << " ";
			else
				cout << "_";
			// if bitwise ANd gives 0 then there is no path to the east
			if((maze[y][x] & E) != 0){
				// if this location or the one directly south have a southern path
				if (((maze[y][x] | maze[y][x+1]) & S) != 0)
					cout << " ";
				else
					cout << "_";
			}
			else
				cout << "|";
		}
		cout << endl;
	}
	cout << endl;
}

// starts at a maze location and carves a path until hitting maze bounds or a "wall"
// uses recursion to follow all paths possible before returning to start call
void Maze::RecursiveBacktrack(int startX, int startY) {
	int deltaX, deltaY, nextX, nextY;
	int directions[4] = {N, E, S, W};

	//shuffle the array of directions
	shuffleArray(directions, 4);

	// iterates through all directions and checks if the maze position is valid or if at bounds of maze
	for(int i = 0; i < 4; i++) {
		deltaX = DirX[directions[i]];
		deltaY = DirY[directions[i]];
		nextX = startX + deltaX;
		nextY = startY + deltaY;
		// check if the maze location is valid
		if (((nextX < size) & (nextX >= 0)) & ((nextY < size) & (nextY >= 0))) {
			//check if maze is not visited at the next location
			if (maze[nextY][nextX] == 0) {
				// bitwise OR the value with the direction
				maze[startY][startX] = (int)((int)maze[startY][startX] | (int)directions[i]);
				maze[nextY][nextX] = (int)((int)maze[nextY][nextX] | (int)OppD[directions[i]]);
				RecursiveBacktrack(nextX, nextY); // recursive call starting from next position
			}
		}
	}
}

// shuffle the array, need to implement better random generation for C++,
// same maze generated for the same parameters every time
void Maze::shuffleArray(int *arr, int size) {
	int i;
	for(i = 0; i < (size - 1); i++) {
		int r = i + (rand() % (size - i));
		int temp = arr[i];
		arr[i] = arr[r];
		arr[r] = temp;
	}
}

int* Maze::getStart(){
	return start;
}

int* Maze::getExit(){
	return exit;
}

int Maze::getOutSize()
{
	return outSize;
}
