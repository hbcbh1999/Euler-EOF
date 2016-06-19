#include "HalfTimeStepUpdateStencil.h"

HalfTimeStepUpdateStencil::HalfTimeStepUpdateStencil ( const Parameters & parameters ) : FieldStencil<InviscidFlowField> ( parameters ) {
    gamma = parameters.flow.HeatCapacityRatio;
    sizeX = parameters.geometry.sizeX;
    sizeY = parameters.geometry.sizeY;
}

void HalfTimeStepUpdateStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j)
{
    if (i == 1 || j == 1)
    {

    }
    else
    {
        std::array<FLOAT, 4>  U_bottom, U_right, U_top, U_left;    // U_r, U_{r+1}, U_{r-1} 
        std::array<FLOAT, 4>  F_right, F_left, G_bottom, G_top;

        for (int n = 0;n < 4; n++)
        {
            U_bottom[n] = inviscidFlowField.getUhatBottom().getFlux(i,j)[n]; 
            U_right[n] = inviscidFlowField.getUhatRight().getFlux(i,j)[n]; 
            U_top[n] =  inviscidFlowField.getUhatTop().getFlux(i,j)[n]; 
            U_left[n] = inviscidFlowField.getUhatLeft().getFlux(i,j)[n]; 
    
            F_right[n] = inviscidFlowField.getFhatRight().getFlux(i,j)[n]; 
            F_left[n] = inviscidFlowField.getFhatLeft().getFlux(i,j)[n];  
            G_bottom[n] = inviscidFlowField.getGhatBottom().getFlux(i,j)[n]; 
            G_top[n] =  inviscidFlowField.getGhatTop().getFlux(i,j)[n]; 
        }

       halfTimeStepUpdate(inviscidFlowField, i, j, U_left, F_left, F_right, G_top, G_bottom, 3);        // Left
       halfTimeStepUpdate(inviscidFlowField, i, j, U_right, F_left, F_right, G_top, G_bottom, 1);         // Right
       halfTimeStepUpdate(inviscidFlowField, i, j, U_bottom, F_left, F_right, G_top, G_bottom,  0);           // Bottom
       halfTimeStepUpdate(inviscidFlowField, i, j, U_top, F_left, F_right, G_top, G_bottom, 2);          // Top
    }
}

void HalfTimeStepUpdateStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{
	// TODO: 3D case
}

void HalfTimeStepUpdateStencil::halfTimeStepUpdate( InviscidFlowField & inviscidFlowField, int i, int j , std::array<FLOAT, 4> U, std::array<FLOAT, 4> F_l, std::array<FLOAT, 4> F_r, std::array<FLOAT, 4> G_b, std::array<FLOAT, 4> G_t, int edge)
{
    std::array<FLOAT, 4> U_halfTime, F, G;

    FLOAT dt = 0.01;

    for (int n = 0;n < 4; n++)
    {
        U_halfTime[n] = U[n] + 0.5 * dt * (F_l[n] - F_r[n]) + 0.5 * dt * (G_b[n] - G_t[n]);
    }

    FLOAT rho, u, v, p;
    // Construct the updated flux;
    FLOAT J, xi[2], eta[2]; 
    J = inviscidFlowField.getJ().getScalar(i,j);
    xi[0] = inviscidFlowField.getXi().getVector(i,j)[0];
    xi[1] = inviscidFlowField.getXi().getVector(i,j)[1];
    eta[0] = inviscidFlowField.getEta().getVector(i,j)[0];
    eta[1] = inviscidFlowField.getEta().getVector(i,j)[1];

    rho = U_halfTime[0]/J;
    u = U_halfTime[1]/U_halfTime[0];
    v = U_halfTime[2]/U_halfTime[0];
    p = (gamma-1) * ( U_halfTime[3]/J - 0.5 * rho * (pow(u,2) + pow(v,2) ) ); 

    F[0] = rho * u;
    F[1] = rho * u * u + p;
    F[2] = rho * u * v;
    F[3] = (U_halfTime[3]/J + p) * u;

    G[0] = rho * v;
    G[1] = rho * v * u;
    G[2] = rho * v * v + p;
    G[3] = (U_halfTime[3]/J + p) * v;

    // Read in to flowfield and apply rotation to the flux
    if (edge == 3)
    {   
        xi[0] = inviscidFlowField.getXi().getVector(i-1,j)[0];
        xi[1] = inviscidFlowField.getXi().getVector(i-1,j)[1];
        for (int n = 0;n < 4; n++)
        {
            inviscidFlowField.getUhatLeft().getFlux(i,j)[n] = U_halfTime[n];
            inviscidFlowField.getFhatLeft().getFlux(i,j)[n] = (xi[0] * F[n] + xi[1] * G[n])*J;
        }
    }
    else if (edge == 1)
    {
        xi[0] = inviscidFlowField.getXi().getVector(i,j)[0];
        xi[1] = inviscidFlowField.getXi().getVector(i,j)[1];
        for (int n = 0;n < 4; n++)
        {
            inviscidFlowField.getUhatRight().getFlux(i,j)[n] = U_halfTime[n];
            inviscidFlowField.getFhatRight().getFlux(i,j)[n] = (xi[0] * F[n] + xi[1] * G[n])*J;
        }
    }
    else if (edge == 0)
    {
        eta[0] = inviscidFlowField.getEta().getVector(i,j-1)[0];
        eta[1] = inviscidFlowField.getEta().getVector(i,j-1)[1];
        for (int n = 0;n < 4; n++)
        {
            inviscidFlowField.getUhatBottom().getFlux(i,j)[n] = U_halfTime[n];
            inviscidFlowField.getGhatBottom().getFlux(i,j)[n] = (eta[0] * F[n] + eta[1] * G[n])*J;
        }
    }
    else if (edge == 2)
    {
        eta[0] = inviscidFlowField.getEta().getVector(i,j)[0];
        eta[1] = inviscidFlowField.getEta().getVector(i,j)[1];
        for (int n = 0;n < 4; n++)
        {
            inviscidFlowField.getUhatTop().getFlux(i,j)[n] = U_halfTime[n];
            inviscidFlowField.getGhatTop().getFlux(i,j)[n] = (eta[0] * F[n] + eta[1] * G[n])*J;
        }
    }
}


void HalfTimeStepUpdateStencil::halfTimeStepUpdate( InviscidFlowField & inviscidFlowField, int i, int j, int k, std::array<FLOAT, 5> U, std::array<FLOAT, 5> F_l, std::array<FLOAT, 5> F_r, std::array<FLOAT, 5> G_b, std::array<FLOAT, 5> G_t, std::array<FLOAT, 5> H_f, std::array<FLOAT, 5> H_back, int edge)
{

}

