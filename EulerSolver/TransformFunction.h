#ifndef _TRANSFORM_FUNCTION_H_
#define _TRANSFORM_FUNCTION_H_

#include <math.h>
#include "../Parameters.h"
#include "../Definitions.h"
#include "../EulerSolver/InviscidFlowField.h"

inline void PhysicsToComputationalDomain2D (InviscidFlowField & inviscidFlowField, FLOAT pv[4], FLOAT HeatCapacityRatio, int i, int j)
{
    FLOAT J, xi[2], eta[2]; 
    J = inviscidFlowField.getJ().getScalar(i,j);
    xi[0] = inviscidFlowField.getXi().getVector(i,j)[0];
    xi[1] = inviscidFlowField.getXi().getVector(i,j)[1];
    eta[0] = inviscidFlowField.getEta().getVector(i,j)[0];
    eta[1] = inviscidFlowField.getEta().getVector(i,j)[1];

    FLOAT U[4],F[4],G[4];       
    // State variables and fluxes
    U[0] = pv[0];   
    U[1] = pv[0] * pv[1];     
    U[2] = pv[0] * pv[2];
    U[3] = 0.5 * pv[0] * (pow(pv[1], 2) + pow(pv[2], 2)) + pv[3]/(HeatCapacityRatio - 1);

    F[0] = U[0] * pv[1];
    F[1] = U[1] * pv[1] + pv[3];
    F[2] = U[2] * pv[1];
    F[3] = (U[3] + pv[3]) * pv[1];

    G[0] = U[0] * pv[2];
    G[1] = U[1] * pv[2];
    G[2] = U[2] * pv[2] + pv[3];
    G[3] = (U[3] + pv[3]) * pv[2];

    // Apply domain transformation:
    for (int n = 0; n<4; n++)
    {
        inviscidFlowField.getUhat().getFlux(i,j)[n] =  U[n]/*/J*/ ;
        inviscidFlowField.getFhat().getFlux(i,j)[n] = /*(xi[0] **/ F[n] /*+ xi[1] * G[n])/J*/;
        inviscidFlowField.getGhat().getFlux(i,j)[n] = /*(eta[0] * F[n] + eta[1] **/ G[n]/*)/J*/;
    }
}


#endif