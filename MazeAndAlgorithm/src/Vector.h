/*
 * Vector.h
 *
 *  Created on: Nov 21, 2016
 *      Author: Sasha
 */

#ifndef SRC_VECTOR_H_
#define SRC_VECTOR_H_

class Vector{
public:
    int x;
    int y;
    int z;
    float length();
    Vector();
	Vector(int x, int y, int z);
private:
};

#endif /* SRC_VECTOR_H_ */
