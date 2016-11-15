#pragma once
#include <math.h>
#include <vector>
#include "findNextNode.h"

using namespace std;

//size of maze, right now I have initialized it at 2
#define sizeOfMaze 2;

class ShortestPath{
public:
    //There will be two lists in this algorithm. The first list will have all the nodes its currently checking. This list
    // will contain all the adjacent nodes to the current node. It will take the best candidate. The second
    //list would contain the nodes that we have already visited and checked
    ShortestPath(void);
    //has start goal been initialized
    bool optimalStartingNode;
    //has reached the final destination
    bool optimalDestinationNode;
    void FindPath(Vector currentPositionofEnemy, Vector destinationPosition);
    Vector nextPositionFromList();

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
    findNextNode* getNode();
    findNextNode* startNode;
    findNextNode* destinationNode;
    vector<findNextNode*> initialList;
    vector<findNextNode*> visitedList;
    //dynamic so use a vector here
    vector<Vector*> nextNodeForPathList; //next node that will be added to the list for the most optimal path
    void startingNodeAndDestinationNode(findNextNode start, findNextNode destination);
    //see if node is in initial list
    void checkCurrentNode(int cost, int x, int z, findNextNode *parent);
    void keepOnFindingthePath();
};

