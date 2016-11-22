#pragma once
#include <iostream>
#include <math.h>
#include <vector>

#include "Node.h"
#include "Vector.h"
//size of maze, right now I have initialized it at 2
#define sizeOfMaze 2;

using namespace std;

float Node::getSum(){
	//This value determines what node gets put into the second list. The smaller
	//the sum the higher priority the node. In other words it is most optimal.
	//So we want the smallest sum which is representing the cost
	float sum = distanceFromCurrentNode + heuristicDistance;
	return sum;
}

float Node::currentNodetoCurrentTarget(Node *targetNode){
	//Manhattan Distance
	//find the x and z coordinates from the current node we are at
	//float x = (float) (abs((float)((this -> xCoordinates) - (targetNode -> xCoordinates))));
	//float z = (float) (abs((float)((this -> zCoordinates) - (targetNode -> zCoordinates))));

	//return x+z;
	return 0;
}

//constructor
Node::Node(){
	parent = 0;
}

Node::Node(int x, int z, Node *parent2 = 0){
	xCoordinates = x;
	zCoordinates = z;
	parent = (parent2);
	//how you find where we are in the map
	whereWeAt = z * sizeOfMaze + x;
	//--------------------------------------
	distanceFromCurrentNode = 0;
	heuristicDistance = 0;
}
