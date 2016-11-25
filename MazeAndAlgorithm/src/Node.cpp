#pragma once

#include "Node.h"
#include <math.h>

node::node(int xp, int yp, int d, int p)
	{
		xPos = xp; yPos = yp; level = d; priority = p;
	}

int node::getxPos() const { return xPos; }
int node::getyPos() const { return yPos; }
int node::getLevel() const { return level; }
int node::getPriority() const { return priority; }

void node::updatePriority(const int & xDest, const int & yDest)
{
	priority = level + estimate(xDest, yDest) * 10; //A*
}

// Estimation function for the remaining distance to the goal.
const int & node::estimate(const int & xDest, const int & yDest) const
{
	static int xd, yd, d;
	xd = xDest - xPos;
	yd = yDest - yPos;

	// Euclidian Distance
	d = static_cast<int>(sqrt(xd*xd + yd*yd));

	// Manhattan distance
	//d=abs(xd)+abs(yd);

	// Chebyshev distance
	//d=max(abs(xd), abs(yd));

	return(d);
}

bool operator<(const node & a, const node & b)
{
	return a.getPriority() > b.getPriority();
}