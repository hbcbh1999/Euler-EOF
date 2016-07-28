#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <array>

	inline double right(double L, double beta, int I, int i)
	{
   		return L - L * (1.0-beta*( pow(((beta+1.0)/(beta-1.0)),(1.0-((I-i))/(I-1.0))) -1.0)/( pow(((beta+1.0)/(beta-1.0)),(1.0-((I-i))/(I-1.0))) +1.0));
	}

	inline double twoSide(double L, double beta, int I, int i)
	{
   		return L - L/2.0*(1.0-beta*(pow(((beta+1.0)/(beta-1.0)),(1.0-2.0*((I-i))/I))-1.0)/(pow(((beta+1.0)/(beta-1.0)),(1.0-2.0*((I-i))/I))+1.0));
	}

	inline double left(double L, double beta, int I, int i)
	{
   		return L*(1.0-beta*(pow(((beta+1.0)/(beta-1.0)),(1.0-(double(i))/I))-1.0)/(pow(((beta+1.0)/(beta-1.0)),(1.0-(double(i))/I))+1.0));
	}

std::array<double,6> gridsmoother(std::array<double,6> beta, std::array<int,5> I,std::array<double,5> L)
{

	double delta1 = right(L[0],beta[0],I[0],I[0]) - right(L[0],beta[0],I[0],I[0]-1);
	double delta4 = right(L[3],beta[3],I[3],I[3]) - right(L[3],beta[3],I[3],I[3]-1);
	// Inital guess
	double beta_min = 1.01;
	double beta_max = 2;
	double delta_n, beta_n;
	double resTor = 1e-8;
	double res = 1;

	while (fabs(res) > resTor)
	{
		beta_n = 1 + 0.5 * ((beta_min-1) + (beta_max-1));
		delta_n = twoSide(L[1],beta_n,I[1],1) ;
		res = delta_n - delta1; 
		if (res > 0){
			beta_max = beta_n;
		}else{
			beta_min = beta_n;
		}
	}
	beta[1] = beta_n;

	// Inital guess
	beta_min = 1.01;
	beta_max = 2;
	res = 1;
	while(fabs(res) > resTor)
	{
		beta_n = 1 + 0.5 * ((beta_min-1) + (beta_max-1));
		delta_n = left(L[2],beta_n,I[2],1);
		res = delta_n - delta1; 
		if (res > 0){
			beta_max = beta_n;
		}else{
			beta_min = beta_n;
		}
	}
	beta[2] = beta_n;

	// Inital guess
	beta_min = 1.01;
	beta_max = 2;
	res = 1;
	while(fabs(res) > resTor)
	{
		beta_n = 1 + 0.5 * ((beta_min-1) + (beta_max-1));
		delta_n = left(L[4],beta_n,I[4],1);
		res = delta_n - delta4; 
		if (res > 0){
			beta_max = beta_n;
		}else{
			beta_min = beta_n;
		}
	}
	beta[4] = beta_n;
	// std::cout << delta4 << " " << delta_n << "\n";
	return beta;
}
