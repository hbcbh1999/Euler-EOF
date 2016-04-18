#include "DomainTransformStencil.h"
#include <algorithm>
#include <math.h>
// #include "../Preprocessor/SlopeChannel/ComputePosition2D.cpp" // TODO: read from the vtk file directly

DomainTransformStencil::DomainTransformStencil ( const Parameters & parameters ) : FieldStencil<InviscidFlowField>(parameters),BoundaryStencil<InviscidFlowField>(parameters)
{}

void DomainTransformStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j){

	const int obstacle = inviscidFlowField.getFlags().getValue(i,j);

	if ((obstacle & OBSTACLE_SELF) == 0){ // if it is a fluid cell

		FLOAT point1_x = inviscidFlowField.getPointCoordinate().getVector(i,j-1)[0];
		FLOAT point1_y = inviscidFlowField.getPointCoordinate().getVector(i,j-1)[1];
		FLOAT point2_x = inviscidFlowField.getPointCoordinate().getVector(i,j)[0];
		FLOAT point2_y = inviscidFlowField.getPointCoordinate().getVector(i,j)[1];
		FLOAT point3_x = inviscidFlowField.getPointCoordinate().getVector(i-1,j)[0];
		FLOAT point3_y = inviscidFlowField.getPointCoordinate().getVector(i-1,j)[1];

		// TODO: Add time derivatives
		FLOAT x_xi = point2_x - point3_x;
		FLOAT x_eta = point2_y - point3_y;
		FLOAT y_xi = point2_x - point1_x;
		FLOAT y_eta = point2_y - point1_y;
		// TODO: Store
		FLOAT J = x_xi*y_eta - x_eta*y_xi; // TODO: Change the notation

		inviscidFlowField.getXi().getVector(i, j)[0] = y_eta/J;
		inviscidFlowField.getXi().getVector(i, j)[1] = -x_eta/J;
		inviscidFlowField.getEta().getVector(i, j)[0] = -y_xi/J;
		inviscidFlowField.getEta().getVector(i, j)[1] = x_xi/J;
		inviscidFlowField.getJ().getScalar(i,j) = J;
	}
}

void DomainTransformStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
	// TODO: 3D case
}

void DomainTransformStencil::applyLeftWall ( InviscidFlowField & inviscidFlowField, int i, int j){

	// Copy the metrics from the interior point on its right
	inviscidFlowField.getXi().getVector(i, j)[0] = inviscidFlowField.getXi().getVector(i+1, j)[0];
	inviscidFlowField.getXi().getVector(i, j)[1] = inviscidFlowField.getXi().getVector(i+1, j)[1];
	inviscidFlowField.getEta().getVector(i, j)[0] = inviscidFlowField.getEta().getVector(i+1, j)[0];
	inviscidFlowField.getEta().getVector(i, j)[1] = inviscidFlowField.getEta().getVector(i+1, j)[1];
	inviscidFlowField.getJ().getScalar(i,j) = inviscidFlowField.getJ().getScalar(i+1,j);
}
void DomainTransformStencil::applyRightWall ( InviscidFlowField & inviscidFlowField, int i, int j){

	// Copy the metrics from the interior point on its left
	inviscidFlowField.getXi().getVector(i, j)[0] = inviscidFlowField.getXi().getVector(i-1, j)[0];
	inviscidFlowField.getXi().getVector(i, j)[1] = inviscidFlowField.getXi().getVector(i-1, j)[1];
	inviscidFlowField.getEta().getVector(i, j)[0] = inviscidFlowField.getEta().getVector(i-1, j)[0];
	inviscidFlowField.getEta().getVector(i, j)[1] = inviscidFlowField.getEta().getVector(i-1, j)[1];
	inviscidFlowField.getJ().getScalar(i,j) = inviscidFlowField.getJ().getScalar(i-1,j);
}
void DomainTransformStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j){

	// Copy the metrics from the interior point on its top
	inviscidFlowField.getXi().getVector(i, j)[0] = inviscidFlowField.getXi().getVector(i, j+1)[0];
	inviscidFlowField.getXi().getVector(i, j)[1] = inviscidFlowField.getXi().getVector(i, j+1)[1];
	inviscidFlowField.getEta().getVector(i, j)[0] = inviscidFlowField.getEta().getVector(i, j+1)[0];
	inviscidFlowField.getEta().getVector(i, j)[1] = inviscidFlowField.getEta().getVector(i, j+1)[1];
	inviscidFlowField.getJ().getScalar(i,j) = inviscidFlowField.getJ().getScalar(i,j+1);
}
void DomainTransformStencil::applyTopWall ( InviscidFlowField & inviscidFlowField, int i, int j){

	// Copy the metrics from the interior point on its bottom
	inviscidFlowField.getXi().getVector(i, j)[0] = inviscidFlowField.getXi().getVector(i, j-1)[0];
	inviscidFlowField.getXi().getVector(i, j)[1] = inviscidFlowField.getXi().getVector(i, j-1)[1];
	inviscidFlowField.getEta().getVector(i, j)[0] = inviscidFlowField.getEta().getVector(i, j-1)[0];
	inviscidFlowField.getEta().getVector(i, j)[1] = inviscidFlowField.getEta().getVector(i, j-1)[1];
	inviscidFlowField.getJ().getScalar(i,j) = inviscidFlowField.getJ().getScalar(i,j-1);
}

void DomainTransformStencil::applyLeftWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
}
void DomainTransformStencil::applyRightWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
}
void DomainTransformStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
}
void DomainTransformStencil::applyTopWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
}
void DomainTransformStencil::applyFrontWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
}
void DomainTransformStencil::applyBackWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
}