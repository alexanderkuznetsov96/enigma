//
// Created by Ken on 11/7/2016.
//

#pragma once
#include <math.h>
//size of maze, right now I have initialized it at 2
#define sizeOfMaze 2;

struct findNextNode{
    int xCoordinates;
    int zCoordinates;
    int whereWeAt;
    findNextNode *parent;
    float distanceFromCurrentNode;
    float heuristicDistance; //estimated distance to goal

    float getSum(){
        sum = distanceFromCurrentNode + heuristicDistance;
        return sum;
    }

    float currentNodetoCurrentTarget(findNextNode *targetNode){
        //Manhattan Distance
        float x = (float) (abs((float)(this -> xCoordinates - targetNode -> xCoordinates)));
        float z = (float) (abs((float)(this -> zCoordinates - targetNode -> zCoordinates)));

        return x+z;
    }

    //constructor
    findNextNode(){
        parent(0);
    }

    findNextNode(int x, int z, findNextNode *parent2 = 0){
        xCoordinates = x;
        zCoordinates = z;
        parent = (parent2);
        whereWeAt = x * sizeOfMaze + z;
        distanceFromCurrentNode = 0;
        heuristicDistance = 0;
    }

};


