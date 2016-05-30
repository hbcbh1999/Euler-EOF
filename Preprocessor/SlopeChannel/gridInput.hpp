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
		51/*JM*/,
		131/*IM*/,
		21/*I1*/,
		51/*I2*/,
		59/*I3*/,
		21/*I4 = I1*/,
		110/*I5*/, 
		
		30/*L1*/,
		60/*L2*/,
		120/*L3*/,
		30/*L4*/,
		180/*L5*/,
		60/*h1*/,
		M_PI/18/*delta*/,

		// 1.05/*beta1*/,
		// 1.15/*beta2*/,
		// 1.1/*beta3*/,
		// 1.5/*beta4*/,
		// 2/*beta5*/,
		// 1.5/*beta6*/

		1.45/*beta1*/,
		2/*beta2*/,
		1.2/*beta3*/,
		1.45/*beta4*/,
		1.5/*beta5*/,
		2/*beta6*/
	};