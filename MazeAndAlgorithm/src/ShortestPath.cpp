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
	int* endPost = maze.getExit();
	int xA, yA, xB, yB;
	xA = startPos[0];
	yA = startPos[1];
	//xB = endPost[0];
	//yB = endPost[1];
	xB = 5;
	yB = 5;

	cout << "Map Size (X,Y): " << sizeX << "," << sizeY << endl;
	cout << "Start: " << xA << "," << yA << endl;
	cout << "Finish: " << xB << "," << yB << endl;
	// get the route
	clock_t start = clock();
	string route = pathFind(xA, yA, xB, yB);
	if (route == "") cout << "An empty route generated!" << endl;
	clock_t end = clock();
	double time_elapsed = double(end - start);
	cout << "Time to calculate the route (ms): " << time_elapsed << endl;
	cout << "Route:" << endl;
	cout << route << endl << endl;

	// follow the route on the map and display it 
	if (route.length()>0)
	{
		int j; char c;
		int x = xA;
		int y = yA;
		map[x][y] = 2;
		shortestRouteArray[x][y] = true;
		for (int i = 0; i<route.length(); i++)
		{
			c = route.at(i);
			j = atoi(&c);
			x = x + dx[j];
			y = y + dy[j];
			map[x][y] = 3;
			shortestRouteArray[x][y] = true;
		}
		map[x][y] = 4;
		shortestRouteArray[x][y] = true;

		// display the map with the route
		for (int x = 0; x<sizeX; x++)
		{
			for (int y = 0; y<sizeY; y++)
				if (map[x][y] == 0)
					cout << ".";
				else if (map[x][y] == 1)
					cout << "O"; //obstacle
				else if (map[x][y] == 2)
					cout << "S"; //start
				else if (map[x][y] == 3)
					cout << "R"; //route
				else if (map[x][y] == 4)
					cout << "F"; //finish
			cout << endl;
		}
		cout << endl;
	}
	//getchar(); // wait for a (Enter) keypress  
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
	sizeY = size+1;
	map = new int*[sizeX];
	closed_nodes_map = new int*[sizeX]; // map of closed (tried-out) nodes
	open_nodes_map = new int*[sizeX]; // map of open (not-yet-tried) nodes
	dir_map = new int*[sizeX]; // map of directions
	shortestRouteArray = new bool*[sizeX];
	for (int i = 0; i < sizeX; i++) {
		map[i] = new int[sizeY];
		closed_nodes_map[i] = new int[sizeY];
		open_nodes_map[i] = new int[sizeY];
		dir_map[i] = new int[sizeY];
		shortestRouteArray[i] = new bool[sizeY];
		for (int j = 0; j < sizeY; j++) {
			map[i][j] = mazeOutput[i][j] ? 0 : 1;
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
	cout << endl;
	cout << "Printing map to navigate: " << endl;
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

string ShortestPath::pathFind(const int & xStart, const int & yStart, const int & xFinish, const int & yFinish)
{
	int m = sizeY-1;
	int n = sizeX-1;
	static priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
	static int pqi; // pq index
	static node* n0;
	static node* m0;
	static int i, j, x, y, xdx, ydy;
	static char c;
	pqi = 0;

	// reset the node maps
	for (y = 0; y<m; y++)
	{
		for (x = 0; x<n; x++)
		{
			closed_nodes_map[x][y] = 0;
			open_nodes_map[x][y] = 0;
		}
	}

	// create the start node and push into list of open nodes
	n0 = new node(xStart, yStart, 0, 0);
	n0->updatePriority(xFinish, yFinish);
	pq[pqi].push(*n0);
	open_nodes_map[x][y] = n0->getPriority(); // mark it on the open nodes map

											  // A* search
	while (!pq[pqi].empty())
	{
		// get the current node w/ the highest priority
		// from the list of open nodes
		n0 = new node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
			pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

		x = n0->getxPos(); y = n0->getyPos();

		pq[pqi].pop(); // remove the node from the open list
		open_nodes_map[x][y] = 0;
		// mark it on the closed nodes map
		closed_nodes_map[x][y] = 1;

		// quit searching when the goal state is reached
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if (x == xFinish && y == yFinish)
		{
			// generate the path from finish to start
			// by following the directions
			string path = "";
			while (!(x == xStart && y == yStart))
			{
				j = dir_map[x][y];
				c = '0' + (j + dir / 2) % dir;
				path = c + path;
				x += dx[j];
				y += dy[j];
			}

			// garbage collection
			delete n0;
			// empty the leftover nodes
			while (!pq[pqi].empty()) pq[pqi].pop();
			return path;
		}

		// generate moves (child nodes) in all possible directions
		for (i = 0; i<dir; i++)
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if (!(xdx<0 || xdx>n - 1 || ydy<0 || ydy>m - 1 || map[xdx][ydy] == 1
				|| closed_nodes_map[xdx][ydy] == 1))
			{
				// generate a child node
				m0 = new node(xdx, ydy, n0->getLevel(),
					n0->getPriority());
				m0->nextLevel(i);
				m0->updatePriority(xFinish, yFinish);

				// if it is not in the open list then add into that
				if (open_nodes_map[xdx][ydy] == 0)
				{
					open_nodes_map[xdx][ydy] = m0->getPriority();
					pq[pqi].push(*m0);
					// mark its parent node direction
					dir_map[xdx][ydy] = (i + dir / 2) % dir;
				}
				else if (open_nodes_map[xdx][ydy]>m0->getPriority())
				{
					// update the priority info
					open_nodes_map[xdx][ydy] = m0->getPriority();
					// update the parent direction info
					dir_map[xdx][ydy] = (i + dir / 2) % dir;

					// replace the node
					// by emptying one pq to the other one
					// except the node to be replaced will be ignored
					// and the new node will be pushed in instead
					while (!(pq[pqi].top().getxPos() == xdx &&
						pq[pqi].top().getyPos() == ydy))
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop(); // remove the wanted node

								   // empty the larger size pq to the smaller one
					if (pq[pqi].size()>pq[1 - pqi].size()) pqi = 1 - pqi;
					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0); // add the better node instead
				}
				else delete m0; // garbage collection
			}
		}
		delete n0; // garbage collection
	}
	return ""; // no route found
}
