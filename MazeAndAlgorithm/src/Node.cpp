#pragma once

#include "Node.h"
#include <math.h>
#include <stdlib.h>

node::node(int xp, int yp, int d, int p)
	{
		xPos = xp; yPos = yp; distanceTravelled = d; priority = p;
	}

int node::getxPos() const { return xPos; }
int node::getyPos() const { return yPos; }
int node::getDistanceTravelled() const { return distanceTravelled; }
int node::getPriority() const { return priority; }

void node::updatePriority(const int & xDest, const int & yDest)
{
	priority = distanceTravelled + estimate(xDest, yDest); //A*
}

void node::updateDistanceTravelled(const int & i) // i: direction
{
	distanceTravelled += 1;
}

// Estimation function for the remaining distance to the goal.
const int & node::estimate(const int & xDest, const int & yDest) const
{
	static int xd, yd, d;
	xd = xDest - xPos;
	yd = yDest - yPos;

	// Euclidian Distance
	//d = static_cast<int>(sqrt(xd*xd + yd*yd));

	// Manhattan distance
	d=abs(xd)+abs(yd);

	// Chebyshev distance
	//d=max(abs(xd), abs(yd));

	return(d);
}

bool operator<(const node & a, const node & b)
{
	return a.getPriority() > b.getPriority();
}
