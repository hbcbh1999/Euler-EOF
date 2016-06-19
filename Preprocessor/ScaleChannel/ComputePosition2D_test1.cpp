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
	double LM, L1, L2, L3, HM, H1, delta, k;
	double beta1, beta2, beta3, beta4, beta5;
	int IM, JM, I1, I2, I3, I4;

    //   ___________________
	//	|  					|
	//	|					H1
	//	HM			  __L3__|  
	//	|			 /
	//	|			L2
	//	|____L1____/  

// Free scale variable
/**///================================///**/
/**/	LM = 210;    /**/	IM = 210;    /**/
/**/	L1 = 30;    /**/	I1 = 30;    /**/		
/**/	L2 = 60;    /**/	I2 = 60;    /**/	
/**/	HM = 60;    /**/	JM = 60;    /**/	
/**/	delta = M_PI/18;	            /**/
/**///================================///**/

// Clustering coeff.
/**///=========================================///**/
/**/	beta1 = 1.5;    /**/	  beta4 = 1.5;   /**/
/**/	beta2 = 1.4;    /**/	  beta5 = 1.5;   /**/		
/**/	beta3 = 1.5;    /**/   			  		  /**/	
/**///==========================================///**/


	k = tan(delta);
	H1 = HM - L2 *k;
	L3 = LM - (L2 + L1);
	I3 = IM - (I1+I2);
	I4 = IM - (I1);

	if (i <= I1)
	{
		point[0] = L1/I1 * (i);
		// point[0] = L1-L1*(1.0-beta1*( pow(((beta1+1.0)/(beta1-1.0)),(1.0-((I1-i))/(I1-1.0))) -1.0)/( pow(((beta1+1.0)/(beta1-1.0)),(1.0-((I1-i))/(I1-1.0))) +1.0));
		point[1] = HM/JM * (j-1);
		// point[1] = HM/2.0*(1.0-beta5*(pow(((beta5+1.0)/(beta5-1.0)),(1.0-(j-1.0)/(JM/2)))-1.0)/(pow(((beta5+1.0)/(beta5-1.0)),(1.0-(j-1.0)/(JM/2)))+1.0));
	} 
	else if (i > I1 && i <= (I2 + I1))
	{
		point[0] = L1 + L2/I2 * (i - I1);
		// point[0] = L1+L2-L2/2.0*(1.0-beta2*(pow(((beta2+1.0)/(beta2-1.0)),(1.0-2.0*(((I2)-(i-I1)))/I2))-1.0)/(pow(((beta2+1.0)/(beta2-1.0)),(1.0-2.0*(((I2)-(i-I1)))/I2))+1.0));
		double Hi = HM - k * (point[0] - L1);
		// point[1] = HM/JM * (j-1);
		point[1] = (HM - Hi) + Hi/JM * (j - 1);	
		// point[1] = k * (point[0] - L1) + Hi/2.0*(1.0-beta5*(pow(((beta5+1.0)/(beta5-1.0)),(1.0-(j-1.0)/(JM/2)))-1.0)/(pow(((beta5+1.0)/(beta5-1.0)),(1.0-(j-1.0)/(JM/2)))+1.0));	
	}
	else if (i > (I1+I2))
	{
		point[0] = L1 + L2 + L3/I3 * (i - I1 - I2);
		// point[1] = HM/JM * (j-1);
		point[1] = (HM - H1) + H1/JM * (j - 1);
		// point[0] = L1 + L2 + L3*(1.0-beta3*(pow(((beta3+1.0)/(beta3-1.0)),(1.0-(double(i-I1-I2))/I3))-1.0)/(pow(((beta3+1.0)/(beta3-1.0)),(1.0-(double(i-I1-I2))/I3))+1.0));

		// point[1] = HM - H1 + H1/2.0*(1.0-beta5*(pow(((beta5+1.0)/(beta5-1.0)),(1.0-(j-1.0)/(JM/2)))-1.0)/(pow(((beta5+1.0)/(beta5-1.0)),(1.0-(j-1.0)/(JM/2)))+1.0));	
	}
	

	return point;


//	std::array<double,2> point, BottomPoint, TopPoint;
// 	double k_inverse;
// 	double LM, L1, L2, HM, H1, delta, k;
// 	int IM, JM, I1, I2, I3, I4;

//     //   _________LM________
// 	//	|   				|
// 	//	|  					|
// 	//	|					|
// 	//	HM			  __L3__|  
// 	//	|			 /
// 	//	|			L2
// 	//	|____L1____/  

// // Free variable table
// /**///================================///**/
// /**/	LM = 60;    /**/	IM = 60;    /**/
// /**/	L1 = 20;    /**/	I1 = 20;    /**/		
// /**/	L2 = 20;    /**/	I2 = 20;    /**/	
// /**/	HM = 20;    /**/	JM = 20;    /**/	
// /**/	delta = M_PI/18;	            /**/
// /**///================================///**/

// 	k = tan(delta);
// 	H1 = HM - L2 *k;
// 	I3 = IM - (I1+I2);
// 	I4 = IM - (I1);

// 	if (i <= I1)
// 	{
// 		point[0] = LM/IM * (i-1);
// 		point[1] = HM/JM * (j-1);
// 	} 
// 	else if (i > I1 && i <= (I2 + I1))
// 	{

// 		point[0] = LM/IM * (i-1);
// 		double Hi = HM - k * (point[0] - L1);
// 		point[1] = (HM - Hi) + Hi/JM * (j - 1);		
// 	}
// 	else
// 	{
// 		point[0] = LM/IM * (i-1);
// 		point[1] = (HM - H1) + H1/JM * (j - 1);
// 	}
	

// 	return point;
}