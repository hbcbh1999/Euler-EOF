#include "UFGHStencil.h"

UFGHStencil::UFGHStencil ( const Parameters & parameters ) : FieldStencil<InviscidFlowField> ( parameters ), BoundaryStencil<InviscidFlowField>(parameters) {
	HeatCapacityRatio = parameters.flow.HeatCapacityRatio;
}

void UFGHStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j)
{
    ConstructUFGH2D(inviscidFlowField, i, j);
}

void UFGHStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k){

	// TODO: 3D case
}

void UFGHStencil::applyLeftWall ( InviscidFlowField & inviscidFlowField, int i, int j)
{
    ConstructUFGH2D(inviscidFlowField, i, j);
}

void UFGHStencil::applyRightWall ( InviscidFlowField & inviscidFlowField, int i, int j)
{
    ConstructUFGH2D(inviscidFlowField, i, j);
}

void UFGHStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j)
{
    ConstructUFGH2D(inviscidFlowField, i, j);
}

void UFGHStencil::applyTopWall ( InviscidFlowField & inviscidFlowField, int i, int j)
{
    ConstructUFGH2D(inviscidFlowField, i, j);
}

// TODO 3D

void UFGHStencil::applyLeftWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}

void UFGHStencil::applyRightWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}

void UFGHStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}

void UFGHStencil::applyTopWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}

void UFGHStencil::applyFrontWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}

void UFGHStencil::applyBackWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}

void UFGHStencil::ConstructUFGH2D( InviscidFlowField & inviscidFlowField, int i, int j )
{

    FLOAT rho,u,v,p;    // Primative variables

    rho = inviscidFlowField.getDensity().getScalar(i,j);
    u = inviscidFlowField.getVelocity().getVector(i,j)[0];
    v = inviscidFlowField.getVelocity().getVector(i,j)[1];
    p = inviscidFlowField.getPressure().getScalar(i,j);

    for (int n = 0; n<4; n++)
    {
        uhat[n] = u * n[n][0] + v * n[n][1];
        vhat[n] = v * n[n][0] - u * n[n][1];
    }
    
    FLOAT U[4],F[4],G[4], Uhat[4][4], Fhat[4][4], Ghat[4][4]; 
    U[0] = rho;   
    U[1] = rho * u;     
    U[2] = rho * v;
    U[3] = 0.5 * rho * (pow(u, 2) + pow(v, 2)) + p/(HeatCapacityRatio - 1);

    F[0] = U[0] * u;
    F[1] = U[1] * u + p;
    F[2] = U[2] * u;
    F[3] = (U[3] + p) * u;

    G[0] = U[0] * v;
    G[1] = U[1] * v;
    G[2] = U[2] * v + p;
    G[3] = (U[3] + p) * v;

    for (int n = 0; n<4; n++)
    {
        inviscidFlowField.getU().getFlux(i,j)[n] =  U[n]/*/J */;
        inviscidFlowField.getF().getFlux(i,j)[n] = /*(xi[0] * */F[n]/* + xi[1] * G[n])/J*/;
        inviscidFlowField.getG().getFlux(i,j)[n] = /*(eta[0] * F[n] + eta[1] * */G[n])/*/J*/;
    }
}