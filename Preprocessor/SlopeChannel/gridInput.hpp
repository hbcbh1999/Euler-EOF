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
		151/*JM*/,
		241/*IM*/,
		21/*I1*/,
		91/*I2*/,
		129/*I3*/,
		61/*I4*/,
		180/*I5*/, 
		
		0.1/*L1*/,
		0.2/*L2*/,
		0.4/*L3*/,
		0.28/*L4*/,
		0.42/*L5*/,
		0.2/*h1*/,
		M_PI/18/*delta*/,

		1.04/*beta1*/,
		1.8/*beta2*/,
		1.3/*beta3*/,
		1.15/*beta4*/,
		1.3/*beta5*/,
		1.5/*beta6*/
	};