//
// Created by Ken on 11/7/2016.
//
using namespace std;
#pragma once
#include "findNextNode.h"
#include <math.h>
#include <vector>
#include "Vector3.h"
//size of maze, right now I have initialized it at 2
#define sizeOfMaze 2;

class ShortestPath{
public:
    ShortestPath(void);
    //has start goal been initialized
    bool optimalStartingNode;
    //has reached the final destination
    bool optimalDestinationNode;
    void FindPath(Vector3 currentPositionofEnemy, Vector3 destinationPosition);
    vector nextPositionFromList();

    void initializeInitialList(){
        initialList.clear();
    }

    void initializeVisitedList(){
        visitedList.clear();
    }

    void initializeNextNodeForPathList(){
        nextNodeForPathList.clear();
    }

private:
    findNextNode *getNode;
    findNextNode *startNode;
    findNextNode *destinationNode;
    vector<findNextNode*> initialList;
    vector<findNextNode*> visitedList;
    //dynamic so use a vector here
    vector<vector*> nextNodeForPathList;
    void startingNodeAndDestinationNode(findNextNode start, findNextNode destination);
    //see if node is in initial list
    void checkCurrentNode(int cost, int x, int z, findNextNode *parent);
    void findPath();
};

