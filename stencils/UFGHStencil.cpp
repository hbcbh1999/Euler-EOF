#include "UFGHStencil.h"
// #include "../Preprocessor/SlopeChannel/ComputePosition2D.cpp" // TODO: read from the vtk file directly

UFGHStencil::UFGHStencil ( const Parameters & parameters ) : FieldStencil<InviscidFlowField> ( parameters ) {}

void UFGHStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j){

	const int obstacle = inviscidFlowField.getFlags().getValue(i,j);

	if ((obstacle & OBSTACLE_SELF) == 0){ // if it is a fluid cell

		FLOAT p = inviscidFlowField.getPressure().getScalar(i,j);		

		FLOAT J = inviscidFlowField.getJ().getScalar(i,j);
		FLOAT xi_x = inviscidFlowField.getXi().getVector(i,j)[0];
		FLOAT xi_y = inviscidFlowField.getXi().getVector(i,j)[1];
		FLOAT eta_x = inviscidFlowField.getEta().getVector(i,j)[0];
		FLOAT eta_y = inviscidFlowField.getEta().getVector(i,j)[1];

		FLOAT U[4],F[4],G[4];
		U[0] = inviscidFlowField.getDensity().getScalar(i,j);
		U[1] = U[0] * inviscidFlowField.getVelocity().getVector(i,j)[0];
		U[2] = U[0] * inviscidFlowField.getVelocity().getVector(i,j)[1];
		U[3] = 0.5 * U[0] * ( pow(U[1]/U[0],2) + pow(U[2]/U[0],2) ) + p/(_parameters.flow.HeatCapacityRatio-1);

		// Flux F
		F[0] = U[0] * U[1];
		F[1] = U[0] * pow(U[1],2) + p;
		F[2] = U[0] * U[1] * U[2];
		F[3] = U[1] * (U[3] + p);

		// Flux G
		G[0] = U[0] * U[2];
		G[1] = U[0] * pow(U[2],2) + p;
		G[2] = U[0] * U[1] * U[2];
		G[3] = U[2] * (U[3] + p);

		// Apply domain transformation

		for (int n = 0; n<4; n++)
		{
			inviscidFlowField.getUhat().getFlux(i,j)[n] = J * U[n] ;
			inviscidFlowField.getFhat().getFlux(i,j)[n] = J * (xi_x * F[n] + xi_y * G[n]);
			inviscidFlowField.getGhat().getFlux(i,j)[n] = J * (eta_x * F[n] + eta_y * G[n]);
		}

	}
}

void UFGHStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k){

	// TODO: 3D case
}
