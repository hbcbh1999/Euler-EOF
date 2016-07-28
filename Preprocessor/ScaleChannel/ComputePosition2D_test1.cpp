#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <array>
#include "gridInput.hpp"
#include "gridsmoother.cpp"

std::array<double,2> ComputePosition2D_test1(int i, int j, GridParameter input)
{
	std::array<double,2> point, BottomPoint, TopPoint;
	double k_inverse;
	double LM, HM, H1, delta, k;
	std::array<double,6> beta;
	std::array<int,5> I;
	std::array<double,5> L;	
	int IM, JM;

//     //   ___L[3]________L[4]____
// 	//	|  					    |
// 	//	|				    	H1
// 	//	HM			    __L[2]__|  
// 	//	|			   /
// 	//	|			L[1]
// 	//	|____L[0]____/  

// // Free scale variable
// /**///================================///**/
// /**/	LM = 210;    /**/	IM = 211;    /**/
// /**/	L[0] = 30;    /**/	I[0] = 30;    /**/		
// /**/	L[1] = 60;    /**/	I[1] = 60;    /**/
// /**/	L[3] = 94;    /**/	I[3] = 80;    /**/
// /**/	HM = 60;    /**/	JM = 61;    /**/	
// /**/	delta = M_PI/18;	            /**/
// /**///================================///**/

// 	k = tan(delta);
// 	H1 = HM - L[1] *k;
// 	L[2] = LM - (L[1] + L[0]);
// 	L[4] = LM - L[3];
// 	I[2] = IM - (I[0]+I[1]);
// 	I[4] = IM - (I[3]);

// // Clustering coeff.
// /**///=========================================///**/
// /**/	beta[0] = 1.5;    /**/	  beta[3] = 1.3;   /**/
// /**/	beta[1] = 1.3;    /**/	  beta[4] = 1.5;   /**/		
// /**/	beta[2] = 1.3;    /**/    beta[5] = 1.2;    /**/	
// /**///==========================================///**/

// 	beta = gridsmoother(beta,I,L);
// 	// int x = I[0];
// 	// L[0] - L[0] * (1.0-beta[0]*( pow(((beta[0]+1.0)/(beta[0]-1.0)),(1.0-((I[0]-x))/(I[0]-1.0))) -1.0)/( pow(((beta[0]+1.0)/(beta[0]-1.0)),(1.0-((I[0]-x))/(I[0]-1.0))) +1.0));


// 	if (i <= I[0])
// 	{
// 		BottomPoint[0] = L[0] - L[0] * (1.0-beta[0]*( pow(((beta[0]+1.0)/(beta[0]-1.0)),(1.0-((I[0]-i))/(I[0]-1.0))) -1.0)/( pow(((beta[0]+1.0)/(beta[0]-1.0)),(1.0-((I[0]-i))/(I[0]-1.0))) +1.0));

// 		TopPoint[0] = L[3] - L[3] * (1.0-beta[3]*( pow(((beta[3]+1.0)/(beta[3]-1.0)),(1.0-((I[3]-i))/(I[3]-1.0))) -1.0)/( pow(((beta[3]+1.0)/(beta[3]-1.0)),(1.0-((I[3]-i))/(I[3]-1.0))) +1.0));

// 		BottomPoint[1] = 0.0;
// 		TopPoint[1] = H1;
// 		k_inverse = (TopPoint[0] - BottomPoint[0])/(TopPoint[1] - BottomPoint[1]);

// 		point[1] = BottomPoint[1] + HM/2.0*(1.0-beta[5]*(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))-1.0)/(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))+1.0));
// 		point[0] = BottomPoint[0] + (point[1]-BottomPoint[1])*k_inverse;

// 		// point[0] = L[0]/I[0] * (i);
// 		// point[0] = L[0]-L[0]*(1.0-beta[0]*( pow(((beta[0]+1.0)/(beta[0]-1.0)),(1.0-((I[0]-i))/(I[0]-1.0))) -1.0)/( pow(((beta[0]+1.0)/(beta[0]-1.0)),(1.0-((I[0]-i))/(I[0]-1.0))) +1.0));
// 		// point[1] = HM/JM * (j-1);
// 		// point[1] = HM/2.0*(1.0-beta[5]*(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))-1.0)/(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))+1.0));
// 	} 

// 	else if (i > I[0] && i <= I[3] /*(I[1] + I[0])*/)
// 	{

// 		BottomPoint[0] = L[0]+L[1]-L[1]/2.0*(1.0-beta[1]*(pow(((beta[1]+1.0)/(beta[1]-1.0)),(1.0-2.0*(((I[1])-(i-I[0])))/I[1]))-1.0)/(pow(((beta[1]+1.0)/(beta[1]-1.0)),(1.0-2.0*(((I[1])-(i-I[0])))/I[1]))+1.0));
// 		TopPoint[0] = L[3]-L[3]*(1.0-beta[3]*( pow(((beta[3]+1.0)/(beta[3]-1.0)),(1.0-((I[3]-i))/(I[3]-1.0))) -1.0)/( pow(((beta[3]+1.0)/(beta[3]-1.0)),(1.0-((I[3]-i))/(I[3]-1.0))) +1.0));

// 		BottomPoint[1] = k * (BottomPoint[0] - L[0]);
// 		TopPoint[1] = H1;
// 		k_inverse = (TopPoint[0] - BottomPoint[0])/(TopPoint[1] - BottomPoint[1]);

// 		point[1] = BottomPoint[1] + (HM - BottomPoint[1])/2.0*(1.0-beta[5]*(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))-1.0)/(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))+1.0));
// 		point[0] = BottomPoint[0] + (point[1]-BottomPoint[1])*k_inverse;
		
// 		// point[0] = L[0] + L[1]/I[1] * (i - I[0]);
// 		// // point[0] = L[0]+L[1]-L[1]/2.0*(1.0-beta[1]*(pow(((beta[1]+1.0)/(beta[1]-1.0)),(1.0-2.0*(((I[1])-(i-I[0])))/I[1]))-1.0)/(pow(((beta[1]+1.0)/(beta[1]-1.0)),(1.0-2.0*(((I[1])-(i-I[0])))/I[1]))+1.0));
// 		// double Hi = HM - k * (point[0] - L[0]);
// 		// // point[1] = HM/JM * (j-1);
// 		// // point[1] = (HM - Hi) + Hi/JM * (j - 1);	
// 		// // point[1] = k * (point[0] - L[0]) + Hi/2.0*(1.0-beta[5]*(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))-1.0)/(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))+1.0));	
// 	}
// 	else if (i > I[3] && i <= (I[0] + I[1]))
// 	{
// 		BottomPoint[0] = L[0]+L[1]-L[1]/2.0*(1.0-beta[1]*(pow(((beta[1]+1.0)/(beta[1]-1.0)),(1.0-2.0*(((I[1])-(i-I[0])))/I[1]))-1.0)/(pow(((beta[1]+1.0)/(beta[1]-1.0)),(1.0-2.0*(((I[1])-(i-I[0])))/I[1]))+1.0));
// 		TopPoint[0] = L[3] + L[4]*(1.0-beta[4]*(pow(((beta[4]+1.0)/(beta[4]-1.0)),(1.0-(double(i-I[3]))/I[4]))-1.0)/(pow(((beta[4]+1.0)/(beta[4]-1.0)),(1.0-(double(i-I[3]))/I[4]))+1.0));

// 		BottomPoint[1] = k * (BottomPoint[0] - L[0]);
// 		TopPoint[1] = H1;
// 		k_inverse = (TopPoint[0] - BottomPoint[0])/(TopPoint[1] - BottomPoint[1]);

// 		point[1] = BottomPoint[1] + (HM - BottomPoint[1])/2.0*(1.0-beta[5]*(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))-1.0)/(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))+1.0));
// 		point[0] = BottomPoint[0] + (point[1]-BottomPoint[1])*k_inverse;

// 		// point[0] = L[0] + L[1] + L[2]/I[2] * (i - I[0] - I[1]);
// 		// // point[1] = HM/JM * (j-1);
// 		// point[1] = (HM - H1) + H1/JM * (j - 1);
// 		// point[0] = L[0] + L[1] + L[2]*(1.0-beta[2]*(pow(((beta[2]+1.0)/(beta[2]-1.0)),(1.0-(double(i-I[0]-I[1]))/I[2]))-1.0)/(pow(((beta[2]+1.0)/(beta[2]-1.0)),(1.0-(double(i-I[0]-I[1]))/I[2]))+1.0));

// 		// point[1] = HM - H1 + H1/2.0*(1.0-beta[5]*(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))-1.0)/(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))+1.0));	
// 	}
// 	else if (i > (I[0] + I[1]))
// 	{
// 		BottomPoint[0] = L[0] + L[1] + L[2]*(1.0-beta[2]*(pow(((beta[2]+1.0)/(beta[2]-1.0)),(1.0-(double(i-I[0]-I[1]))/I[2]))-1.0)/(pow(((beta[2]+1.0)/(beta[2]-1.0)),(1.0-(double(i-I[0]-I[1]))/I[2]))+1.0));
// 		TopPoint[0] = L[3] + L[4]*(1.0-beta[4]*(pow(((beta[4]+1.0)/(beta[4]-1.0)),(1.0-(double(i-I[3]))/I[4]))-1.0)/(pow(((beta[4]+1.0)/(beta[4]-1.0)),(1.0-(double(i-I[3]))/I[4]))+1.0));

// 		BottomPoint[1] = k * L[1];
// 		TopPoint[1] = H1;
// 		k_inverse = (TopPoint[0] - BottomPoint[0])/(TopPoint[1] - BottomPoint[1]);

// 		point[1] = BottomPoint[1] + (HM - BottomPoint[1])/2.0*(1.0-beta[5]*(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))-1.0)/(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))+1.0));
// 		point[0] = BottomPoint[0] + (point[1]-BottomPoint[1])*k_inverse;

// 		// point[0] = L[0] + L[1] + L[2]/I[2] * (i - I[0] - I[1]);
// 		// // point[1] = HM/JM * (j-1);
// 		// point[1] = (HM - H1) + H1/JM * (j - 1);
// 		// point[0] = L[0] + L[1] + L[2]*(1.0-beta[2]*(pow(((beta[2]+1.0)/(beta[2]-1.0)),(1.0-(double(i-I[0]-I[1]))/I[2]))-1.0)/(pow(((beta[2]+1.0)/(beta[2]-1.0)),(1.0-(double(i-I[0]-I[1]))/I[2]))+1.0));

// 		// point[1] = HM - H1 + H1/2.0*(1.0-beta[5]*(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))-1.0)/(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))+1.0));	
// 	}
	

// 	return point;


    //   _________LM_________
	//	|   				 |
	//	|  					 |
	//	|				 	 |
	//	HM			   __L[2]|  
	//	|			  /
	//	|			L[1]
	//	|____L[0]____/  

// Free variable table
/**///================================///**/
/**/	LM = 210;    /**/	IM = 210;    /**/
/**/	L[0] = 30;    /**/	I[0] = 30;    /**/		
/**/	L[1] = 60;    /**/	I[1] = 60;    /**/	
/**/	HM = 60;    /**/	JM = 60;    /**/	
/**/	delta = M_PI/180*10;	            /**/
/**///================================///**/

	k = tan(delta);
	H1 = HM - L[1] *k;
	I[2] = IM - (I[0]+I[1]);
	I[3] = IM - (I[0]);

	// FLOAT beta[0] = 1.2, beta[5] = 1.2;

	// 	BottomPoint[0] = LM/IM * (i-1);

	// 	TopPoint[0] = LM/IM * (i-1);/*LM - LM * (1.0-beta[0]*( pow(((beta[0]+1.0)/(beta[0]-1.0)),(1.0-((IM-i))/(IM-1.0))) -1.0)/( pow(((beta[0]+1.0)/(beta[0]-1.0)),(1.0-((IM-i))/(IM-1.0))) +1.0));*/
	// 	BottomPoint[1] = 0.0;
	// 	TopPoint[1] = H1;
	// 	k_inverse = (TopPoint[0] - BottomPoint[0])/(TopPoint[1] - BottomPoint[1]);

	// 	point[1] = BottomPoint[1] + HM/2.0*(1.0-beta[5]*(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))-1.0)/(pow(((beta[5]+1.0)/(beta[5]-1.0)),(1.0-(j-1.0)/(JM/2)))+1.0));
	// 	point[0] = BottomPoint[0] + (point[1]-BottomPoint[1])*k_inverse;


	if (i <= I[0])
	{
		point[0] = L[0]/I[0] * (i-1);
		point[1] = HM/JM * (j-1);
	}
	// else if (i>	I[0])
	// {
	// 	point[0] = L[0] + (LM-L[0])/(IM-I[0]) * ((i-I[0])-1);
	// 	point[1] = HM/JM * (j-1);
	// } 
	else if (i > I[0] && i <= (I[1] + I[0]))
	{

		point[0] = LM/IM * (i-1);
		double Hi = HM - k * (point[0] - L[0]);
		point[1] = (HM - Hi) + Hi/JM * (j - 1);		
	}
	else
	{
		point[0] = LM/IM * (i-1);
		point[1] = (HM - H1) + H1/JM * (j - 1);
	}
	

	return point;
}