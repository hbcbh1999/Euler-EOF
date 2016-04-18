#include "RoeStencil.h"
#include "../EulerSolver/Riemann/RoeSolver.cpp"

RoeStencil::RoeStencil ( const Parameters & parameters ) : FieldStencil<InviscidFlowField> ( parameters ),BoundaryStencil<InviscidFlowField> (parameters) {
    HeatCapacityRatio = parameters.flow.HeatCapacityRatio;
}

void RoeStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j)
{
    getInterfaceFlux(inviscidFlowField, i, j);
}

void RoeStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

    // TODO: 3D case
}

void RoeStencil::applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j )
{
    getInterfaceFlux(inviscidFlowField, i, j);
}

void RoeStencil::applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j )
{
    // No implementation at right wall
}

void RoeStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j )
{ 
    getInterfaceFlux(inviscidFlowField, i, j);
}

void RoeStencil::applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j )
{
    // No implementation at top wall 
}

// TODO: 3D

void RoeStencil::applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k ){
     
}

void RoeStencil::applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k ){
     
}

void RoeStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k ){
     
}

void RoeStencil::applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j, int k ){
     
}

void RoeStencil::applyFrontWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k ){
     
}

void RoeStencil::applyBackWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k ){}



void RoeStencil::getInterfaceFlux(InviscidFlowField & inviscidFlowField, int i, int j)
{
    std::vector<FLOAT> U_Local,U_Right,U_Top;
    std::vector<FLOAT> F_Local,F_Right;
    std::vector<FLOAT> G_Local,G_Top;
    std::vector<FLOAT> H_Local,H_Front;   
    std::vector<FLOAT> F_mid, G_mid, H_mid;

    for ( int n = 0; n<4; n++)
    {
        U_Local[n] = inviscidFlowField.getUhat().getFlux(i,j)[n];
        U_Right[n] = inviscidFlowField.getUhat().getFlux(i+1,j)[n];
        U_Top[n] = inviscidFlowField.getUhat().getFlux(i,j+1)[n];

        F_Local[n] = inviscidFlowField.getFhat().getFlux(i,j)[n];
        F_Right[n] = inviscidFlowField.getFhat().getFlux(i+1,j)[n];
        
        G_Local[n] = inviscidFlowField.getGhat().getFlux(i,j)[n];
        G_Top[n] = inviscidFlowField.getGhat().getFlux(i,j+1)[n];
    }

    F_mid = RoeSolver(U_Local, U_Top, G_Local, G_Top, HeatCapacityRatio);

    // This function treat Riemann problem on x, y, z direction by changing the sequency of the varible in the outside input. When calculate flux G on y direction, we pass U = [rho, v, u, E] from outside but assign in the function as [rho, u, v, E].

    std::iter_swap(U_Local.begin()+1,U_Local.begin()+2);
    std::iter_swap(U_Top.begin()+1,U_Top.begin()+2);

    std::iter_swap(G_Local.begin()+1,G_Local.begin()+2);
    std::iter_swap(G_Top.begin()+1,G_Top.begin()+2);

    G_mid = RoeSolver(U_Local, U_Top, G_Local, G_Top, HeatCapacityRatio);

    // Change [rho v u E] back to [rho u v E]
    std::iter_swap(G_mid.begin()+1,U_Local.begin()+2);


    for ( int n = 0; n<4; n++)
    {   
        inviscidFlowField.getFmid().getFlux(i,j)[n] = F_mid[n];
        inviscidFlowField.getGmid().getFlux(i,j)[n] = G_mid[n];
    }

}

void RoeStencil::getInterfaceFlux(InviscidFlowField & inviscidFlowField, int i, int j, int k)
{
    //TODO:3D
}  