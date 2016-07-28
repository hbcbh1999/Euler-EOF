#include "MUSCLStencil.h"
#include "../EulerSolver/Riemann/RoeSolver.cpp"
MUSCLStencil::MUSCLStencil ( const Parameters & parameters ) : FieldStencil<InviscidFlowField> ( parameters ) {
	HeatCapacityRatio = parameters.flow.HeatCapacityRatio;
}

void MUSCLStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j)
{
    computeFlux(inviscidFlowField,i,j);

	FLOAT dtdx = _parameters.timestep.dt;
	FLOAT dtdy = _parameters.timestep.dt;
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


void MUSCLStencil::computeFlux(InviscidFlowField & inviscidFlowField, int i, int j)
{
    std::array<FLOAT, 4> U_i_j_right,U_ip1_j_left,U_i_j_top, U_i_jp1_bottom;
    std::array<FLOAT, 4> F_i_j_right,F_ip1_j_left;
    std::array<FLOAT, 4> G_i_j_top,G_i_jp1_bottom;
    std::array<FLOAT, 4> F_mid, G_mid;

    for ( int n = 0; n<4; n++)
    {
        U_i_j_right[n] = inviscidFlowField.getUhatRight().getFlux(i,j)[n];
        U_ip1_j_left[n] = inviscidFlowField.getUhatLeft().getFlux(i+1,j)[n];

        U_i_j_top[n] = inviscidFlowField.getUhatTop().getFlux(i,j)[n];
        U_i_jp1_bottom[n] = inviscidFlowField.getUhatBottom().getFlux(i,j+1)[n];

        F_i_j_right[n] = inviscidFlowField.getFhatRight().getFlux(i,j)[n];
        F_ip1_j_left[n] = inviscidFlowField.getFhatLeft().getFlux(i+1,j)[n];

        G_i_j_top[n] = inviscidFlowField.getGhatTop().getFlux(i,j)[n];
        G_i_jp1_bottom[n] = inviscidFlowField.getGhatBottom().getFlux(i,j+1)[n];
    }

    F_mid = RoeSolver(U_i_j_right, U_ip1_j_left, F_i_j_right, F_ip1_j_left, HeatCapacityRatio);

    // // This function treat Riemann problem on x, y, z direction by changing the sequency of the varible in the outside input. When calculate flux G on y direction, we pass U = [rho, v, u, E] from outside but assign in the function as [rho, u, v, E].
    std::iter_swap(U_i_j_top.begin()+1,U_i_j_top.begin()+2);
    std::iter_swap(U_i_jp1_bottom.begin()+1,U_i_jp1_bottom.begin()+2);

    std::iter_swap(G_i_j_top.begin()+1,G_i_j_top.begin()+2);
    std::iter_swap(G_i_jp1_bottom.begin()+1,G_i_jp1_bottom.begin()+2);

    G_mid = RoeSolver(U_i_j_top, U_i_jp1_bottom, G_i_j_top, G_i_jp1_bottom, HeatCapacityRatio);

    // Change [rho v u E] back to [rho u v E]
    std::iter_swap(G_mid.begin()+1,G_mid.begin()+2);


    for ( int n = 0; n<4; n++)
    {
        inviscidFlowField.getFmid().getFlux(i,j)[n] = F_mid[n];
        inviscidFlowField.getGmid().getFlux(i,j)[n] = G_mid[n];
    }

}

void MUSCLStencil::computeFlux(InviscidFlowField & inviscidFlowField, int i, int j, int k)
{
    //TODO:3D
}
