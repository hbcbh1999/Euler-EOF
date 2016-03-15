#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include "ComputePosition2D.cpp"

int main(int argc, char const *argv[])
{
	std::ofstream vtkFile;
	std::string fileName = "Slope_channel_grid.vtk";
	std::stringstream pointData,cellData,cellType;
	int cellRefNum = 0;
/*------------------ TEST MANUAL INPUT----------------------*/
	// node number

	parameter input1=
	{
		151/*JM*/,241,31,91,119,76,165, 
		0.1,0.2,0.4,0.28,0.42,0.2,M_PI/18,
		1.01,1.05,1.05,1.05,1.05,1.05
	};

/*-------------------------------------------------------*/
	// cellwise loop
	for( int j = 1; j < input1.JM; j++ )
	{
		for ( int i = 1; i < input1.IM; i++ )
		{
			// store cell indices in stringstream
			cellData << 4 << " ";
			for (int ii = 0; ii<4; ii++)
			{
				cellData << cellRefNum + ii << " "; 
			}
			cellData << "\n";
			cellRefNum = cellRefNum + 4;
			// store cell type
			cellType << 9 << "\n";
			// Store grid point	
			GridPoint2D point0 = ComputePosition2D(i,j,input1);
			GridPoint2D point1 = ComputePosition2D(i+1,j,input1);
			GridPoint2D point2 = ComputePosition2D(i+1,j+1,input1);
			GridPoint2D point3 = ComputePosition2D(i,j+1,input1);
			pointData << point0.x << " " << point0.y << " " << 0 << "\n";
			pointData << point1.x << " " << point1.y << " " << 0 << "\n";
			pointData << point2.x << " " << point2.y << " " << 0 << "\n";
			pointData << point3.x << " " << point3.y << " " << 0 << "\n";
		}
	}
 
	// Write to the vtk file
	vtkFile.open(fileName.c_str());
	// Vtk Header
	vtkFile << "# vtk DataFile Version 3.1" << "\n";
	vtkFile << "This is the Output of the flow field for paraview" << "\n";
	vtkFile << "ASCII" << "\n" << "DATASET UNSTRUCTURED_GRID"<< "\n" << "\n";

	// Write cell data;
	vtkFile << "CELLS " << (input1.IM - 1)*(input1.JM - 1) << " " << 5* (input1.IM - 1)*(input1.JM - 1) << "\n";
	vtkFile << cellData.str()<< "\n";
	// Write cell type;
 	vtkFile << "CELL_TYPES " << (input1.IM - 1)*(input1.JM - 1) << "\n";
	vtkFile << cellType.str()<< "\n";
	// Write cell point:
	vtkFile << "POINTS " << 4*(input1.IM - 1)*(input1.JM - 1) << " " << "FLOAT" << "\n";
		vtkFile << pointData.str()<< "\n";
	vtkFile.close();

	return 0;
}

// GridPoint2D ComputePosition2D(int i, int j, parameter input)
// {
// 	GridPoint2D point, BottomPoint, TopPoint;
// 	double k_inverse;

// 	if ( i > 0 && i < input.I1)
// 	{
// 		BottomPoint.x = input.L1-input.L1*(1.0-input.beta1*( pow(((input.beta1+1.0)/(input.beta1-1.0)),(1.0-(input.I1-i+1.0)/input.I1)) -1.0)/( pow(((input.beta1+1.0)/(input.beta1-1.0)),(1.0-(input.I1-i+1.0)/input.I1)) + 1.0));
// 		BottomPoint.y = 0.0;
// 		TopPoint.x = input.L4-input.L4*(1.0-input.beta4*( pow(((input.beta4+1.0)/(input.beta4-1.0)),(1.0-(input.I4-i+1.0)/input.I4)) -1.0)/( pow(((input.beta4+1.0)/(input.beta4-1.0)),(1.0-(input.I4-i+1.0)/input.I4)) +1.0));
// 		TopPoint.y = input.H1;
// 		k_inverse = (TopPoint.x - BottomPoint.x)/(TopPoint.y - BottomPoint.y);

// 		if (j == 1)
// 		{
// 			point = BottomPoint;
// 		}	
// 		else if (j > 1 && j < input.JM)
// 		{
// 			point.y = input.H1/2.0*(1.0-input.beta6*(pow(((input.beta6+1.0)/(input.beta6-1.0)),(1.0-(j-1.0)/(input.JM/2)))-1.0)/(pow(((input.beta6+1.0)/(input.beta6-1.0)),(1.0-(j-1.0)/(input.JM/2)))+1.0));
// 			point.x = BottomPoint.x + (point.y-BottomPoint.y)*k_inverse;
// 		}
// 		else
// 		{ 
// 			point = TopPoint;	
// 		}

// 	}

// 	else if ( i >= input.I1 && i < input.I4)
// 	{
// 		BottomPoint.x = input.L1+input.L2/2.0*(1.0-input.beta2*(pow(((input.beta2+1.0)/(input.beta2-1.0)),(1.0-(2.0*(i-input.I1))/input.I2))-1.0)/(pow(((input.beta2+1.0)/(input.beta2-1.0)),(1.0-(2.0*(i-input.I1))/input.I2))+1.0));
// 		TopPoint.x = input.L4-input.L4*(1.0-input.beta4*(pow(((input.beta4+1.0)/(input.beta4-1.0)),(1.0-(input.I4-i+1.0)/input.I4))-1.0)/(pow(((input.beta4+1.0)/(input.beta4-1.0)),(1.0-(input.I4-i+1.0)/input.I4))+1.0));
// 		BottomPoint.y = tan(input.delta)*(BottomPoint.x-input.L1);
// 		TopPoint.y = input.H1;
// 		k_inverse = (TopPoint.x - BottomPoint.x)/(TopPoint.y-BottomPoint.y);
		
// 		if (j == 1)
// 		{
// 			point = BottomPoint;
// 		}	
// 		else if (j > 1 && j < input.JM)
// 		{
// 			point.y = BottomPoint.y+(TopPoint.y-BottomPoint.y)/2.0*(1.0-input.beta6*(pow(((input.beta6+1.0)/(input.beta6-1.0)),(1.0-(j-1.0)/(input.JM/2)))-1.0)/(pow(((input.beta6+1.0)/(input.beta6-1.0)),(1.0-(j-1.0)/(input.JM/2)))+1.0));
// 			point.x = BottomPoint.x + (point.y-BottomPoint.y)*k_inverse;
// 		}
// 		else if (j == input.JM)
// 		{ 
// 			point = TopPoint;	
// 		}


// 	}
// 	else if ( i >= input.I4 && i < input.IM)
// 	{
// 		TopPoint.x = input.L4+input.L5*(1.0-input.beta5*(pow(((input.beta5+1.0)/(input.beta5-1.0)),(1.0-(double(i-input.I4))/input.I5))-1.0)/(pow(((input.beta5+1.0)/(input.beta5-1.0)),(1.0-(double(i-input.I4))/input.I5))+1.0));
// 		TopPoint.y = input.H1;

// 		if (i <= (input.I1+input.I2))
//     	{
//     		BottomPoint.x = input.L1+input.L2-input.L2/2.0*(1.0-input.beta2*(pow(((input.beta2+1.0)/(input.beta2-1.0)),(1.0-2.0*(((input.I2/2)-(i-input.I1- (input.I2/2))))/input.I2))-1.0)/(pow(((input.beta2+1.0)/(input.beta2-1.0)),(1.0-2.0*(((input.I2/2)-(i-input.I1- (input.I2/2))))/input.I2))+1.0));
//     		BottomPoint.y = tan(input.delta)*(BottomPoint.x-input.L1);
//     	}
// 		else if (i > (input.I1+input.I2))
//     	{
//     		BottomPoint.x = input.L1+input.L2+input.L3*(1.0-input.beta3*(pow(((input.beta3+1.0)/(input.beta3-1.0)),(1.0-(double(i-input.I1-input.I2))/input.I3))-1.0)/(pow(((input.beta3+1.0)/(input.beta3-1.0)),(1.0-(double(i-input.I1-input.I2))/input.I3))+1.0));
//     		BottomPoint.y = tan(input.delta)*input.L2;
//     	}

// 		k_inverse = (TopPoint.x - BottomPoint.x)/(TopPoint.y-BottomPoint.y);

// 		if (j == 1)
// 		{
//     		point = BottomPoint;	
// 		}
// 		else if (j>1 && j< input.JM)
// 		{
//      		point.y = BottomPoint.y+(TopPoint.y-BottomPoint.y)/2.0*(1.0-input.beta6*(pow(((input.beta6+1.0)/(input.beta6-1.0)),(1.0-(j-1.0)/ (input.JM/2)))-1.0)/(pow(((input.beta6+1.0)/(input.beta6-1.0)),(1.0-(j-1.0)/ (input.JM/2)))+1.0));
//     		point.x = BottomPoint.x + (point.y-BottomPoint.y)*k_inverse;
// 		}
// 		else if (j == input.JM)
// 		{
//     		point = TopPoint;
//     	}

// 	}

// 	else
// 	{

// 	}

// 	return point;
// }