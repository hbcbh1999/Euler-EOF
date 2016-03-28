#include "PointCoordinateStencil.h"
#include "../Preprocessor/SlopeChannel/ComputePosition2D.cpp"

PointCoordinateStencil::PointCoordinateStencil ( const Parameters & parameters ): FieldStencil<InviscidFlowField> ( parameters ) {}

void PointCoordinateStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j)
{
	//TODO: read from the vtk file directly in future
	GridPoint2D point = ComputePosition2D(i,j,input1);
	//-------------------------------------------
	
	inviscidFlowField.getPointCoordinate().getVector(i, j)[1] = point.x;
	inviscidFlowField.getPointCoordinate().getVector(i, j)[2] = point.y;
	// std::cout<< point.x << std::endl;

}

void PointCoordinateStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k){

	// TODO: 3D case
}