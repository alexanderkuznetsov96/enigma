#include "ShortestPath.h"
#include "Node.h"
#include <queue>
#include <string>

using namespace std;

ShortestPath::ShortestPath(Maze maze) : maze(maze)
{
	// generate map
	generateMap();
	// get start and finish locations
	int* startPos = maze.getStart();
	int* endPos = maze.getExit();
	int xStart, yStart, xEnd, yEnd;
	xStart = startPos[0];
	yStart = startPos[1];
	xEnd = endPos[0];
	yEnd = endPos[1];

	// get the route
	string route = findPath(xStart, yStart, xEnd, yEnd);
	if (route == "") cout << "An empty route generated!" << endl;

	// follow the route on the map and display it 
	if (route.length()>0)
	{
		int directionAsInt; char directionAsC;
		int x = xStart;
		int y = yStart;
		maze_map[x][y] = 2;
		shortestRouteArray[x][y] = true;
		for (unsigned int i = 0; i<route.length(); i++)
		{
			directionAsC = route.at(i);
			directionAsInt = atoi(&directionAsC);
			x = x + dx[directionAsInt];
			y = y + dy[directionAsInt];
			maze_map[x][y] = 3;
			shortestRouteArray[x][y] = true;
		}
		maze_map[x][y] = 4;
		shortestRouteArray[x][y] = true;
	}
}

string ShortestPath::getShortestRouteString()
{
	return shortestRoute;
}

bool** ShortestPath::getShortestRouteArray()
{
	return shortestRouteArray;
}

void ShortestPath::generateMap()
{
	mazeOutput = maze.outputMaze();
	int size = maze.getOutSize();
	sizeX = size;
	sizeY = size;
	maze_map = new int*[sizeX];
	nodes_closed_map = new int*[sizeX]; // map of closed (tried-out) nodes
	nodes_open_map = new int*[sizeX]; // map of open (not-yet-tried) nodes
	map_dir = new int*[sizeX]; // map of directions
	shortestRouteArray = new bool*[sizeX];
	for (int i = 0; i < sizeX; i++) {
		maze_map[i] = new int[sizeY];
		nodes_closed_map[i] = new int[sizeY];
		nodes_open_map[i] = new int[sizeY];
		map_dir[i] = new int[sizeY];
		shortestRouteArray[i] = new bool[sizeY];
		for (int j = 0; j < sizeY; j++) {
			maze_map[i][j] = mazeOutput[i][j] ? 0 : 1;
			shortestRouteArray[i][j] = false;
		}
	}

	// DEBUGGING
	/*for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			map[j][i] = 0;
		}
	}

	for (int j = 3; j < sizeY-3; j++) {
		map[sizeX / 2][j] = 1;
	}*/

	// print map
	/*cout << endl;
	cout << "Printing map to navigate: " << endl;
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
	cout << endl;*/
}

string ShortestPath::findPath(const int & xStart, const int & yStart, const int & xFinish, const int & yFinish)
{
	int m = sizeY-1;
	int n = sizeX-1;
	static priority_queue<node> priorityq[2]; // list of open (not-yet-tried) nodes
	static int pqindex; // pq index
	static node* node0;
	static node* child0;
	static int i, j, x, y, xdx, ydy;
	static char c;
	pqindex = 0;

	// reset the node maps
	for (y = 0; y<m; y++)
	{
		for (x = 0; x<n; x++)
		{
			nodes_closed_map[x][y] = 0;
			nodes_open_map[x][y] = 0;
		}
	}

	// create the start node and push into list of open nodes
	node0 = new node(xStart, yStart, 0, 0);
	node0->updatePriority(xFinish, yFinish);
	priorityq[pqindex].push(*node0);
	nodes_open_map[x][y] = node0->getPriority(); // mark it on the open nodes map

											  // A* search
	while (!priorityq[pqindex].empty())
	{
		// get the current node w/ the highest priority
		// from the list of open nodesm0
		node0 = new node(priorityq[pqindex].top().getxPos(), priorityq[pqindex].top().getyPos(),
			priorityq[pqindex].top().getDistanceTravelled(), priorityq[pqindex].top().getPriority());

		x = node0->getxPos(); y = node0->getyPos();

		priorityq[pqindex].pop(); // remove the node from the open list
		nodes_open_map[x][y] = 0;
		// mark it on the closed nodes map
		nodes_closed_map[x][y] = 1;

		// quit searching when the goal state is reached
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if (x == xFinish && y == yFinish)
		{
			// generate the path from finish to start
			// by following the directions
			string path = "";
			while (!(x == xStart && y == yStart))
			{
				j = map_dir[x][y];
				c = '0' + (j + dir / 2) % dir;
				path = c + path;
				x += dx[j];
				y += dy[j];
			}

			// garbage collection
			delete node0;
			// empty the leftover nodes
			while (!priorityq[pqindex].empty()) priorityq[pqindex].pop();
			return path;
		}

		// generate moves (child nodes) in all possible directions
		for (i = 0; i<dir; i++)
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if (!(xdx<0 || xdx>n - 1 || ydy<0 || ydy>m - 1 || maze_map[xdx][ydy] == 1
				|| nodes_closed_map[xdx][ydy] == 1))
			{
				// generate a child node
				child0 = new node(xdx, ydy, node0->getDistanceTravelled(),
					node0->getPriority());
				child0->updateDistanceTravelled(i);
				child0->updatePriority(xFinish, yFinish);

				// if it is not in the open list then add into that
				if (nodes_open_map[xdx][ydy] == 0)
				{
					nodes_open_map[xdx][ydy] = child0->getPriority();
					priorityq[pqindex].push(*child0);
					// mark its parent node direction
					map_dir[xdx][ydy] = (i + dir / 2) % dir;
				}
				else if (nodes_open_map[xdx][ydy]>child0->getPriority())
				{
					// update the priority info
					nodes_open_map[xdx][ydy] = child0->getPriority();
					// update the parent direction info
					map_dir[xdx][ydy] = (i + dir / 2) % dir;

					// replace the node
					// by emptying one pq to the other one
					// except the node to be replaced will be ignored
					// and the new node will be pushed in instead
					while (!(priorityq[pqindex].top().getxPos() == xdx &&
						priorityq[pqindex].top().getyPos() == ydy))
					{
						priorityq[1 - pqindex].push(priorityq[pqindex].top());
						priorityq[pqindex].pop();
					}
					priorityq[pqindex].pop(); // remove the wanted node

								   // empty the larger size pq to the smaller one
					if (priorityq[pqindex].size()>priorityq[1 - pqindex].size()) pqindex = 1 - pqindex;
					while (!priorityq[pqindex].empty())
					{
						priorityq[1 - pqindex].push(priorityq[pqindex].top());
						priorityq[pqindex].pop();
					}
					pqindex = 1 - pqindex;
					priorityq[pqindex].push(*child0); // add the better node instead
				}
				else delete child0; // garbage collection
			}
		}
		delete node0; // garbage collection
	}
	return ""; // no route found
}
