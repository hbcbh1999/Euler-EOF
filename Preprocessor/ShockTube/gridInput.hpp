#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

struct GridParameter
{
	// Node number
	int JM; int IM; int I1; int I2; int I3; int I4; int I5;
	// Geometry scale
	double L1;double L2; double L3; double L4; double L5; double H1; double delta;
	// Clustering parameter
	double beta1;double beta2;double beta3;double beta4;double beta5;double beta6;	
};

GridParameter input1=
	{
		151/*JM*/,241,31,91,119,76,165, 
		0.1,0.2,0.4,0.28,0.42,0.2,M_PI/18,
		1.02,1.1,1.05,1.02,1.05,1.1
	};