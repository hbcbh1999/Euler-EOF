#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

struct GridPoint2D
{
	double x;
	double y;
};
struct parameter
{
	// Node number
	int JM; int IM; int I1; int I2; int I3; int I4; int I5;
	// Geometry scale
	double L1;double L2; double L3; double L4; double L5; double H1; double delta;
	// Clustering parameter
	double beta1;double beta2;double beta3;double beta4;double beta5;double beta6;	
};