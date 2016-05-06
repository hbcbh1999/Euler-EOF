#include "BoundaryConditionStencil.h"

InletBoundaryConditionStencil::InletBoundaryConditionStencil(const Parameters & parameters):
    BoundaryStencil<InviscidFlowField>(parameters) 
    {
    	HeatCapacityRatio = parameters.flow.HeatCapacityRatio;
    	// Freestream velocity
    	FreeStreamVelocity[0] = parameters.flow.Ma;                   
    	FreeStreamVelocity[1] = 0;		
    	FreeStreamVelocity[2] = 0.0;                           
    }

// Charateristic boundary condition applied

void InletBoundaryConditionStencil::applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j )
{

 //    FLOAT J, xi[2], eta[2], XI, ETA; 
 //    J = inviscidFlowField.getJ().getScalar(i,j);
 //    xi[0] = inviscidFlowField.getXi().getVector(i,j)[0];
 //    xi[1] = inviscidFlowField.getXi().getVector(i,j)[1];
 //    eta[0] = inviscidFlowField.getEta().getVector(i,j)[0];
 //    eta[1] = inviscidFlowField.getEta().getVector(i,j)[1];

 //    ETA = sqrt(pow(eta[0],2) + pow(eta[1],2));
 //    XI = sqrt(pow(xi[0],2) + pow(xi[1],2));


	// FLOAT pv_fs[4],pv_g[4],pv_i[4],pv_b[4];		// Primative variables for freestream, ghost cell, interior cell
	// // Freestream variables:
	// pv_fs[0] = 1.0;							// rho
	// pv_fs[1] = FreeStreamVelocity[0];		// u
	// pv_fs[2] = FreeStreamVelocity[1];		// v
	// pv_fs[3] = 1.0;	 						// p
	// // Ghost variables;
	// pv_g[0] = inviscidFlowField.getDensity().getScalar(i,j);
	// pv_g[1] = inviscidFlowField.getVelocity().getVector(i,j)[0];
	// pv_g[2] = inviscidFlowField.getVelocity().getVector(i,j)[1];
	// pv_g[3] = inviscidFlowField.getPressure().getScalar(i,j);
	// // Interior variables
	// pv_i[0] = inviscidFlowField.getDensity().getScalar(i+1,j);
	// pv_i[1] = inviscidFlowField.getVelocity().getVector(i+1,j)[0];
	// pv_i[2] = inviscidFlowField.getVelocity().getVector(i+1,j)[1];
	// pv_i[3] = inviscidFlowField.getPressure().getScalar(i+1,j);
	// //TODO: further verification needed, Initially compute wall primative variables by linearization 
	
	// FLOAT r0 = 1.0; 
	// FLOAT c0 = 1.0; 

	// if (_parameters.flow.Ma >= 1)		// Supersonic fslow
	// { 	
	// 	for (int n = 0; n<4; n++)
	// 	{
	// 		pv_b[n] = pv_fs[n];		// Read the free stream value to 
	// 	}
	// }
	// else		// Subsonic flow
	// {
	// 	// Caculate the pressure from the charateristic varibles relation
	// 	pv_b[3] = 0.5*(pv_fs[3] + pv_i[3] + r0 * c0 * (xi[0] * (pv_fs[1] - pv_i[1]) + xi[1] * (pv_fs[2] - pv_i[2])))/XI;
	// 	pv_b[0] = pv_fs[0] +  (pv_b[3] - pv_fs[3])/(pow(c0,2));
	// 	pv_b[1] = pv_fs[1] +  xi[0]/XI * (pv_fs[3] - pv_b[3])/(r0 * c0);
	// 	pv_b[2] = pv_fs[2] +  xi[1]/XI * (pv_fs[3] - pv_b[3])/(r0 * c0);
	// }

	// for (int n = 0; n<4; n++)
	// {
	// 	pv_g[n] = pv_b[n];		// Extrapolate to the ghost cell
	// }
	// // // // *************************************** Debug
	// inviscidFlowField.getDensity().getScalar(i,j) = pv_g[0];	// rho
	// inviscidFlowField.getVelocity().getVector(i,j)[0] = pv_g[1];
	// inviscidFlowField.getVelocity().getVector(i,j)[1] = pv_g[2];
	// inviscidFlowField.getPressure().getScalar(i,j) = pv_g[3];
	// //  						// p

		// // // *************************************** Debug
	// if (j>25 && j < 50){
	inviscidFlowField.getDensity().getScalar(i,j) = 1.0;	// rho
	inviscidFlowField.getVelocity().getVector(i,j)[0] = FreeStreamVelocity[0];
	inviscidFlowField.getVelocity().getVector(i,j)[1] = FreeStreamVelocity[1];	
	inviscidFlowField.getPressure().getScalar(i,j) = 1.0;
	// }
	// else
	// {
	// inviscidFlowField.getDensity().getScalar(i,j) = 1.0;	// rho
	// inviscidFlowField.getVelocity().getVector(i,j)[0] = FreeStreamVelocity[0] * 0.8;
	// inviscidFlowField.getVelocity().getVector(i,j)[1] = 0;	
	// inviscidFlowField.getPressure().getScalar(i,j) = 1.0;		
	// }
	//  						// p

	/// **************************** Debug 2


}

// TODO: implement the inlet condition from other wall
void InletBoundaryConditionStencil::applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j )
{}

void InletBoundaryConditionStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j )
{}

void InletBoundaryConditionStencil::applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j )
{}

// TODO: 3D
void InletBoundaryConditionStencil::applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void InletBoundaryConditionStencil::applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void InletBoundaryConditionStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void InletBoundaryConditionStencil::applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void InletBoundaryConditionStencil::applyFrontWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void InletBoundaryConditionStencil::applyBackWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}



WallBoundaryConditionStencil::WallBoundaryConditionStencil(const Parameters & parameters):
BoundaryStencil<InviscidFlowField>(parameters) 
{
	HeatCapacityRatio = parameters.flow.HeatCapacityRatio;
	// Freestream velocity
}

void WallBoundaryConditionStencil::applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j )
{}

void WallBoundaryConditionStencil::applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j )
{}

void WallBoundaryConditionStencil::applyBottomWall ( 
	InviscidFlowField & inviscidFlowField, int i, int j )
{	
    FLOAT J, xi[2], eta[2], XI, ETA; 
    J = inviscidFlowField.getJ().getScalar(i,j);
    xi[0] = inviscidFlowField.getXi().getVector(i,j)[0];
    xi[1] = inviscidFlowField.getXi().getVector(i,j)[1];
    eta[0] = inviscidFlowField.getEta().getVector(i,j)[0];
    eta[1] = inviscidFlowField.getEta().getVector(i,j)[1];

    ETA = sqrt(pow(eta[0],2) + pow(eta[1],2));
    XI = sqrt(pow(xi[0],2) + pow(xi[1],2));

	FLOAT pv_g[4],pv_i[4],pv_b[4];		// Primative variables for freestream, ghost cell, interior cell
	// Ghost variables;

	// Interior variables
	pv_i[0] = inviscidFlowField.getDensity().getScalar(i,j+1);
	pv_i[1] = inviscidFlowField.getVelocity().getVector(i,j+1)[0];
	pv_i[2] = inviscidFlowField.getVelocity().getVector(i,j+1)[1];
	pv_i[3] = inviscidFlowField.getPressure().getScalar(i,j+1);
	// Initially compute wall primative variables by linearization
 
	FLOAT r0 = 1.0; 
	FLOAT c0 = 1.0; 

	pv_g[3] = pv_i[3] /*+ r0 * c0 * (eta[0] * pv_i[1] + eta[1] * pv_i[2])/ETA*/;
	pv_g[0] = pv_i[0];
	pv_g[1] = pv_i[1] - 2 * eta[0] * (eta[0] * pv_i[1] + eta[1] * pv_i[2])/pow(ETA,2); 
	pv_g[2] = pv_i[2] - 2 * eta[1] * (eta[0] * pv_i[1] + eta[1] * pv_i[2])/pow(ETA,2);

	// for (int n = 0; n<4; n++)
	// {
	// 	pv_g[n] = 2* pv_b[n] - pv_i[n];		// Extrapolate to the ghost cell
	// }

	inviscidFlowField.getDensity().getScalar(i,j) = pv_g[0];	// rho
	inviscidFlowField.getVelocity().getVector(i,j)[0] = pv_g[1];
	inviscidFlowField.getVelocity().getVector(i,j)[1] = pv_g[2];
	inviscidFlowField.getPressure().getScalar(i,j) = pv_g[3];

	// inviscidFlowField.getDensity().getScalar(i,j) = inviscidFlowField.getDensity().getScalar(i,j+1);	// rho
	// inviscidFlowField.getVelocity().getVector(i,j)[0] = inviscidFlowField.getVelocity().getVector(i,j+1)[0];
	// inviscidFlowField.getVelocity().getVector(i,j)[1] = -inviscidFlowField.getVelocity().getVector(i,j+1)[1];
	// inviscidFlowField.getPressure().getScalar(i,j) = inviscidFlowField.getPressure().getScalar(i,j+1);
}

void WallBoundaryConditionStencil::applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j )
{
	// // Get the transform metrices
	// FLOAT  xi[2], eta[2], XI, ETA; 
	
	// xi[0] = inviscidFlowField.getXi().getVector(i,j)[0];
	// xi[1] = inviscidFlowField.getXi().getVector(i,j)[1];
	// eta[0] = inviscidFlowField.getEta().getVector(i,j)[0];
	// eta[1] = inviscidFlowField.getEta().getVector(i,j)[1];

	// XI = sqrt(pow(xi[0],2)+pow(xi[1],2));
	// ETA = sqrt(pow(eta[0],2)+pow(eta[1],2));

	// FLOAT pv_g[4],pv_i[4],pv_b[4];		// Primative variables for freestream, ghost cell, interior cell
	// 		// State variables and fluxes for freestream, ghost cell, interior cell
	// // // Ghost variables;
	// pv_g[0] = inviscidFlowField.getDensity().getScalar(i,j);
	// pv_g[1] = inviscidFlowField.getVelocity().getVector(i,j)[0];
	// pv_g[2] = inviscidFlowField.getVelocity().getVector(i,j)[1];
	// pv_g[3] = inviscidFlowField.getPressure().getScalar(i,j);
	// // // Interior variables
	// pv_i[0] = inviscidFlowField.getDensity().getScalar(i,j-1);
	// pv_i[1] = inviscidFlowField.getVelocity().getVector(i,j-1)[0];
	// pv_i[2] = inviscidFlowField.getVelocity().getVector(i,j-1)[1];
	// pv_i[3] = inviscidFlowField.getPressure().getScalar(i,j-1);
	// // Initially compute wall primative variables by linearization
 
	// FLOAT r0 = 1.0; 
	// FLOAT c0 = 1.0; 

	// pv_b[3] = pv_i[3]/* - r0 * c0 * (eta[0] * pv_i[1] + eta[1] * pv_i[2])/ETA*/;
	// pv_b[0] = pv_i[0] + ( pv_b[3] - pv_i[3] )/pow(c0,2);
	// pv_b[1] = pv_i[1] - eta[0] * (eta[0] * pv_i[1] + eta[1] * pv_i[2])/pow(ETA,2); 
	// pv_b[2] = pv_i[2] - eta[1] * (eta[0] * pv_i[1] + eta[1] * pv_i[2])/pow(ETA,2);

	// for (int n = 0; n<4; n++)
	// {
	// 	pv_g[n] = pv_b[n];		// Extrapolate to the ghost cell
	// }

	// inviscidFlowField.getDensity().getScalar(i,j) = pv_g[0];// rho
	// inviscidFlowField.getVelocity().getVector(i,j)[0] = pv_g[1];
	// inviscidFlowField.getVelocity().getVector(i,j)[1] = pv_g[2];
	// inviscidFlowField.getPressure().getScalar(i,j) = pv_g[3];

	// // // ******************** Debug
	inviscidFlowField.getDensity().getScalar(i,j) = inviscidFlowField.getDensity().getScalar(i,j-1);// rho
	inviscidFlowField.getVelocity().getVector(i,j)[0] = inviscidFlowField.getVelocity().getVector(i,j-1)[0];
	inviscidFlowField.getVelocity().getVector(i,j)[1] = - inviscidFlowField.getVelocity().getVector(i,j-1)[1];
	inviscidFlowField.getPressure().getScalar(i,j) = inviscidFlowField.getPressure().getScalar(i,j-1);


}

// TODO: 3D
void WallBoundaryConditionStencil::applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void WallBoundaryConditionStencil::applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void WallBoundaryConditionStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void WallBoundaryConditionStencil::applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void WallBoundaryConditionStencil::applyFrontWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void WallBoundaryConditionStencil::applyBackWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}


OutflowBoundaryConditionStencil::OutflowBoundaryConditionStencil(const Parameters & parameters):
    BoundaryStencil<InviscidFlowField>(parameters) 
    {

    	HeatCapacityRatio = parameters.flow.HeatCapacityRatio;
    	// Freestream velocity
    	FreeStreamVelocity[0] = parameters.flow.Ma;                   
    	FreeStreamVelocity[1] = 0.0;		
    	FreeStreamVelocity[2] = 0.0;     
    }
//

void OutflowBoundaryConditionStencil::applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j )
{}

void OutflowBoundaryConditionStencil::applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j )
{
	// // Get the transform metrices
	// FLOAT  xi[2], eta[2], XI, ETA; 
	
	// xi[0] = inviscidFlowField.getXi().getVector(i,j)[0];
	// xi[1] = inviscidFlowField.getXi().getVector(i,j)[1];
	// eta[0] = inviscidFlowField.getEta().getVector(i,j)[0];
	// eta[1] = inviscidFlowField.getEta().getVector(i,j)[1];

	// XI = sqrt(pow(xi[0],2)+pow(xi[1],2));
	// ETA = sqrt(pow(eta[0],2)+pow(eta[1],2));

	// FLOAT pv_fs[4],pv_g[4],pv_i[4],pv_b[4];
	// // Freestream variables:
	// pv_fs[0] = 1.0;						// rho
	// pv_fs[1] = FreeStreamVelocity[0];		// u
	// pv_fs[2] = FreeStreamVelocity[1];		// v
	// pv_fs[3] = 1.0/HeatCapacityRatio; 	// p
	// // Ghost variables;
	// pv_g[0] = inviscidFlowField.getDensity().getScalar(i,j);
	// pv_g[1] = inviscidFlowField.getVelocity().getVector(i,j)[0];
	// pv_g[2] = inviscidFlowField.getVelocity().getVector(i,j)[1];
	// pv_g[3] = inviscidFlowField.getPressure().getScalar(i,j);
	// // Interior variables
	// pv_i[0] = inviscidFlowField.getDensity().getScalar(i-1,j);
	// pv_i[1] = inviscidFlowField.getVelocity().getVector(i-1,j)[0];
	// pv_i[2] = inviscidFlowField.getVelocity().getVector(i-1,j)[1];
	// pv_i[3] = inviscidFlowField.getPressure().getScalar(i-1,j);
	// // Initially compute wall primative variables by linearization
 
	// FLOAT r0 = 1.0; 
	// FLOAT c0 = 1.0; 

	// if (pv_i[2] >= 1)		// supersonic outflow
	// {
	// 	for (int n = 0; n<4; n++)
	// 	{
	// 		pv_g[n] = pv_i[n];		// Ghost cell directly extrapolate from the interior point
	// 	}
	// }
	// else		// Subsonic
	// {
	// 	pv_b[3] = pv_i[3];
	// 	pv_b[0] = pv_fs[0] +  (pv_b[3] - pv_fs[3])/(pow(c0,2));
	// 	pv_b[1] = pv_fs[1] +  xi[0]/XI * (pv_fs[3] - pv_b[3])/(r0 * c0);
	// 	pv_b[2] = pv_fs[2] +  xi[1]/XI * (pv_fs[3] - pv_b[3])/(r0 * c0);

	// 	for (int n = 0; n<4; n++)
	// 	{
	// 		pv_g[n] = pv_b[n];		// Extrapolate to the ghost cell
	// 	}
	// }

	// // // PhysicsToComputationalDomain2D(inviscidFlowField, pv_g, HeatCapacityRatio, i, j);

	// inviscidFlowField.getDensity().getScalar(i,j) = pv_g[0];// rho
	// inviscidFlowField.getVelocity().getVector(i,j)[0] = pv_g[1];
	// inviscidFlowField.getVelocity().getVector(i,j)[1] = pv_g[2];
	// inviscidFlowField.getPressure().getScalar(i,j) = pv_g[3];

	inviscidFlowField.getDensity().getScalar(i,j) = inviscidFlowField.getDensity().getScalar(i-1,j);	// rho
	inviscidFlowField.getVelocity().getVector(i,j)[0] =inviscidFlowField.getVelocity().getVector(i-1,j)[0];
	inviscidFlowField.getVelocity().getVector(i,j)[1] = inviscidFlowField.getVelocity().getVector(i-1,j)[1];
	inviscidFlowField.getPressure().getScalar(i,j) = inviscidFlowField.getPressure().getScalar(i-1,j);


}


void OutflowBoundaryConditionStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j )
{}

void OutflowBoundaryConditionStencil::applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j )
{}

// TODO: 3D
void OutflowBoundaryConditionStencil::applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void OutflowBoundaryConditionStencil::applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void OutflowBoundaryConditionStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void OutflowBoundaryConditionStencil::applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void OutflowBoundaryConditionStencil::applyFrontWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void OutflowBoundaryConditionStencil::applyBackWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
