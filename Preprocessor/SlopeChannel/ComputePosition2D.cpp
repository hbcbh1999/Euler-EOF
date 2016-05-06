#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <array>
#include "gridInput.hpp"

std::array<double,2> ComputePosition2D(int i, int j, GridParameter input)
{
	std::array<double,2> point, BottomPoint, TopPoint;
	double k_inverse;

	if ( i >= 1 && i <= input.I1)
	{	
		if (i != input.I1)
			{
				BottomPoint[0] = input.L1-input.L1*(1.0-input.beta1*( pow(((input.beta1+1.0)/(input.beta1-1.0)),(1.0-(input.I1-i+1.0)/input.I1)) -1.0)/( pow(((input.beta1+1.0)/(input.beta1-1.0)),(1.0-(input.I1-i+1.0)/input.I1)) + 1.0));
			}
		else
			{
				BottomPoint[0] = input.L1;
			}

		BottomPoint[1] = 0.0;
		TopPoint[0] = input.L4-input.L4*(1.0-input.beta4*( pow(((input.beta4+1.0)/(input.beta4-1.0)),(1.0-(input.I4-i+1.0)/input.I4)) -1.0)/( pow(((input.beta4+1.0)/(input.beta4-1.0)),(1.0-(input.I4-i+1.0)/input.I4)) +1.0));
		TopPoint[1] = input.H1;
		k_inverse = (TopPoint[0] - BottomPoint[0])/(TopPoint[1] - BottomPoint[1]);

		if (j == 1)
		{
			point = BottomPoint;
		}	
		else if (j > 1 && j < input.JM)
		{
			point[1] = input.H1/2.0*(1.0-input.beta6*(pow(((input.beta6+1.0)/(input.beta6-1.0)),(1.0-(j-1.0)/(input.JM/2)))-1.0)/(pow(((input.beta6+1.0)/(input.beta6-1.0)),(1.0-(j-1.0)/(input.JM/2)))+1.0));
			point[0] = BottomPoint[0] + (point[1]-BottomPoint[1])*k_inverse;
		}
		else
		{ 
			point = TopPoint;	
		}

	}


	else if ( i >= input.I1 && i <= input.I4)
	{
		if (i != input.I1)
		{
			BottomPoint[0] = input.L1+input.L2/2.0*(1.0-input.beta2*(pow(((input.beta2+1.0)/(input.beta2-1.0)),(1.0-(2.0*(i-input.I1))/input.I2))-1.0)/(pow(((input.beta2+1.0)/(input.beta2-1.0)),(1.0-(2.0*(i-input.I1))/input.I2))+1.0));
		}
		else
		{
			BottomPoint[0] = input.L1;
		}

		if (i != input.I1)
		{
			TopPoint[0] = input.L4-input.L4*(1.0-input.beta4*(pow(((input.beta4+1.0)/(input.beta4-1.0)),(1.0-(input.I4-i+1.0)/input.I4))-1.0)/(pow(((input.beta4+1.0)/(input.beta4-1.0)),(1.0-(input.I4-i+1.0)/input.I4))+1.0));
		}
		else
		{
			TopPoint[0] = input.L4;
		}

		BottomPoint[1] = tan(input.delta)*(BottomPoint[0]-input.L1);
		TopPoint[1] = input.H1;
		k_inverse = (TopPoint[0] - BottomPoint[0])/(TopPoint[1]-BottomPoint[1]);
		
		if (j == 1)
		{
			point = BottomPoint;
		}	
		else if (j > 1 && j < input.JM)
		{
			point[1] = BottomPoint[1]+(TopPoint[1]-BottomPoint[1])/2.0*(1.0-input.beta6*(pow(((input.beta6+1.0)/(input.beta6-1.0)),(1.0-(j-1.0)/(input.JM/2)))-1.0)/(pow(((input.beta6+1.0)/(input.beta6-1.0)),(1.0-(j-1.0)/(input.JM/2)))+1.0));
			point[0] = BottomPoint[0] + (point[1]-BottomPoint[1])*k_inverse;
		}
		else if (j == input.JM)
		{ 
			point = TopPoint;	
		}
	}
	else if ( i >= input.I4 && i <= input.IM)
	{
		if (i != input.I4)
		{
			TopPoint[0] = input.L4+input.L5*(1.0-input.beta5*(pow(((input.beta5+1.0)/(input.beta5-1.0)),(1.0-(double(i-input.I4))/input.I5))-1.0)/(pow(((input.beta5+1.0)/(input.beta5-1.0)),(1.0-(double(i-input.I4))/input.I5))+1.0));
		}
		else
		{
			TopPoint[0] = input.L4;
		}
		TopPoint[1] = input.H1;

		if (i <= (input.I1+input.I2))
    	{
    		BottomPoint[0] = input.L1+input.L2-input.L2/2.0*(1.0-input.beta2*(pow(((input.beta2+1.0)/(input.beta2-1.0)),(1.0-2.0*(((input.I2)-(i-input.I1)))/input.I2))-1.0)/(pow(((input.beta2+1.0)/(input.beta2-1.0)),(1.0-2.0*(((input.I2)-(i-input.I1)))/input.I2))+1.0));
    		BottomPoint[1] = tan(input.delta)*(BottomPoint[0]-input.L1);
    	}
		else if (i > (input.I1+input.I2))
    	{
    		BottomPoint[0] = input.L1+input.L2+input.L3*(1.0-input.beta3*(pow(((input.beta3+1.0)/(input.beta3-1.0)),(1.0-(double(i-input.I1-input.I2))/input.I3))-1.0)/(pow(((input.beta3+1.0)/(input.beta3-1.0)),(1.0-(double(i-input.I1-input.I2))/input.I3))+1.0));
    		BottomPoint[1] = tan(input.delta)*input.L2;
    	}

		k_inverse = (TopPoint[0] - BottomPoint[0])/(TopPoint[1]-BottomPoint[1]);

		if (j == 1)
		{
    		point = BottomPoint;	
		}
		else if (j>1 && j< input.JM)
		{
     		point[1] = BottomPoint[1]+(TopPoint[1]-BottomPoint[1])/2.0*(1.0-input.beta6*(pow(((input.beta6+1.0)/(input.beta6-1.0)),(1.0-(j-1.0)/ (input.JM/2)))-1.0)/(pow(((input.beta6+1.0)/(input.beta6-1.0)),(1.0-(j-1.0)/ (input.JM/2)))+1.0));
    		point[0] = BottomPoint[0] + (point[1]-BottomPoint[1])*k_inverse;
		}
		else if (j == input.JM)
		{
    		point = TopPoint;
    	}

	}

	else
	{

	}

	return point;
}