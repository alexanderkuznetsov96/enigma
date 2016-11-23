#pragma once
#include <math.h>
#include <vector>

#include "Node.h"
#include "Vector.h"
#include "Maze.h"

using namespace std;

//size of maze, right now I have initialized it at 2
#define sizeOfMaze 2;

class ShortestPath{
public:
    //There will be two lists in this algorithm. The first list will have all the nodes its currently checking. This list
    // will contain all the adjacent nodes to the current node. It will take the best candidate. The second
    //list would contain the nodes that we have already visited and checked
    ShortestPath(Maze maze);
    //has start goal been initialized
    bool optimalStartingNode;
    //has reached the final destination
    bool optimalDestinationNode;
    void FindPath(Vector currentPositionofEnemy, Vector destinationPosition);
    Vector nextPositionFromList();
    Maze* maze;
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
    Node* getNode();
    Node* startNode;
    Node* destinationNode;
    vector<Node*> initialList;
    vector<Node*> visitedList;
    //dynamic so use a vector here
    vector<Vector*> nextNodeForPathList; //next node that will be added to the list for the most optimal path
    void startingNodeAndDestinationNode(Node start, Node destination);
    //see if node is in initial list
    void checkCurrentNode(int cost, int x, int z, Node *parent);
    void keepOnFindingthePath();
};

