#include "RecoverStencil.h"

RecoverStencil::RecoverStencil ( const Parameters & parameters ) : FieldStencil<InviscidFlowField> ( parameters ) {}

void RecoverStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j)
{
    FLOAT Uhat[4],U[4],J;
	J = inviscidFlowField.getJ().getScalar(i,j);
	for (int n = 0; n < 4; ++n)
	{
		Uhat[n] = inviscidFlowField.getUhat().getFlux(i,j)[n];
		U[n] = Uhat[n]/**J*/;
	}
	
	inviscidFlowField.getDensity().getScalar(i,j) = U[0];
	inviscidFlowField.getVelocity().getVector(i,j)[0] = U[1]/U[0];
	inviscidFlowField.getVelocity().getVector(i,j)[1] = U[2]/U[0];
	inviscidFlowField.getPressure().getScalar(i,j) = (_parameters.flow.HeatCapacityRatio-1) *( U[3] - 0.5 * U[0] * ( pow(U[1]/U[0],2) + pow(U[2]/U[0],2) ) ); 
}

void RecoverStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

	// TODO: 3D case
}
