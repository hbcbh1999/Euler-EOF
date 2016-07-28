#include "ReconstructStencil.h"
#include <algorithm>   
ReconstructStencil::ReconstructStencil ( const Parameters & parameters ) : FieldStencil<InviscidFlowField> ( parameters ), BoundaryStencil<InviscidFlowField>(parameters) {
    omega = 0;
    gamma = parameters.flow.HeatCapacityRatio;
    sizeX = parameters.geometry.sizeX;
    sizeY = parameters.geometry.sizeY;
}

void ReconstructStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j)
{
    if(i==1||i==(sizeX+2)||j==1||j==(sizeY+2))
    {

    }
    else
    {
        reconstruct(inviscidFlowField, i, j, 3);    // Left
        reconstruct(inviscidFlowField, i, j, 1);    // Right
        reconstruct(inviscidFlowField, i, j, 0);    // Bottom
        reconstruct(inviscidFlowField, i, j, 2);    // Top
    }
}

void ReconstructStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{
	// TODO: 3D case
}

void ReconstructStencil::applyLeftWall ( InviscidFlowField & inviscidFlowField, int i, int j)
{
    reconstructBoundary(inviscidFlowField, i, j);
 
}

void ReconstructStencil::applyRightWall ( InviscidFlowField & inviscidFlowField, int i, int j)
{
    reconstructBoundary(inviscidFlowField, i, j);
}

void ReconstructStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j)
{
    reconstructBoundary(inviscidFlowField, i, j);
}

void ReconstructStencil::applyTopWall ( InviscidFlowField & inviscidFlowField, int i, int j)
{
    reconstructBoundary(inviscidFlowField, i, j);
}

void ReconstructStencil::applyLeftWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}

void ReconstructStencil::applyRightWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}

void ReconstructStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}

void ReconstructStencil::applyTopWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}

void ReconstructStencil::applyFrontWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}

void ReconstructStencil::applyBackWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}

void ReconstructStencil::reconstruct(InviscidFlowField & inviscidFlowField, int i, int j, int edge)
{
    std::array<FLOAT, 4>  U_r, U_rp1, U_rm1, U_b;    // U_r, U_{r+1}, U_{r-1} 
    std::array<FLOAT, 4>  F_r, F_rp1, F_rm1;
    std::array<FLOAT, 4>  G_r, G_rp1, G_rm1;
    std::array<FLOAT, 4> DeltaU, DeltaF, DeltaG;
    std::array<FLOAT, 4>  U_g, F_g, G_g;
    std::array<FLOAT, 4>  U_rec, F_rec, G_rec;
    
    // Read in from flowfield
    for (int n = 0;n < 4; n++)
    {
        U_r[n] = inviscidFlowField.getUhat().getFlux(i,j)[n];
        // Compute the slope of reconstruction
        if (edge == 0 || edge == 2)     // top & bottom
        {
            U_rp1[n] = inviscidFlowField.getUhat().getFlux(i,j+1)[n];
            U_rm1[n] = inviscidFlowField.getUhat().getFlux(i,j-1)[n];

            // DeltaU[n] = MinMaxMod((U_rp1[n]-U_r[n]),(U_r[n]-U_rm1[n]),0);            
            if((U_rp1[n] - U_r[n]) > 0)
            {
                DeltaU[n] = std::max(0.0,std::min((U_rp1[n] - U_r[n]),(U_r[n] - U_rm1[n])));
            }
            else
            {
                DeltaU[n] = std::min(0.0,std::max((U_rp1[n] - U_r[n]),(U_r[n] - U_rm1[n])));
            }

            // DeltaU[n] = 0.5 * (1 + omega) * (U_r[n] - U_rm1[n]) + 0.5 * (1 - omega) * (U_rp1[n] - U_r[n]);

            // if (j == 2 )
            // {
            //     // U_b[n] = inviscidFlowField.getUhat().getFlux(i,j-1)[n];
            //     DeltaU[n] = 0.0 /*(U_r[n] - U_b[n])/0.5*/;
            // }
            // else if( j == (sizeY + 1))
            // {
            //     // U_b[n] = inviscidFlowField.getUhat().getFlux(i,j+1)[n];
            //     DeltaU[n] = 0.0/* (U_b[n] - U_r[n])/0.5*/;
            // }
        }
        else        // left & right
        {
            U_rp1[n] = inviscidFlowField.getUhat().getFlux(i+1,j)[n];
            U_rm1[n] = inviscidFlowField.getUhat().getFlux(i-1,j)[n];

             // DeltaU[n] = MinMaxMod((U_rp1[n]-U_r[n]),(U_r[n]-U_rm1[n]),0);  

            if((U_rp1[n] - U_r[n]) > 0)
            {
                DeltaU[n] = std::max(0.0,std::min((U_rp1[n] - U_r[n]),(U_r[n] - U_rm1[n])));
            }
            else
            {
                DeltaU[n] = std::min(0.0,std::max((U_rp1[n] - U_r[n]),(U_r[n] - U_rm1[n])));
            }

            // DeltaU[n] = 0.5 * (1 + omega) * (U_r[n] - U_rm1[n]) + 0.5 * (1 - omega) * (U_rp1[n] - U_r[n]);
            // DeltaU[n] = 0;
            if (i == 2 )
            {
                // U_b[n] = inviscidFlowField.getUhat().getFlux(i-1,j)[n];
                DeltaU[n] = 0.0 /*(U_r[n] - U_b[n])/0.5*/;
            }
            else if( i == (sizeX + 1))
            {
                // U_b[n] = inviscidFlowField.getUhat().getFlux(i+1,j)[n];
                DeltaU[n] = 0.0 /*(U_b[n] - U_r[n])/0.5*/;
            }
        }

        // Read in the reconstructed U
        if (edge == 0)
        {   
            U_rec[n] = U_r[n] - 0.5 * DeltaU[n];
            inviscidFlowField.getUhatBottom().getFlux(i,j)[n] = U_rec[n];
        }
        else if (edge == 1)
        {
            U_rec[n] = U_r[n] + 0.5 * DeltaU[n];
            inviscidFlowField.getUhatRight().getFlux(i,j)[n] = U_rec[n];
        }
        else if (edge == 2)
        {
            U_rec[n] = U_r[n] + 0.5 * DeltaU[n];
            inviscidFlowField.getUhatTop().getFlux(i,j)[n] = U_rec[n];
        }
        else
        {
            U_rec[n] = U_r[n] - 0.5 * DeltaU[n];
            inviscidFlowField.getUhatLeft().getFlux(i,j)[n] = U_rec[n];
        }
    }

    // Compute flux 
    FLOAT J, xi[2], eta[2]; 
    J = inviscidFlowField.getJ().getScalar(i,j);
    xi[0] = inviscidFlowField.getXi().getVector(i,j)[0];
    xi[1] = inviscidFlowField.getXi().getVector(i,j)[1];
    eta[0] = inviscidFlowField.getEta().getVector(i,j)[0];
    eta[1] = inviscidFlowField.getEta().getVector(i,j)[1];

    FLOAT rho, u, v, p;
    // Construct the updated flux;
    rho = U_rec[0]/J;
    u = U_rec[1]/U_rec[0];
    v = U_rec[2]/U_rec[0];
    p = (gamma-1) * ( U_rec[3]/J - 0.5 * rho * (pow(u,2) + pow(v,2) ) ); 

    F_rec[0] = rho * u;
    F_rec[1] = rho * u * u + p;
    F_rec[2] = rho * u * v;
    F_rec[3] = (U_rec[3]/J + p) * u;

    G_rec[0] = rho * v;
    G_rec[1] = rho * v * u;
    G_rec[2] = rho * v * v + p;
    G_rec[3] = (U_rec[3]/J + p) * v;

    if (edge == 0)
    {
        eta[0] = inviscidFlowField.getEta().getVector(i,j-1)[0];
        eta[1] = inviscidFlowField.getEta().getVector(i,j-1)[1];
        for (int n = 0;n < 4; n++)
        {   
            inviscidFlowField.getGhatBottom().getFlux(i,j)[n] = (eta[0] * F_rec[n] + eta[1] * G_rec[n])*J;
        }
    }
    else if (edge == 1)
    {
        xi[0] = inviscidFlowField.getXi().getVector(i,j)[0];
        xi[1] = inviscidFlowField.getXi().getVector(i,j)[1];
        for (int n = 0;n < 4; n++)
        {        
            inviscidFlowField.getFhatRight().getFlux(i,j)[n] = (xi[0] * F_rec[n] + xi[1] * G_rec[n])*J;
        }
    }
    else if (edge == 2)
    {
        eta[0] = inviscidFlowField.getEta().getVector(i,j)[0];
        eta[1] = inviscidFlowField.getEta().getVector(i,j)[1];
        for (int n = 0;n < 4; n++)
        {      
            inviscidFlowField.getGhatTop().getFlux(i,j)[n] = (eta[0] * F_rec[n] + eta[1] * G_rec[n])*J;
        }
    }
    else
    {
        xi[0] = inviscidFlowField.getXi().getVector(i-1,j)[0];
        xi[1] = inviscidFlowField.getXi().getVector(i-1,j)[1];            
        for (int n = 0;n < 4; n++)
        {           
            inviscidFlowField.getFhatLeft().getFlux(i,j)[n] = (xi[0] * F_rec[n] + xi[1] * G_rec[n])*J;
        }
    }
 }

void ReconstructStencil::reconstruct(InviscidFlowField & inviscidFlowField, int i, int j, int k, int edge)
{

}

void ReconstructStencil::reconstructBoundary(InviscidFlowField & inviscidFlowField, int i, int j)
{
    std::array<FLOAT, 4>  U_g, F_g, G_g;
        FLOAT rho, u, v, p;

    FLOAT J, xi[2], eta[2]; 
    J = inviscidFlowField.getJ().getScalar(i,j);
    xi[0] = inviscidFlowField.getXi().getVector(i,j)[0];
    xi[1] = inviscidFlowField.getXi().getVector(i,j)[1];
    eta[0] = inviscidFlowField.getEta().getVector(i,j)[0];
    eta[1] = inviscidFlowField.getEta().getVector(i,j)[1];
    for (int n = 0;n < 4; n++)
    {
        U_g[n] = inviscidFlowField.getUhat().getFlux(i,j)[n];
    }
    // Construct the updated flux;
    rho = U_g[0]/J;
    u = U_g[1]/U_g[0];
    v = U_g[2]/U_g[0];
    p = (gamma-1) * ( U_g[3]/J - 0.5 * rho * (pow(u,2) + pow(v,2) ) ); 

    F_g[0] = rho * u;
    F_g[1] = rho * u * u + p;
    F_g[2] = rho * u * v;
    F_g[3] = (U_g[3]/J + p) * u;

    G_g[0] = rho * v;
    G_g[1] = rho * v * u;
    G_g[2] = rho * v * v + p;
    G_g[3] = (U_g[3]/J + p) * v;
    
    for (int n = 0;n < 4; n++)
    {
        inviscidFlowField.getUhatBottom().getFlux(i,j)[n] = U_g[n];
        inviscidFlowField.getUhatRight().getFlux(i,j)[n] = U_g[n];
        inviscidFlowField.getUhatTop().getFlux(i,j)[n] = U_g[n];
        inviscidFlowField.getUhatLeft().getFlux(i,j)[n] = U_g[n];

        inviscidFlowField.getFhatRight().getFlux(i,j)[n] = (xi[0] * F_g[n] + xi[1] * G_g[n])*J;
        inviscidFlowField.getFhatLeft().getFlux(i,j)[n] = (xi[0] * F_g[n] + xi[1] * G_g[n])*J;
        inviscidFlowField.getGhatBottom().getFlux(i,j)[n] = (eta[0] * F_g[n] + eta[1] * G_g[n])*J;
        inviscidFlowField.getGhatTop().getFlux(i,j)[n] = (eta[0] * F_g[n] + eta[1] * G_g[n])*J;
    }
}

void ReconstructStencil::reconstructBoundary(InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}

FLOAT ReconstructStencil::MinMaxMod(FLOAT a, FLOAT b, int k)
{
    if (k == 0)        // Min
    {
        if (a*b > 0)
        {
            if (abs(a) < abs(b))
            {
                return a;
            }
            else
            {
                return b;
            }
        }
        else
        {
            return 0.0;
        }
    }
    if(k == 1 )    // Max
    {
        if (a*b > 0)
        {
            if (abs(a) > abs(b))
            {
                return a;
            }
            else
            {
                return b;
            }
        }
        else
        {
            return 0.0;
        }
    }  

}