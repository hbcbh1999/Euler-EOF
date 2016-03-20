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
			GridPoint2D point0 = ComputePosition2D(i+1,j+1,input1);

			pointData << point0.x << " " << point0.y << " " << 0 << "\n";
			// pointData << point1.x << " " << point1.y << " " << 0 << "\n";
			// pointData << point2.x << " " << point2.y << " " << 0 << "\n";
			// pointData << point3.x << " " << point3.y << " " << 0 << "\n";
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
