#include "Vector.h"
#include <math.h>

float Vector::length(){
	return sqrt((x*x) + (y*y) + (z*z));
}
Vector::Vector() : x(0), y(0), z(0) {}
Vector::Vector(int x, int y, int z) : x(x), y(y), z(z) {}
