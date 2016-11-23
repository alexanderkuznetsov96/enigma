#pragma once
#include <iostream>
#include "ShortestPath.h"

#include "Node.h"
#include "Vector.h"

using namespace std;

ShortestPath::ShortestPath(Maze maze): maze(&maze){
    optimalStartingNode = false;
    //has reached the final destination
    destinationNode = NULL;
    startNode = NULL;
    optimalDestinationNode = false;
}

void ShortestPath::FindPath(Vector currentPositionofEnemy, Vector destinationPosition) {
    if(!optimalStartingNode){
        //Essentially we are initializing the stuff here.
        //If it doesnt belong in the optimal starting node list, delete it and clear it out of the list
        for(int i = 0; i < initialList.size(); i++){
            //clear open list if theres anything in it
            delete(initialList[i]);
        }//end for
        //clear it
        initialList.clear();
        //If the visited list does not have nodes that belong in the optimal list we dont need it
        for(int j = 0; j < visitedList.size(); j++){
            //clear open list
            delete(visitedList[j]);
        }//end for
        visitedList.clear();
        //If the next node for the path to the destination list does not have nodes that belong in the optimal list we dont need it
        for(int k = 0; k < nextNodeForPathList.size(); k++){
            //clear open list
            delete(nextNodeForPathList[k]);
        }//end for
        nextNodeForPathList.clear();

        //Start
        Node start;
        //get the x and z coordinate value
        start.xCoordinates = currentPositionofEnemy.x;
        start.zCoordinates = currentPositionofEnemy.z;

        //Destination, we want to know the destination for the heuristic, find the destination, then find the shortest path
        Node destination;
        //get the x and z coordinate value
        destination.xCoordinates = destinationPosition.x;
        destination.zCoordinates = destinationPosition.z;

        //We now have the start node and destination so we can start trying to find the shortest path well...not just yet
        startingNodeAndDestinationNode(start, destination);
        //set this bad boy equal to true now
        optimalStartingNode = true;
    }//end if
    else{
        //it is the starting node so lets find the path now and keep on traversing till you find that bad boy
        keepOnFindingthePath();
    }//end else
}

void ShortestPath::startingNodeAndDestinationNode(Node start, Node destination) {
    //Pretty self explanatory, we are initializing the start and destination nodes here

    //findNextNode(x, z, parent)
    startNode = new Node(start.xCoordinates, start.zCoordinates, 0);
    destinationNode = new Node(destination.xCoordinates, destination.zCoordinates, &destination);

    //We are just initializing everything here, start nodes a pointer and we are getting distancefromcurrentnode, etc.
    startNode->distanceFromCurrentNode = 0;
    //This is the manhattan distance (x+z coordinates)
    startNode->heuristicDistance = startNode->currentNodetoCurrentTarget(destinationNode);
    startNode->parent = 0;

    //Push back the start node
    initialList.push_back(startNode);

}

Node* ShortestPath::getNode(){

    //Set it nice and big because the lower the sum the higher priority. The sum will get replaced in the list if it is smaller
    //So we set this nice and big so it will be replaced later
    int optimalSum = 9999999; //set this to infinity*************
    int nodeIndex = 0;
    Node* nextNode = NULL;

    for(int i = 0; i < initialList.size(); i++){
        //If get sum is less than optimal sum then this means that it is the higher priority and we will want to take this
        //replaces optimal sum with the smaller sum and results in the higher priority. Node index gets updated to i
        //no need for else cause we aint gonna do anything if its bigger. Just keep on looping through until you find something
        //smaller
        if(initialList[i]->getSum() < optimalSum){
            optimalSum = initialList[i]->getSum();
            nodeIndex = i;
        }//end if
    }//end for

    if(nodeIndex > 0){
        //lets look at the next node
        nextNode = initialList[nodeIndex];
        //push next node into the visited list
        visitedList.push_back(nextNode);
        //now we wanna erase the thing we were looking at in the initial list cause we dont need it anymore
        initialList.erase(initialList.begin() + nodeIndex);
    }//end if

    return nextNode;
}

void ShortestPath::checkCurrentNode(int cost, int x, int z, Node *parent) {
    //We wanna be looking at the adjacent nodes to the current node. We will look at it like this
    //First condidtion is if we hit a wall then bullocks.
    /*
    if(x = false){
        //ignore it, and we aint gonna go through it
        return;
    }
    */
    Node* newNode = new Node(x, z, parent);
    newNode->distanceFromCurrentNode = cost;
    newNode->heuristicDistance = parent->currentNodetoCurrentTarget(destinationNode);
    int whereWeAtInVisitedList = z * sizeOfMaze + x;

    for(int i = 0; i < visitedList.size(); i++){
        if(whereWeAtInVisitedList == visitedList[i]->whereWeAt){
            //check visited list, if that node already in visited list, just ignore it
            return;
        }//end if
        else if(whereWeAtInVisitedList == initialList[i]->whereWeAt){
            //else if its in the initial list then we gotta look at it
            float newSum = newNode->distanceFromCurrentNode + cost + initialList[i]->heuristicDistance;
            if(initialList[i]->getSum() > newSum){
                //If the new sum is less than the sum we had then we take it cause its better
                initialList[i] -> distanceFromCurrentNode = newNode->distanceFromCurrentNode + cost;
                initialList[i]->parent = newNode;
            }//end nested if
            else{
                //sum is less than what we're looking for so lets just get rid of that
                delete newNode;
                return;
            }//end nested else
        }//end else if
    }//end for
    //push back new node into the initial list
    initialList.push_back(newNode);
}

void ShortestPath::keepOnFindingthePath() {
    //Keep on finding the next node to throw into the path
    Node* thisCell = getNode();
    Node* path;

    if(initialList.empty()){
        //dont need to go through it cause the list is empty....
        return;
    }//end if
    else if(thisCell->whereWeAt == destinationNode->whereWeAt){
        //if this cell has already reached the destination we want to set the parent of this cell equal to
        //the parent of the destination node to the
        destinationNode->parent = thisCell->parent;

        for(path = destinationNode; path != NULL; path = path->parent){
            //youre starting at the destination node here, and if it doesnt equal null keep on looping through
            //this bad boy. Wanna get to the parent

            //Go through the nodes find the shortest path and push it into the next node for the path list.
            //This will give the most optimal path to goal
            nextNodeForPathList.push_back(new Vector((path -> xCoordinates), 0, (path -> zCoordinates)));
        }//end for
        //Bring home the red panties honey, weve found the destination
        optimalDestinationNode = true;
        return;
    }//end else if

    else{
        //Dont bring home the red panties, we haven't found the destination honey. We now check all the adjacent nodes
        // right
        checkCurrentNode(thisCell->distanceFromCurrentNode +1, thisCell->xCoordinates +1, thisCell->zCoordinates, thisCell);
        //left
        checkCurrentNode(thisCell->distanceFromCurrentNode +1, thisCell->xCoordinates -1, thisCell->zCoordinates, thisCell);
        //top
        checkCurrentNode(thisCell->distanceFromCurrentNode +1, thisCell->xCoordinates, thisCell->zCoordinates +1, thisCell);
        //bottom
        checkCurrentNode(thisCell->distanceFromCurrentNode +1, thisCell->xCoordinates, thisCell->zCoordinates -1, thisCell);
        //diagonally up and to the right. cost will be the square root of 2+1 (3)
        checkCurrentNode(thisCell->distanceFromCurrentNode +1.4f, thisCell->xCoordinates +1, thisCell->zCoordinates +1, thisCell);
        //diagonally up and to the left. cost will be the square root of 2+1 (3)
        checkCurrentNode(thisCell->distanceFromCurrentNode +1.4f, thisCell->xCoordinates -1, thisCell->zCoordinates +1, thisCell);
        //diagonally down and to the right. cost will be the square root of 2+1 (3)
        checkCurrentNode(thisCell->distanceFromCurrentNode +1.4f, thisCell->xCoordinates +1, thisCell->zCoordinates -1, thisCell);
        //diagonally down and to the left. cost will be the square root of 2+1 (3)
        checkCurrentNode(thisCell->distanceFromCurrentNode +1.4f, thisCell->xCoordinates -1, thisCell->zCoordinates -1, thisCell);


        for(int i = 0; i < initialList.size(); i++){
            if(thisCell->whereWeAt == initialList[i]->whereWeAt){
                //get rid of it from the initial list
                initialList.erase(initialList.begin() +i);
            }//end if
        }//end for
    }//end else
}//end function

//-----this entire function i have no idea why we need it
//-----i grabbed it online and it didnt really have a description so lets try running the code without it first
//-----on top of that it doesnt make sense
//-----oh and on top of that it doesnt make any sense
//-----yeah on top of that it doesnt make sense

/*
Vector ShortestPath::nextPositionFromList(GameObject whatTheButt){
    //Get the first position from the shortest path from the list
    int listIndex = 1;

    //change this into a for loop, for int i = 0 i<nextNodeforPathList i++
    Vector theNextPosition;
    Vector distanceBetween = theNextPositionforNode - whatTheButt.currentPositionOfObject;

    theNextPosition.x = (nextNodeForPathList[nextNodeForPathList.size() - listIndex])->x;
    theNextPosition.z = (nextNodeForPathList[nextNodeForPathList.size() - listIndex])->z;

    if (listIndex < nextNodeForPathList.size()){
        if(distanceBetween.length() < whatTheButt.radiusofObject){
            //once whatTheButt has touched the first position in the shortest path, you wanna delete it so it goes to the next path
            nextNodeForPathList.erase(nextNodeForPathList.end() - listIndex);
        }//end nested if
    }//end if

    return theNextPosition;
}
*/
