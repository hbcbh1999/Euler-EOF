#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <array>
#include "gridInput.hpp"

std::array<double,2> ComputePosition2D_test1(int i, int j, GridParameter input)
{
	std::array<double,2> point, BottomPoint, TopPoint;
	double k_inverse;

	double sizeX = 120;
	double sizeY1 = 75;
	double sizeY2 = 25;

	int Xnum = 120;
	int Ynum = 75;

	point[0] = sizeX/Xnum * (i-1);
	point[1] = point[0] * ((sizeY1-sizeY2)/sizeX) + ( sizeY1 - point[0] * ((sizeY1-sizeY2)/sizeX)  )/Ynum * (j-1);
	

	return point;
}