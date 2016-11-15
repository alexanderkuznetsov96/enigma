#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <math.h>
//size of maze, right now I have initialized it at 2
#define sizeOfMaze 2;

using namespace std;

struct findNextNode{
    int xCoordinates;
    int zCoordinates;
    int whereWeAt;
    findNextNode *parent; //previous, starting node
    //There will be two lists in this algorithm. The first list will have all the nodes its currently checking. This list
    // will contain all the adjacent nodes to the current node. It will take the best candidate. To find the best candidate
    //we look at the distance from the current node (G) and the heuristic distance (H)
    float distanceFromCurrentNode;
    float heuristicDistance; //estimated distance from the node to the destination

    float getSum(){
        //This value determines what node gets put into the second list. The smaller
        //the sum the higher priority the node. In other words it is most optimal.
        //So we want the smallest sum which is representing the cost
        float sum = distanceFromCurrentNode + heuristicDistance;
        return sum;
    }

    float currentNodetoCurrentTarget(findNextNode *targetNode){
        //Manhattan Distance
        //find the x and z coordinates from the current node we are at
        float x = (float) (abs((float)((this -> xCoordinates) - (targetNode -> xCoordinates))));
        float z = (float) (abs((float)((this -> zCoordinates) - (targetNode -> zCoordinates))));

        return x+z;
    }

    //constructor
    findNextNode(){
        parent = 0;
    }

    findNextNode(int x, int z, findNextNode *parent2 = 0){
        xCoordinates = x;
        zCoordinates = z;
        parent = (parent2);
        //how you find where we are in the map
        whereWeAt = z * sizeOfMaze + x;
        //--------------------------------------
        distanceFromCurrentNode = 0;
        heuristicDistance = 0;
    }

};

//----------------------------------------------------------------------------------------------------------
struct Vector{
    int x;
    int y;
    int z;
    //------------------------------------------
    float length(){
        sqrt((x*x) + (y*y) + (z*z));
    }
    //------------------------------------------
    Vector();
    Vector(int x, int y, int z);
};



