#pragma once

const int dir = 4; // number of possible directions to go at any position
// how the target moves through map based on direction
static int dx[dir]={1, 0, -1, 0};
static int dy[dir]={0, 1, 0, -1};

class node
{
public:
	node(int xp, int yp, int d, int p);
	int getxPos() const;
	int getyPos() const;
	int getDistanceTravelled() const;
	int getPriority() const;

	void updatePriority(const int & xDest, const int & yDest);
	void updateDistanceTravelled(const int & i); // i: direction

	// Estimation function for the remaining distance to the goal.
	const int & estimate(const int & xDest, const int & yDest) const;
private:
	// current position
	int xPos;
	int yPos;
	// total distance already travelled to reach the node
	int distanceTravelled;
	// priority=distanceTravelled+remaining distance estimate
	int priority;  // smaller: higher priority
};

// Determine priority (in the priority queue)
bool operator<(const node & a, const node & b);
