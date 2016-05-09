#include "GodunovStencil.h"

GodunovStencil::GodunovStencil ( const Parameters & parameters ) : FieldStencil<InviscidFlowField> ( parameters ) {
	dt = 0.001;
	dx = parameters.geometry.lengthX/parameters.geometry.sizeX;
	dy = parameters.geometry.lengthX/parameters.geometry.sizeX;
}

void GodunovStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j)
{
	FLOAT dtdx = 0.02;
	FLOAT dtdy = 0.02;
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

void GodunovStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{
	// TODO: 3D case
}
