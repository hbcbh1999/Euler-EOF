#include "UFGHBoundaryStencil.h"
 
 UFGHInletBoundaryStencil::UFGHInletBoundaryStencil(const Parameters & parameters):
    BoundaryStencil<InviscidFlowField>(parameters) 
    {
    
    HeatCapacityRatio = parameters.flow.HeatCapacityRatio;
    // Freestream condition (Non-dimensionlized)
    pv_fs[0] = 1.0;                                         //  rho
    pv_fs[1] = parameters.flow.Ma;                          //  u
    pv_fs[2] = 0.0;                                         //  v
    pv_fs[3] = 1.0/HeatCapacityRatio;       //  p
    }



// Charateristic boundary condition applied

void UFGHInletBoundaryStencil::applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j )
{	
    J = inviscidFlowField.getJ().getScalar(i,j);
    xi_x = inviscidFlowField.getXi().getVector(i,j)[0];
    xi_y = inviscidFlowField.getXi().getVector(i,j)[1];
    eta_x = inviscidFlowField.getEta().getVector(i,j)[0];
    eta_y = inviscidFlowField.getEta().getVector(i,j)[1];

    xi = sqrt(pow(xi_x,2)+pow(xi_y,2));
    eta = sqrt(pow(eta_x,2)+pow(eta_y,2));
	
	// Test
	// Read the interior cell

	for (int n = 0; n<4; n++)
	{
		U_g[n] = inviscidFlowField.getU().getFlux(i,j)[n];
		U_i[n] = inviscidFlowField.getU().getFlux(i+1,j)[n];
		U_b[n] = (U_g[0] + U_i[0])/2;
	}

	FLOAT r0 = U_b[0];
	FLOAT u0 = U_b[1]/U_b[0];
	FLOAT v0 = U_b[2]/U_b[0];
	FLOAT p0 = (HeatCapacityRatio -1) * ( U_b[3] - 0.5 * r0 * (pow(u0,2) + pow(v0,2)));
	FLOAT c0 = sqrt(HeatCapacityRatio * p0 / r0); 


	if (_parameters.flow.Ma >= 1)		// Supersonic fslow
	{ 	
		for (int n = 0; n<4; n++)
		{
			pv_b[n] = pv_fs[n];		// Read the free stream value to 
		}
	}
	else		// Subsonic fslow
	{
		// Caculate the pressure from the charateristic varibles relation
		// TODO: check it has been transformed or not. 
		pv_b[3] = 0.5*(pv_fs[3] + pv_i[3] + r0 * c0 * (xi_x * (pv_fs[1] - pv_i[1]) + xi_y * (pv_fs[2] - pv_i[2])))/xi;
		pv_b[0] = pv_fs[0] +  (pv_b[3] - pv_fs[3])/(pow(c0,2));
		pv_b[1] = pv_fs[1] +  xi_x/xi * (pv_fs[3] - pv_b[3])/(r0 * c0);
		pv_b[2] = pv_fs[2] +  xi_y/xi * (pv_fs[3] - pv_b[3])/(r0 * c0);
	}

	for (int n = 0; n<4; n++)
	{
		pv_g[n] = 2.0 * pv_b[n] -  pv_i[n];		// Extrapolate to the ghost cell
	}
	// State variables U in gost cell
	U_g[0] = pv_g[0];	
	U_g[1] = pv_g[0]*pv_g[1];		
	U_g[2] = pv_g[0]*pv_g[2];
	U_g[3] = 0.5 * pv_g[0] * (pow(pv_g[1], 2) + pow(pv_g[2], 2)) + pv_g[3]/(_parameters.flow.HeatCapacityRatio - 1);
	// Flux F in gost cell
	F_g[0] = U_g[0] * U_g[1];
	F_g[1] = U_g[0] * pow(U_g[1]/U_g[0],2) + pv_g[3];
	F_g[2] = U_g[0] * U_g[1] * U_g[2];
	F_g[3] = U_g[1] * (U_g[3] + pv_g[3]);

	// Flux G in gost cell
	G_g[0] = U_g[0] * U_g[2];
	G_g[1] = U_g[0] * pow(U_g[1]/U_g[0],2) + pv_g[3];
	G_g[2] = U_g[0] * U_g[1] * U_g[2];
	G_g[3] = U_g[2] * (U_g[3] + pv_g[3]);

	// Apply domain transformation:
	for (int n = 0; n<4; n++)
	{
		inviscidFlowField.getUhat().getFlux(i,j)[n] = J * U_g[n] ;
		inviscidFlowField.getFhat().getFlux(i,j)[n] = J * (xi_x * F_g[n] + xi_y * G_g[n]);
		inviscidFlowField.getGhat().getFlux(i,j)[n] = J * (eta_x * F_g[n] + xi_y * G_g[n]);
	}
}

// TODO: implement the inlet condition from other wall
void UFGHInletBoundaryStencil::applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j )
{}

void UFGHInletBoundaryStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j )
{}

void UFGHInletBoundaryStencil::applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j )
{}

// TODO: 3D
void UFGHInletBoundaryStencil::applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void UFGHInletBoundaryStencil::applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void UFGHInletBoundaryStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void UFGHInletBoundaryStencil::applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void UFGHInletBoundaryStencil::applyFrontWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void UFGHInletBoundaryStencil::applyBackWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}



UFGHWallBoundaryStencil::UFGHWallBoundaryStencil(const Parameters & parameters):
BoundaryStencil<InviscidFlowField>(parameters) {

	HeatCapacityRatio = parameters.flow.HeatCapacityRatio;
    // Freestream condition (Non-dimensionlized)
    pv_fs[0] = 1.0;                                         //  rho
    pv_fs[1] = _parameters.flow.Ma;                          //  u
    pv_fs[2] = 0.0;                                         //  v
    pv_fs[3] = 1.0/HeatCapacityRatio;       //  p
}

void UFGHWallBoundaryStencil::applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j )
{}

void UFGHWallBoundaryStencil::applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j )
{}

void UFGHWallBoundaryStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j )
{	
	J = inviscidFlowField.getJ().getScalar(i,j);
    xi_x = inviscidFlowField.getXi().getVector(i,j)[0];
    xi_y = inviscidFlowField.getXi().getVector(i,j)[1];
    eta_x = inviscidFlowField.getEta().getVector(i,j)[0];
    eta_y = inviscidFlowField.getEta().getVector(i,j)[1];

    xi = sqrt(pow(xi_x,2)+pow(xi_y,2));
    eta = sqrt(pow(eta_x,2)+pow(eta_y,2));
    // Test
	for (int n = 0; n<4; n++)
	{
		U_g[n] = inviscidFlowField.getU().getFlux(i,j)[n];
		U_i[n] = inviscidFlowField.getU().getFlux(i,j+1)[n];
		U_b[n] = (U_g[0] + U_i[0])/2;
	}

	FLOAT r0 = U_b[0];
	FLOAT u0 = U_b[1]/U_b[0];
	FLOAT v0 = U_b[2]/U_b[0];
	FLOAT p0 = (HeatCapacityRatio -1) * ( U_b[3] - 0.5 * r0 * (pow(u0,2) + pow(v0,2)));
	FLOAT c0 = sqrt(HeatCapacityRatio * p0 / r0); 
	
	for (int n = 0; n<4; n++)
	{
		pv_i[n] = inviscidFlowField.getU().getFlux(i,j+1)[n];		// Read the interior cell
	}

	pv_b[3] = pv_i[3] - r0 * c0 * (eta_x * pv_i[1] + eta_y * pv_i[2])/eta;
	pv_b[0] = pv_i[0] + ( pv_b[3] - pv_i[3] )/pow(c0,2);
	pv_b[1] = pv_i[1] - eta_x * (eta_x * pv_i[1] + eta_y * pv_i[2])/pow(eta,2); 
	pv_b[2] = pv_i[2] - eta_y * (eta_x * pv_i[1] + eta_y * pv_i[2])/pow(eta,2);

	for (int n = 0; n<4; n++)
	{
		pv_g[n] = 2.0 * pv_b[n] -  pv_i[n];		// Extrapolate to the ghost cell
	}

	// State variables U
	U_g[0] = pv_g[0];	
	U_g[1] = pv_g[0]*pv_g[1];		
	U_g[2] = pv_g[0]*pv_g[2];
	U_g[3] = 0.5 * pv_g[0] * (pow(pv_g[1], 2) + pow(pv_g[2], 2)) + pv_g[3]/(_parameters.flow.HeatCapacityRatio - 1);
	// Flux F
	F_g[0] = U_g[0] * U_g[1];
	F_g[1] = U_g[0] * pow(U_g[1]/U_g[0],2) + pv_g[3];
	F_g[2] = U_g[0] * U_g[1] * U_g[2];
	F_g[3] = U_g[1] * (U_g[3] + pv_g[3]);

	// Flux G
	G_g[0] = U_g[0] * U_g[2];
	G_g[1] = U_g[0] * pow(U_g[1]/U_g[0],2) + pv_g[3];
	G_g[2] = U_g[0] * U_g[1] * U_g[2];
	G_g[3] = U_g[2] * (U_g[3] + pv_g[3]);

	// Apply domain transformation:
	for (int n = 0; n<4; n++)
	{
		inviscidFlowField.getUhat().getFlux(i,j)[n] = J * U_g[n] ;
		inviscidFlowField.getFhat().getFlux(i,j)[n] = J * (xi_x * F_g[n] + xi_y * G_g[n]);
		inviscidFlowField.getGhat().getFlux(i,j)[n] = J * (eta_x * F_g[n] + xi_y * G_g[n]);
	}
}

void UFGHWallBoundaryStencil::applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j )
{
	J = inviscidFlowField.getJ().getScalar(i,j);
    xi_x = inviscidFlowField.getXi().getVector(i,j)[0];
    xi_y = inviscidFlowField.getXi().getVector(i,j)[1];
    eta_x = inviscidFlowField.getEta().getVector(i,j)[0];
    eta_y = inviscidFlowField.getEta().getVector(i,j)[1];

    xi = sqrt(pow(xi_x,2)+pow(xi_y,2));
    eta = sqrt(pow(eta_x,2)+pow(eta_y,2));

	// Test
	for (int n = 0; n<4; n++)
	{
		U_g[n] = inviscidFlowField.getU().getFlux(i,j)[n];
		U_i[n] = inviscidFlowField.getU().getFlux(i,j-1)[n];
		U_b[n] = (U_g[0] + U_i[0])/2;
	}

	FLOAT r0 = U_b[0];
	FLOAT u0 = U_b[1]/U_b[0];
	FLOAT v0 = U_b[2]/U_b[0];
	FLOAT p0 = (HeatCapacityRatio -1) * ( U_b[3] - 0.5 * r0 * (pow(u0,2) + pow(v0,2)));
	FLOAT c0 = sqrt(HeatCapacityRatio * p0 / r0); 

	for (int n = 0; n<4; n++)
	{
		pv_i[n] = inviscidFlowField.getU().getFlux(i,j-1)[n];		// Read the interior cell
	}

	pv_b[3] = pv_i[3] + r0 * c0 * (eta_x * pv_i[1] + eta_y * pv_i[2])/eta;
	pv_b[0] = pv_i[0] + ( pv_b[3] - pv_i[3] )/pow(c0,2);
	pv_b[1] = pv_i[1] - eta_x * (eta_x * pv_i[1] + eta_y * pv_i[2])/pow(eta,2); 
	pv_b[2] = pv_i[2] - eta_y * (eta_x * pv_i[1] + eta_y * pv_i[2])/pow(eta,2);

	for (int n = 0; n<4; n++)
	{
		pv_g[n] = 2.0 * pv_b[n] -  pv_i[n];		// Extrapolate to the ghost cell
	}

	// State variables U
	U_g[0] = pv_g[0];	
	U_g[1] = pv_g[0]*pv_g[1];		
	U_g[2] = pv_g[0]*pv_g[2];
	U_g[3] = 0.5 * pv_g[0] * (pow(pv_g[1], 2) + pow(pv_g[2], 2)) + pv_g[3]/(_parameters.flow.HeatCapacityRatio - 1);
	// Flux F
	F_g[0] = U_g[0] * U_g[1];
	F_g[1] = U_g[0] * pow(U_g[1]/U_g[0],2) + pv_g[3];
	F_g[2] = U_g[0] * U_g[1] * U_g[2];
	F_g[3] = U_g[1] * (U_g[3] + pv_g[3]);

	// Flux G
	G_g[0] = U_g[0] * U_g[2];
	G_g[1] = U_g[0] * pow(U_g[1]/U_g[0],2) + pv_g[3];
	G_g[2] = U_g[0] * U_g[1] * U_g[2];
	G_g[3] = U_g[2] * (U_g[3] + pv_g[3]);

	// Apply domain transformation:
	for (int n = 0; n<4; n++)
	{
		inviscidFlowField.getUhat().getFlux(i,j)[n] = J * U_g[n] ;
		inviscidFlowField.getFhat().getFlux(i,j)[n] = J * (xi_x * F_g[n] + xi_y * G_g[n]);
		inviscidFlowField.getGhat().getFlux(i,j)[n] = J * (eta_x * F_g[n] + xi_y * G_g[n]);
	}
}

// TODO: 3D
void UFGHWallBoundaryStencil::applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void UFGHWallBoundaryStencil::applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void UFGHWallBoundaryStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void UFGHWallBoundaryStencil::applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void UFGHWallBoundaryStencil::applyFrontWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void UFGHWallBoundaryStencil::applyBackWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}


UFGHOutflowBoundaryStencil::UFGHOutflowBoundaryStencil(const Parameters & parameters):
    BoundaryStencil<InviscidFlowField>(parameters) {
    HeatCapacityRatio = parameters.flow.HeatCapacityRatio;
    // Freestream condition (Non-dimensionlized)
    pv_fs[0] = 1.0;                                         //  rho
    pv_fs[1] = _parameters.flow.Ma;                          //  u
    pv_fs[2] = 0.0;                                         //  v
    pv_fs[3] = 1.0/HeatCapacityRatio;       //  p
    }
//

void UFGHOutflowBoundaryStencil::applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j )
{}

void UFGHOutflowBoundaryStencil::applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j )
{
    J = inviscidFlowField.getJ().getScalar(i,j);
    xi_x = inviscidFlowField.getXi().getVector(i,j)[0];
    xi_y = inviscidFlowField.getXi().getVector(i,j)[1];
    eta_x = inviscidFlowField.getEta().getVector(i,j)[0];
    eta_y = inviscidFlowField.getEta().getVector(i,j)[1];

    xi = sqrt(pow(xi_x,2)+pow(xi_y,2));
    eta = sqrt(pow(eta_x,2)+pow(eta_y,2));

    // Test
	for (int n = 0; n<4; n++)
	{
		U_g[n] = inviscidFlowField.getU().getFlux(i,j)[n];
		U_i[n] = inviscidFlowField.getU().getFlux(i-1,j)[n];
		U_b[n] = (U_g[0] + U_i[0])/2;
	}
	// linearized primative value on the boundary
	FLOAT r0 = U_b[0];
	FLOAT u0 = U_b[1]/U_b[0];
	FLOAT v0 = U_b[2]/U_b[0];
	FLOAT p0 = (HeatCapacityRatio -1) * ( U_b[3] - 0.5 * r0 * (pow(u0,2) + pow(v0,2)));
	FLOAT c0 = sqrt(HeatCapacityRatio * p0 / r0); 

	for (int n = 0; n<4; n++)
	{
		pv_i[n] = inviscidFlowField.getU().getFlux(i-1,j)[n];		// Read the interior cell
	} 

	if (pv_i[2] >= 1)		// subsonic outflow
	{
		for (int n = 0; n<4; n++)
		{
			pv_g[n] = pv_i[n];		// Ghost cell directly extrapolate from the interior point
		}
		// State variables U
		U_g[0] = pv_g[0];	
		U_g[1] = pv_g[0] * pv_g[1];		
		U_g[2] = pv_g[0] * pv_g[2];
		U_g[3] = 0.5 * pv_g[0] * (pow(pv_g[1], 2) + pow(pv_g[2], 2)) + pv_g[3]/(_parameters.flow.HeatCapacityRatio - 1);
	}
	else		// Subsonic
	{
		pv_b[3] = pv_i[3];
		pv_b[0] = pv_fs[0] +  (pv_b[3] - pv_fs[3])/(pow(c0,2));
		pv_b[1] = pv_fs[1] +  xi_x/xi * (pv_fs[3] - pv_b[3])/(r0 * c0);
		pv_b[2] = pv_fs[2] +  xi_y/xi * (pv_fs[3] - pv_b[3])/(r0 * c0);

		for (int n = 0; n<4; n++)
		{
			pv_g[n] = 2.0 * pv_b[n] -  pv_i[n];		// Extrapolate to the ghost cell
		}

		// State variables U
		U_g[0] = pv_g[0];	
		U_g[1] = pv_g[0] * pv_g[1];		
		U_g[2] = pv_g[0] * pv_g[2];
		U_g[3] = 0.5 * pv_g[0] * (pow(pv_g[1], 2) + pow(pv_g[2], 2)) + pv_g[3]/(_parameters.flow.HeatCapacityRatio - 1);
	}

	// Flux F
	F_g[0] = U_g[0] * U_g[1];
	F_g[1] = U_g[0] * pow(U_g[1]/U_g[0],2) + pv_g[3];
	F_g[2] = U_g[0] * U_g[1] * U_g[2];
	F_g[3] = U_g[1] * (U_g[3] + pv_g[3]);

	// Flux G
	G_g[0] = U_g[0] * U_g[2];
	G_g[1] = U_g[0] * pow(U_g[1]/U_g[0],2) + pv_g[3];
	G_g[2] = U_g[0] * U_g[1] * U_g[2];
	G_g[3] = U_g[2] * (U_g[3] + pv_g[3]);

	// Apply domain transformation
	for (int n = 0; n<4; n++)
	{
		inviscidFlowField.getUhat().getFlux(i,j)[n] = J * U_g[n] ;
		inviscidFlowField.getFhat().getFlux(i,j)[n] = J * (xi_x * F_g[n] + xi_y * G_g[n]);
		inviscidFlowField.getGhat().getFlux(i,j)[n] = J * (eta_x * F_g[n] + xi_y * G_g[n]);
	}
}

void UFGHOutflowBoundaryStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j )
{}

void UFGHOutflowBoundaryStencil::applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j )
{}

// TODO: 3D
void UFGHOutflowBoundaryStencil::applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void UFGHOutflowBoundaryStencil::applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void UFGHOutflowBoundaryStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void UFGHOutflowBoundaryStencil::applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void UFGHOutflowBoundaryStencil::applyFrontWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}
void UFGHOutflowBoundaryStencil::applyBackWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{}