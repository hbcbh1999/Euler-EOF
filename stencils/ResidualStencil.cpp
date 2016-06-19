#include "ResidualStencil.h"

ResidualStencil::ResidualStencil ( const Parameters & parameters ) : FieldStencil<InviscidFlowField> ( parameters ) {}

void ResidualStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j)
{
	if (i>1 && j>1)
	{
		FLOAT RhoRelRes = inviscidFlowField.getRhoRelRes().getScalar(i,j);
		if (RhoRelRes > MaxRhoRelRes)
		{
			MaxRhoRelRes = RhoRelRes;
		}
	}


}

void ResidualStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

	// TODO: 3D case
}

void ResidualStencil::reset()
{
	MaxRhoRelRes = 0;
}

FLOAT ResidualStencil::getMaxResidual() {
    return MaxRhoRelRes;
}