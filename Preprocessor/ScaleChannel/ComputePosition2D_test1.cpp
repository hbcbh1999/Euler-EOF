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
	double sizeY = 75;

	int Xnum = 120;
	int Ynum = 75;

	point[0] = sizeX/Xnum * i;
	point[1] = sizeY/Ynum * j;

	return point;
}