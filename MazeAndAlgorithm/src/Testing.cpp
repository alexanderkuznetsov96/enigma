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
	cout << "Test size 5 maze: " << endl;
	int size = 5;
	Maze maze1(size, 1, 1); // set to any desired size
	maze1.printMaze();
	cout << endl;
	//maze.outputMaze();
	//cout << "Maze Output: " << endl;
	//maze.printOutput();
	//cout << endl;
	clock_t start = clock();
	maze1.getShortestPath();
	clock_t end = clock();
	double time_elapsed = double(end - start);
	cout << "Time to calculate the route (ms): " << time_elapsed << endl;
	maze1.printShortestPath();

	cout << endl;
	cout << "Test size 10 maze: " << endl;
	size = 10;
	Maze maze2(size, 1, 1); // set to any desired size
	maze2.printMaze();
	cout << endl;
	start = clock();
	maze2.getShortestPath();
	end = clock();
	time_elapsed = double(end - start);
	cout << "Time to calculate the route (ms): " << time_elapsed << endl;
	maze2.printShortestPath();

	cout << endl;
	cout << "Test size 15 maze: " << endl;
	size = 15;
	Maze maze3(size, 1, 1); // set to any desired size
	maze3.printMaze();
	cout << endl;
	start = clock();
	maze3.getShortestPath();
	end = clock();
	time_elapsed = double(end - start);
	cout << "Time to calculate the route (ms): " << time_elapsed << endl;
	maze3.printShortestPath();

	cout << endl;
	cout << "Test size 20 maze: " << endl;
	size = 20;
	Maze maze4(size, 1, 1); // set to any desired size
	maze4.printMaze();
	cout << endl;
	start = clock();
	maze4.getShortestPath();
	end = clock();
	time_elapsed = double(end - start);
	cout << "Time to calculate the route (ms): " << time_elapsed << endl;
	maze4.printShortestPath();

	cout << endl;
	cout << "Test size 30 maze: " << endl;
	size = 30;
	Maze maze5(size, 1, 1); // set to any desired size
	maze5.printMaze();
	cout << endl;
	start = clock();
	maze5.getShortestPath();
	end = clock();
	time_elapsed = double(end - start);
	cout << "Time to calculate the route (ms): " << time_elapsed << endl;
	maze5.printShortestPath();

	cout << endl;
	cout << "Test size 40 maze: " << endl;
	size = 40;
	Maze maze6(size, 1, 1); // set to any desired size
	maze6.printMaze();
	cout << endl;
	start = clock();
	maze6.getShortestPath();
	end = clock();
	time_elapsed = double(end - start);
	cout << "Time to calculate the route (ms): " << time_elapsed << endl;
	maze6.printShortestPath();

	cout << endl;
	cout << "Test size 100 maze: " << endl;
	size = 100;
	Maze maze7(size, 1, 1); // set to any desired size
	maze7.printMaze();
	cout << endl;
	start = clock();
	maze7.getShortestPath();
	end = clock();
	time_elapsed = double(end - start);
	cout << "Time to calculate the route (ms): " << time_elapsed << endl;
	maze7.printShortestPath();

	cout << endl;
	cout << "Testing lazy initialization (getShortestPath() of maze above): " << endl;
	start = clock();
	maze7.getShortestPath();
	end = clock();
	time_elapsed = double(end - start);
	cout << "Time to calculate the route (ms): " << time_elapsed << endl;

	return 0;
}
