using namespace std;
#include <iostream>
#include "findNextNode.h"
#include "ShortestPath.h"
#include "Vector3.h"

ShortestPath::ShortestPath(void){
    optimalStartingNode = false;
    //has reached the final destination
    optimalDestinationNode = false;

}

void ShortestPath::FindPath(Vector3 currentPositionofEnemy, Vector3 destinationPosition) {
    if(!optimalStartingNode){
        for(int i = 0; i < initialList.size(); i++){
            //clear open list
            delete(initialList[i]);
        }//end for
        initialList.clear();
        for(int j = 0; j < visitedList.size(); j++){
            //clear open list
            delete(visitedList[j]);
        }//end for
        visitedList.clear();
        for(int k = 0; k < nextNodeForPathList.size(); k++){
            //clear open list
            delete(nextNodeForPathList[k]);
        }//end for
        nextNodeForPathList.clear();

        //Start
        findNextNode start;
        start.xCoordinates = currentPositionofEnemy.x;
        start.zCoordinates = currentPositionofEnemy.z;

        //Destination
        findNextNode destination;
        destination.xCoordinates = destinationPosition.x;
        destination.zCoordinates = destinationPosition.z;

        startingNodeAndDestinationNode(start, destination);
        optimalStartingNode = true;
    }//end if
    else{
        findPath();
    }//end else
}

void ShortestPath::startingNodeAndDestinationNode(findNextNode start, findNextNode destination) {
    startNode = new findNextNode(start.xCoordinates, start.zCoordinates, 0);
    destinationNode = new findNextNode(destination.xCoordinates, destination.zCoordinates, &destination);

    startNode->distanceFromCurrentNode = 0;
    startNode->heuristicDistance = startNode->currentNodetoCurrentTarget(destinationNode);
    startNode->parent = 0;

    initialList.push_back(startNode);

}

findNextNode* ShortestPath::getNode(){

    float optimalSum; //set this to infinitiy*************
    int nodeIndex = 0;
    findNextNode* nextNode = NULL;

    for(int i = 0; i < initialList.size(); i++){
        if(initialList[i]->getSum() < optimalSum){
            optimalSum = initialList[i]->getSum();
            nodeIndex = i;
        }//end if
    }//end for

    if(nodeIndex >= 0){
        nextNode = initialList[nodeIndex];
        visitedList.push_back(nextNode);
        initialList.erase(initialList.begin() + nodeIndex);
    }//end if

    return nextNode;
}

void ShortestPath::checkCurrentNode(int cost, int x, int z, findNextNode *parent) {
    if(/*check if there is a wall*/){
        return;
    }
    int whatWeAtInVisitedList = z * sizeOfMaze + x;
    for(int i = 0; i < visitedList.size(); i++){
        if(whatWeAtInVisitedList == visitedList[i]->whereWeAt){
            //check visited list, if that cell already in visited list, just return
            return;
        }//end if
    }//end for

    findNextNode* newNode = new findNextNode(x, z, parent);
    newNode->distanceFromCurrentNode = cost;
    newNode->heuristicDistance = parent->currentNodetoCurrentTarget(destinationNode);

    for(int j = 0; j < initialList.size(); j++){
        if(whatWeAtInVisitedList == initialList[j]->whereWeAt){
            float newSum = newNode->distanceFromCurrentNode + cost + initialList[j]->heuristicDistance;
            if(initialList[j]->getSum() > newSum){
                initialList[j] -> distanceFromCurrentNode = newNode->distanceFromCurrentNode + cost;
                initialList[j]->parent = newNode;
            }//end nested if
            else{
                //sum is less than what we're looking for so lets just get rid of that
                delete newNode;
                return;
            }//end nested else
        }//end if
    }//end for
    initialList.push_back(newNode);
}