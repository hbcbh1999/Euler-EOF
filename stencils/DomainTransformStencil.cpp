#include "DomainTransformStencil.h"
#include "../Preprocessor/SlopeChannel/ComputePosition2D.cpp" // TODO: read from the vtk file directly

DomainTransformStencil::DomainTransformStencil ( const Parameters & parameters ) : FieldStencil<InviscidFlowField> ( parameters ) {}

void DomainTransformStencil::apply ( InviscidFlowField & InviscidFlowField, int i, int j){

	const int obstacle = InviscidFlowField.getFlags().getValue(i,j);

	if ((obstacle & OBSTACLE_SELF) == 0){ // if it is a fluid cell

		GridPoint2D point1 = ComputePosition2D(i+1,j,input1);
		GridPoint2D point2 = ComputePosition2D(i+1,j+1,input1);
		GridPoint2D point3 = ComputePosition2D(i,j+1,input1); 

		// TODO: Add time derivatives
		FLOAT x_xi = point2.x - point3.x;
		FLOAT x_eta = point2.y - point3.y;
		FLOAT y_xi = point2.x - point1.x;
		FLOAT y_eta = point2.y - point1.y;
		// TODO: Store 
		FLOAT J = x_xi*y_eta - x_eta*y_xi;

		InviscidFlowField.getXi().getVector(i, j)[1] = y_eta/J;
		InviscidFlowField.getXi().getVector(i, j)[2] = -x_eta/J;
		InviscidFlowField.getEta().getVector(i, j)[1] = -y_xi/J;
		InviscidFlowField.getEta().getVector(i, j)[2] = x_xi/J;
		InviscidFlowField.getJ().getScalar(i,j) = J;
	}
}

void DomainTransformStencil::apply ( InviscidFlowField & InviscidFlowField, int i, int j, int k){

	// TODO: 3D case
}
