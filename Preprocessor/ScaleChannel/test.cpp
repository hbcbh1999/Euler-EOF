#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <array>
#include "gridsmoother.cpp"

int main(int argc, char const *argv[])
{
	double LM, HM, H1, delta, k;
	std::array<double,6> beta;
	std::array<int,5> I;
	std::array<double,5> L;	
	int IM, JM;

    //   ___L[3]________L[4]____
	//	|  					    |
	//	|				    	H1
	//	HM			    __L[2]__|  
	//	|			   /
	//	|			L[1]
	//	|____L[0]____/  

// Free scale variable
/**///================================///**/
/**/	LM = 210;    /**/	IM = 106;    /**/
/**/	L[0] = 30;    /**/	I[0] = 15;    /**/		
/**/	L[1] = 60;    /**/	I[1] = 30;    /**/
/**/	L[3] = 94;    /**/	I[3] = 40;    /**/
/**/	HM = 60;    /**/	JM = 31;    /**/	
/**/	delta = M_PI/18;	            /**/
/**///================================///**/

	k = tan(delta);
	H1 = HM - L[1] *k;
	L[2] = LM - (L[1] + L[0]);
	L[4] = LM - L[3];
	I[2] = IM - (I[0]+I[1]);
	I[4] = IM - (I[3]);

// Clustering coeff.
/**///=========================================///**/
/**/	beta[0] = 1.5;    /**/	  beta[3] = 1.4;   /**/
/**/	beta[1] = 1.8;    /**/	  beta[4] = 1.8;   /**/		
/**/	beta[2] = 1.6;    /**/    beta[5] = 1.5;    /**/	
/**///==========================================///**/

	beta = gridsmoother(beta,I,L);
	std::cout << beta[1] << " " << beta[2]<< " " <<  beta[3] << " " << beta[4] << " " ;		
}