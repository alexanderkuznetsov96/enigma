#pragma once

const int dir = 8; // number of possible directions to go at any position
				   // if dir==4
				   //static int dx[dir]={1, 0, -1, 0};
				   //static int dy[dir]={0, 1, 0, -1};
				   // if dir==8
static int dx[dir] = { 1, 1, 0, -1, -1, -1, 0, 1 };
static int dy[dir] = { 0, 1, 1, 1, 0, -1, -1, -1 };

class node
{
public:
	node(int xp, int yp, int d, int p);
	int getxPos() const;
	int getyPos() const;
	int getLevel() const;
	int getPriority() const;

	void updatePriority(const int & xDest, const int & yDest);
		// give better priority to going straight instead of diagonally
	void nextLevel(const int & i); // i: direction

	// Estimation function for the remaining distance to the goal.
	const int & estimate(const int & xDest, const int & yDest) const;
private:
	// current position
	int xPos;
	int yPos;
	// total distance already travelled to reach the node
	int level;
	// priority=level+remaining distance estimate
	int priority;  // smaller: higher priority
};

// Determine priority (in the priority queue)
bool operator<(const node & a, const node & b);
