/*
 * Maze.cpp
 *
 *  Created on: Nov 7, 2016
 *      Author: Sasha
 */
#include "Maze.h"
using namespace std;

// main function for testing
int main(){
	Maze maze(5); // set to any desired size
	maze.RecursiveBacktrack(0, 0); // starts from top left corner
	maze.printMaze();
	maze.outputMaze();
	maze.printOutput();
	return 0;
}

Maze::Maze(int size) {
	this->size = size;
	maze = new int*[size];
	storage = new int[size * size];
	for (int i = 0; i < size*size; i++)
		storage[i] = 0;
	// each "row" points to a section of the
	for (int i = 0; i < size; i++)
		maze[i] = storage + size * i;

	int outSize = size * 2;
	output = new bool*[outSize];
	outStorage = new bool[(outSize+1) * outSize];
	for (int i = 0; i < (outSize+1) * outSize; i++)
		outStorage[i] = false;
	for (int i = 0; i < outSize; i++)
		output[i] = outStorage + (outSize+1) * i;
}

// returns the output, a grid that can be used to interpret the maze as
// empty space or wall, false reps wall, true reps empty space
bool** Maze::outputMaze() {
	for(int y = 0; y < size; y++){
		output[y*2][0] = false;
		for(int x = 0; x < size; x++){
			if(y >= size/2){
				if((maze[y][x] & S) !=  0)
					output[y*2+1][x*2+1] = true;
				if((maze[y][x] & W) !=  0)
					output[y*2][x*2] = true;
				if((maze[y][x] & E) !=  0)
					output[y*2][x*2+1] = true;
				if((maze[y][x] & N) != 0)
					output[y*2][x*2+1] = true;
			}
			else{
				if((maze[y][x] & S) !=  0)
					output[y*2+1][x*2+1] = true;
				if((maze[y][x] & E) !=  0)
					output[y*2+1][x*2+1] = true;
				if((maze[y][x] & W) !=  0)
					output[y*2+1][x*2] = true;
				if((maze[y][x] & N) != 0)
					output[y*2][x*2+1] = true;
			}
		}
		output[y][size*2] = false;
	}
	return output;
}

void Maze::printOutput(){
	for(int i = 0; i < size*2; i++){
		for(int j = 0; j < size*2+1; j++){
			cout << ((output[i][j])?" ":"0");
		}
		cout << endl;
	}
	cout << endl;
}

void Maze::printMaze() {
	for(int i = 0; i < this->size; i++){
		for(int j = 0; j < this->size; j++){
			cout << maze[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;

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


