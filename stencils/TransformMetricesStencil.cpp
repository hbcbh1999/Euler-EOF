#include "TransformMetricesStencil.h"
#include <algorithm>
#include <math.h>
// #include "../Preprocessor/SlopeChannel/ComputePosition2D.cpp" // TODO: read from the vtk file directly

TransformMetricesStencil::TransformMetricesStencil ( const Parameters & parameters ) : FieldStencil<InviscidFlowField>(parameters),BoundaryStencil<InviscidFlowField>(parameters)
{

}

void TransformMetricesStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j){

		FLOAT point1_x = inviscidFlowField.getPointCoordinate().getVector(i,j-1)[0];
		FLOAT point1_y = inviscidFlowField.getPointCoordinate().getVector(i,j-1)[1];
		FLOAT point2_x = inviscidFlowField.getPointCoordinate().getVector(i,j)[0];
		FLOAT point2_y = inviscidFlowField.getPointCoordinate().getVector(i,j)[1];
		FLOAT point3_x = inviscidFlowField.getPointCoordinate().getVector(i-1,j)[0];
		FLOAT point3_y = inviscidFlowField.getPointCoordinate().getVector(i-1,j)[1];

		// TODO: Add time derivatives
		FLOAT x_xi = point2_x - point3_x;
		FLOAT y_xi = point2_y - point3_y;
		FLOAT x_eta = point2_x - point1_x;
		FLOAT y_eta = point2_y - point1_y;
		
		// TODO: Store
		FLOAT J = x_xi*y_eta - x_eta*y_xi; // TODO: Change the notation

		inviscidFlowField.getXi().getVector(i, j)[0] = y_eta/J;
		inviscidFlowField.getXi().getVector(i, j)[1] = -x_eta/J;
		inviscidFlowField.getEta().getVector(i, j)[0] = -y_xi/J;
		inviscidFlowField.getEta().getVector(i, j)[1] = x_xi/J;
		inviscidFlowField.getJ().getScalar(i,j) = J;

}

void TransformMetricesStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
	// TODO: 3D case
}

void TransformMetricesStencil::applyLeftWall ( InviscidFlowField & inviscidFlowField, int i, int j){

		FLOAT point1_x = inviscidFlowField.getPointCoordinate().getVector(i,j-1)[0];
		FLOAT point1_y = inviscidFlowField.getPointCoordinate().getVector(i,j-1)[1];
		FLOAT point2_x = inviscidFlowField.getPointCoordinate().getVector(i,j)[0];
		FLOAT point2_y = inviscidFlowField.getPointCoordinate().getVector(i,j)[1];
		FLOAT point3_x = inviscidFlowField.getPointCoordinate().getVector(i-1,j)[0];
		FLOAT point3_y = inviscidFlowField.getPointCoordinate().getVector(i-1,j)[1];

		// TODO: Add time derivatives
		FLOAT x_xi = point2_x - point3_x;
		FLOAT y_xi = point2_y - point3_y;
		FLOAT x_eta = point2_x - point1_x;
		FLOAT y_eta = point2_y - point1_y;
		
		// TODO: Store
		FLOAT J = x_xi*y_eta - x_eta*y_xi; // TODO: Change the notation

		inviscidFlowField.getXi().getVector(i, j)[0] = y_eta/J;
		inviscidFlowField.getXi().getVector(i, j)[1] = -x_eta/J;
		inviscidFlowField.getEta().getVector(i, j)[0] = -y_xi/J;
		inviscidFlowField.getEta().getVector(i, j)[1] = x_xi/J;
		inviscidFlowField.getJ().getScalar(i,j) = J;
}
void TransformMetricesStencil::applyRightWall ( InviscidFlowField & inviscidFlowField, int i, int j){

		FLOAT point1_x = inviscidFlowField.getPointCoordinate().getVector(i,j-1)[0];
		FLOAT point1_y = inviscidFlowField.getPointCoordinate().getVector(i,j-1)[1];
		FLOAT point2_x = inviscidFlowField.getPointCoordinate().getVector(i,j)[0];
		FLOAT point2_y = inviscidFlowField.getPointCoordinate().getVector(i,j)[1];
		FLOAT point3_x = inviscidFlowField.getPointCoordinate().getVector(i-1,j)[0];
		FLOAT point3_y = inviscidFlowField.getPointCoordinate().getVector(i-1,j)[1];

		// TODO: Add time derivatives
		FLOAT x_xi = point2_x - point3_x;
		FLOAT y_xi = point2_y - point3_y;
		FLOAT x_eta = point2_x - point1_x;
		FLOAT y_eta = point2_y - point1_y;
		
		// TODO: Store
		FLOAT J = x_xi*y_eta - x_eta*y_xi; // TODO: Change the notation

		inviscidFlowField.getXi().getVector(i, j)[0] = y_eta/J;
		inviscidFlowField.getXi().getVector(i, j)[1] = -x_eta/J;
		inviscidFlowField.getEta().getVector(i, j)[0] = -y_xi/J;
		inviscidFlowField.getEta().getVector(i, j)[1] = x_xi/J;
		inviscidFlowField.getJ().getScalar(i,j) = J;
}
void TransformMetricesStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j){
	
		FLOAT point1_x = inviscidFlowField.getPointCoordinate().getVector(i,j-1)[0];
		FLOAT point1_y = inviscidFlowField.getPointCoordinate().getVector(i,j-1)[1];
		FLOAT point2_x = inviscidFlowField.getPointCoordinate().getVector(i,j)[0];
		FLOAT point2_y = inviscidFlowField.getPointCoordinate().getVector(i,j)[1];
		FLOAT point3_x = inviscidFlowField.getPointCoordinate().getVector(i-1,j)[0];
		FLOAT point3_y = inviscidFlowField.getPointCoordinate().getVector(i-1,j)[1];

		// TODO: Add time derivatives
		FLOAT x_xi = point2_x - point3_x;
		FLOAT y_xi = point2_y - point3_y;
		FLOAT x_eta = point2_x - point1_x;
		FLOAT y_eta = point2_y - point1_y;
		
		// TODO: Store
		FLOAT J = x_xi*y_eta - x_eta*y_xi; // TODO: Change the notation

		inviscidFlowField.getXi().getVector(i, j)[0] = y_eta/J;
		inviscidFlowField.getXi().getVector(i, j)[1] = -x_eta/J;
		inviscidFlowField.getEta().getVector(i, j)[0] = -y_xi/J;
		inviscidFlowField.getEta().getVector(i, j)[1] = x_xi/J;
		inviscidFlowField.getJ().getScalar(i,j) = J;

}
void TransformMetricesStencil::applyTopWall ( InviscidFlowField & inviscidFlowField, int i, int j){

		FLOAT point1_x = inviscidFlowField.getPointCoordinate().getVector(i,j-1)[0];
		FLOAT point1_y = inviscidFlowField.getPointCoordinate().getVector(i,j-1)[1];
		FLOAT point2_x = inviscidFlowField.getPointCoordinate().getVector(i,j)[0];
		FLOAT point2_y = inviscidFlowField.getPointCoordinate().getVector(i,j)[1];
		FLOAT point3_x = inviscidFlowField.getPointCoordinate().getVector(i-1,j)[0];
		FLOAT point3_y = inviscidFlowField.getPointCoordinate().getVector(i-1,j)[1];

		// TODO: Add time derivatives
		FLOAT x_xi = point2_x - point3_x;
		FLOAT y_xi = point2_y - point3_y;
		FLOAT x_eta = point2_x - point1_x;
		FLOAT y_eta = point2_y - point1_y;
		
		// TODO: Store
		FLOAT J = x_xi*y_eta - x_eta*y_xi; // TODO: Change the notation

		inviscidFlowField.getXi().getVector(i, j)[0] = y_eta/J;
		inviscidFlowField.getXi().getVector(i, j)[1] = -x_eta/J;
		inviscidFlowField.getEta().getVector(i, j)[0] = -y_xi/J;
		inviscidFlowField.getEta().getVector(i, j)[1] = x_xi/J;
		inviscidFlowField.getJ().getScalar(i,j) = J;
}

void TransformMetricesStencil::applyLeftWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
}
void TransformMetricesStencil::applyRightWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
}
void TransformMetricesStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
}
void TransformMetricesStencil::applyTopWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
}
void TransformMetricesStencil::applyFrontWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
}
void TransformMetricesStencil::applyBackWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
}
