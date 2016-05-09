#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <array>
#include "ComputePosition2D.cpp"

int main(int argc, char const *argv[])
{
	std::ofstream vtkFile;
	std::string fileName = "Slope_channel_grid.vtk";
	std::stringstream pointData,cellData,cellType;
	int cellRefNum = 0;
/*------------------ TEST MANUAL INPUT----------------------*/
	// node number

/*-------------------------------------------------------*/
	// cellwise loop
	for( int j = 0; j < input1.JM; j++ )
	{
		for ( int i = 0; i < input1.IM; i++ )
		{
			// store cell indices in stringstream
			// cellData << 4 << " ";
			// for (int ii = 0; ii<4; ii++)
			// {
			// 	cellData << cellRefNum + ii << " "; 
			// }
			// cellData << "\n";
			// cellRefNum = cellRefNum + 4;
			// // store cell type
			// cellType << 9 << "\n";
			// Store grid point	
			std::array<double,2> point0 = ComputePosition2D(i+1,j+1,input1);

			pointData << point0[0] << " " << point0[1] << " " << 0 << "\n";
			// pointData << point1[0] << " " << point1[1] << " " << 0 << "\n";
			// pointData << point2[0] << " " << point2[1] << " " << 0 << "\n";
			// pointData << point3[0] << " " << point3[1] << " " << 0 << "\n";
		}
	}
 
	// Write to the vtk file
	vtkFile.open(fileName.c_str());
	// Vtk Header
	vtkFile << "# vtk DataFile Version 3.1" << "\n";
	vtkFile << "This is the Output of the flow field for paraview" << "\n";
	vtkFile << "ASCII" << "\n" << "DATASET STRUCTURED_GRID"<< "\n";
	vtkFile << "DIMENSIONS " << input1.IM << " " << input1.JM << " " << 1 << " " << "\n"<<"\n";

	// // Write cell data;
	// vtkFile << "CELLS " << (input1.IM - 1)*(input1.JM - 1) << " " << 5* (input1.IM - 1)*(input1.JM - 1) << "\n";
	// vtkFile << cellData.str()<< "\n";
	// // Write cell type;
 // 	vtkFile << "CELL_TYPES " << (input1.IM - 1)*(input1.JM - 1) << "\n";
	// vtkFile << cellType.str()<< "\n";
	// Write cell point:
	vtkFile << "POINTS " << (input1.IM )*(input1.JM) << " " << "FLOAT" << "\n";
		vtkFile << pointData.str()<< "\n";
	vtkFile.close();

	return 0;
}
