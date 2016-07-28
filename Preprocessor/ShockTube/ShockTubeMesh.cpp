#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <array>
#include "gridInput.hpp"

std::array<double,2> ShockTubeMesh(int i, int j, GridParameter input)
{
	std::array<double,2> point, BottomPoint, TopPoint;
	double k_inverse;

	double sizeX = 100;
	double sizeY = 10;

	int Xnum = 400;
	int Ynum = 5;

	point[0] = sizeX/Xnum * (i-1);
	point[1] = sizeY/Ynum * (j-1);
	
	return point;
}