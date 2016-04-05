#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include "RoeSolver.cpp"
int main(int argc, char const *argv[])
{
	/* code */
	int dim = 2;
	float gamma = 1.4;
	float inputL[4] = {1.0, 0.75, 0.0, 1.0};
	float inputR[4] = {1.0, 0.75, 0.0, 1.0};


	std::vector<float> WL, WR;
	for (int i = 0; i<4; i++)
	{
		WL.push_back(inputL[i]);
		WR.push_back(inputR[i]);
	}
	
	// std::vector<float> F_mid;
	std::vector<float>::iterator It;
	/*F_mid = */RoeSolver(WL,WR,dim,gamma);

	// for( It = F_mid.begin();It !=F_mid.end();It ++)
	// {
	// 	std::cout<<*It<<std::endl;
	// }

	return 0;
}