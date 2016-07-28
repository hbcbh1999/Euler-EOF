#include "VTKGeoStencil.h"

VTKGeoStencil::VTKGeoStencil(const Parameters & parameters) :
		FieldStencil<InviscidFlowField>(parameters) {
			// _inviscid = (parameters.simulation.type=="inviscid");
			_meshsize = parameters.meshsize;
			cellRefNum = 0;
			_dim = parameters.geometry.dim;
			 _prefix = parameters.vtk.prefix;
			 sizeX = parameters.geometry.sizeX;
			sizeY = parameters.geometry.sizeY;
}

void VTKGeoStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j )
{
	if (i>1 && j > 1)
	{
		pointData << inviscidFlowField.getPointCoordinate().getVector(i-1,j-1)[0] << " " << inviscidFlowField.getPointCoordinate().getVector(i-1,j-1)[1]<< " " << 0 << "\n";
		pointData << inviscidFlowField.getPointCoordinate().getVector(i,j-1)[0] << " " << inviscidFlowField.getPointCoordinate().getVector(i,j-1)[1]<< " " << 0 << "\n";
		pointData << inviscidFlowField.getPointCoordinate().getVector(i,j)[0] << " " << inviscidFlowField.getPointCoordinate().getVector(i,j)[1]<< " " << 0 << "\n";
		pointData << inviscidFlowField.getPointCoordinate().getVector(i-1,j)[0] << " " << inviscidFlowField.getPointCoordinate().getVector(i-1,j)[1]<< " " << 0 << "\n";

	// Write cell data;

		cellData << 4 << " ";
		for (int ii = 0; ii<4; ii++)
		{
			cellData << cellRefNum + ii << " "; 
		}
		cellData << "\n";
	cellRefNum = cellRefNum + 4;

	// Write cell type;
	cellType << 9 << " ";
	pressureValue << inviscidFlowField.getPressure().getScalar(i,j)<<"\n";
    }       		


}



void VTKGeoStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{
	
}

void VTKGeoStencil::write ( InviscidFlowField &  inviscidFlowField, int timeStep )
{
	std::ofstream vtkFile;
	std::stringstream vtkFileName;
	std::string fileName;
	// Out put the timestep as the vtk file name.
	vtkFileName <<"./result/" << _prefix <<"." << timeStep << ".vtk";
	fileName = vtkFileName.str();

	// Write the vtk content
	vtkFile.open(fileName.c_str());

	// // Vtk Header
	vtkFile << "# vtk DataFile Version 3.1" << "\n";
	vtkFile << "This is the Output of the flow field"<< " " << _prefix << " " << "for paraview" << "\n";
	vtkFile << "ASCII" << "\n" << "DATASET UNSTRUCTURED_GRID"<< "\n" << "\n";
	// Write point location;
	if (_dim == 3){

	} 
	else{
		vtkFile << "POINTS " << 4*(inviscidFlowField.getNx()) * (inviscidFlowField.getNy()) << " " << "FLOAT" << "\n";
		vtkFile << pointData.str()<< "\n";

	// // Write cell data;
		vtkFile << "CELLS " << (inviscidFlowField.getNx()) * (inviscidFlowField.getNy()) << " " << 5*(inviscidFlowField.getNx()) * (inviscidFlowField.getNy()) << "\n";
		vtkFile << cellData.str()<< "\n";

	// Write cell type;
		vtkFile << "CELL_TYPES " << (inviscidFlowField.getNx()) * (inviscidFlowField.getNy()) << "\n";
		vtkFile << cellType.str()<< "\n";

		vtkFile << "CELL_DATA " << (inviscidFlowField.getNx()) * (inviscidFlowField.getNy()) << "\n";

	// // Write pressure in cell data;
	// 	vtkFile << "VECTORS PointCoordinate FLOAT" << "\n";
	// 	vtkFile << PointCoordinateValue.str() << "\n";

	// 	vtkFile << "VECTORS Xi FLOAT" << "\n";
	// 	vtkFile << XiValue.str() << "\n";

	// 	vtkFile << "VECTORS Eta FLOAT \n";
	// 	vtkFile << EtaValue.str() << "\n";

    	vtkFile << "SCALARS Pressure FLOAT" << "\n" << "LOOKUP_TABLE default"<< "\n";
		vtkFile << pressureValue.str() << "\n"; 

	}
		vtkFile.close();
}

void VTKGeoStencil::clear ()
{
	cellRefNum = 0;
	pointData.str("");
	cellData.str("");
	cellType.str("");
	pressureValue.str("");
}