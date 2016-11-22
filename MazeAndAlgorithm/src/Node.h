#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <math.h>
//size of maze, right now I have initialized it at 2
#define sizeOfMaze 2;

using namespace std;

class Node{
public:
	int xCoordinates;
	int zCoordinates;
	int whereWeAt;
	Node *parent; //previous, starting node
	//There will be two lists in this algorithm. The first list will have all the nodes its currently checking. This list
	// will contain all the adjacent nodes to the current node. It will take the best candidate. To find the best candidate
	//we look at the distance from the current node (G) and the heuristic distance (H)
	float distanceFromCurrentNode;
	float heuristicDistance; //estimated distance from the node to the destination
	float getSum();
	float currentNodetoCurrentTarget(Node *targetNode);
	Node(int x, int z, Node *parent);
	Node();
private:
};
