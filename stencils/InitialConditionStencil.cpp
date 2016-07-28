#include "InitialConditionStencil.h"

InitialConditionStencil::InitialConditionStencil (const Parameters & parameters) :
    FieldStencil<InviscidFlowField> (parameters)
{
    	HeatCapacityRatio = parameters.flow.HeatCapacityRatio;
        FreeStreamVelocity = parameters.flow.Ma;
        sizeX = parameters.geometry.sizeX;
        sizeY = parameters.geometry.sizeY;
        scenario = parameters.simulation.scenario;
}

void InitialConditionStencil::apply (InviscidFlowField & inviscidFlowField, int i, int j)
{

    if (scenario == "channel")
    {
        // if (FreeStreamVelocity < 1)
        // {
            inviscidFlowField.getDensity().getScalar(i, j) = 1.0;
            inviscidFlowField.getVelocity().getVector(i, j)[0] = FreeStreamVelocity;
            inviscidFlowField.getVelocity().getVector(i, j)[1] = 0.0;
            inviscidFlowField.getPressure().getScalar(i, j) = 1/HeatCapacityRatio;
        // }
        // else
        // {
            // inviscidFlowField.getDensity().getScalar(i, j) = 0.125;
            // inviscidFlowField.getVelocity().getVector(i, j)[0] = 0.0;
            // inviscidFlowField.getVelocity().getVector(i, j)[1] = 0.0;
            // inviscidFlowField.getPressure().getScalar(i, j) = 0.1;
        // }
    }    
    if (scenario == "shock tube")
    {
        if (i < sizeX/2)
        {
            inviscidFlowField.getDensity().getScalar(i, j) = 1.0;
            inviscidFlowField.getVelocity().getVector(i, j)[0] = 0.0;
            inviscidFlowField.getVelocity().getVector(i, j)[1] = 0.0;
            inviscidFlowField.getPressure().getScalar(i, j) = 1.0;
        }
        else
        {
            inviscidFlowField.getDensity().getScalar(i, j) = 0.125;
            inviscidFlowField.getVelocity().getVector(i, j)[0] = 0.0;
            inviscidFlowField.getVelocity().getVector(i, j)[1] = 0.0;
            inviscidFlowField.getPressure().getScalar(i, j) = 0.1;
        }
    }
}

void InitialConditionStencil::apply (InviscidFlowField & inviscidFlowField, int i, int j, int k)
{
// TODO: 3D    
}

