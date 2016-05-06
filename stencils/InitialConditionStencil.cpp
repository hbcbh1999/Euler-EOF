#include "InitialConditionStencil.h"

InitialConditionStencil::InitialConditionStencil (const Parameters & parameters) :
    FieldStencil<InviscidFlowField> (parameters)
{
    	HeatCapacityRatio = parameters.flow.HeatCapacityRatio;
        FreeStreamVelocity = parameters.flow.Ma;
}

void InitialConditionStencil::apply (InviscidFlowField & inviscidFlowField, int i, int j)
{
    inviscidFlowField.getDensity().getScalar(i, j) = 0.125;
    inviscidFlowField.getVelocity().getVector(i, j)[0] = 0.0;
    inviscidFlowField.getVelocity().getVector(i, j)[1] = 0.0;
    inviscidFlowField.getPressure().getScalar(i, j) = 0.1;

    // std::cout << inviscidFlowField.getDensity().getScalar(i, j) << "\n";
}

void InitialConditionStencil::apply (InviscidFlowField & inviscidFlowField, int i, int j, int k)
{
// TODO: 3D    
}

