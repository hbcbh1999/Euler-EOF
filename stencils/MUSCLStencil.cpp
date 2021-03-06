#include "MUSCLStencil.h"
#include "../EulerSolver/Riemann/RoeSolver.cpp"
MUSCLStencil::MUSCLStencil ( const Parameters & parameters ) : FieldStencil<InviscidFlowField> ( parameters ) {
	dt = 0.001;
	dx = parameters.geometry.lengthX/parameters.geometry.sizeX;
	dy = parameters.geometry.lengthX/parameters.geometry.sizeX;
	HeatCapacityRatio = parameters.flow.HeatCapacityRatio;
}

void MUSCLStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j)
{
    reconstructFlux(inviscidFlowField,i,j);
	rotateUFGH(inviscidFlowField, i, j);

	FLOAT dtdx = 0.01;
	FLOAT dtdy = 0.01;
	if (i == 1 || j == 1)
	{

	}
	else
	{
		// std::cout << dt << "\n";
		for (int n = 0; n < 4; n++)
		{
			U_n[n] = inviscidFlowField.getUhat().getFlux(i,j)[n];
			F_left[n] = inviscidFlowField.getFmid().getFlux(i-1,j)[n];
			F_right[n] = inviscidFlowField.getFmid().getFlux(i,j)[n];
			G_top[n] = inviscidFlowField.getGmid().getFlux(i,j)[n];
			G_bottom[n] = inviscidFlowField.getGmid().getFlux(i,j-1)[n];
			// Update at next time step
			U_np1[n] = U_n[n] + dtdx*(F_left[n] - F_right[n]) + dtdy*(G_bottom[n] - G_top[n]);
			inviscidFlowField.getUhat().getFlux(i,j)[n] = U_np1[n];
		}
	}

}

void MUSCLStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{
	// TODO: 3D case
}


void MUSCLStencil::rotateUFGH(InviscidFlowField & inviscidFlowField, int i, int j)
{
    std::array<FLOAT, 4> U_Local,U_Right,U_Top;
    std::array<FLOAT, 4> F_Local,F_Right;
    std::array<FLOAT, 4> G_Local,G_Top;
    std::array<FLOAT, 4> H_Local,H_Front;
    std::array<FLOAT, 4> F_mid, G_mid, H_mid;

    FLOAT omega = 0.0;

    // Reconstruction
    for ( int n = 0; n<4; n++)
    {
        U_Local[n] = inviscidFlowField.getUhat().getFlux(i,j)[n];
        U_Right[n] = inviscidFlowField.getUhat().getFlux(i+1,j)[n];
        U_Top[n] = inviscidFlowField.getUhat().getFlux(i,j+1)[n];
        U_Left[n] = inviscidFlowField.getUhat().getFlux(i-1,j)[n];
        U_Bottom[n] = inviscidFlowField.getUhat().getFlux(i,j-1)[n];

        Delta[n] = 0.5 * (1+omega) * (U_Local[n]-U_Left[n])+0.5*(1-omega) * (U_Right[n] - U_Local[n]);

        U_Local_L[n] = U_Local[n] - 0.5 * Delta[n]; // Value on the left interface of the local cell
        U_Local_R[n] = U_Local[n] + 0.5 * Delta[n]; // Value on the right interface of the intercell
    }


    F_mid = RoeSolver(U_Local, U_Right, F_Local, F_Right, HeatCapacityRatio);

    // // This function treat Riemann problem on x, y, z direction by changing the sequency of the varible in the outside input. When calculate flux G on y direction, we pass U = [rho, v, u, E] from outside but assign in the function as [rho, u, v, E].


    std::iter_swap(U_Local.begin()+1,U_Local.begin()+2);
    std::iter_swap(U_Top.begin()+1,U_Top.begin()+2);

    std::iter_swap(G_Local.begin()+1,G_Local.begin()+2);
    std::iter_swap(G_Top.begin()+1,G_Top.begin()+2);

    G_mid = RoeSolver(U_Local, U_Top, G_Local, G_Top, HeatCapacityRatio);

    // Change [rho v u E] back to [rho u v E]
    std::iter_swap(G_mid.begin()+1,G_mid.begin()+2);


    for ( int n = 0; n<4; n++)
    {
        inviscidFlowField.getFmid().getFlux(i,j)[n] = F_mid[n];
        inviscidFlowField.getGmid().getFlux(i,j)[n] = G_mid[n];
    }

}

void MUSCLStencil::rotateUFGH(InviscidFlowField & inviscidFlowField, int i, int j, int k)
{
    //TODO:3D
}
