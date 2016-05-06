#include "InviscidGlobalBoundaryFactory.h"

InviscidGlobalBoundaryFactory::InviscidGlobalBoundaryFactory(Parameters & parameters):
    _parameters(parameters){
    // The parameters will be modified, and therefore are not declared as constants.

    // All stencils are created, disregarding wether they will be used or not. This is less
    // complicated and doesn't seem that costly

    _inlet = new InletBoundaryConditionStencil(parameters);

    _wall = new WallBoundaryConditionStencil(parameters);

    _outflow = new OutflowBoundaryConditionStencil(parameters);

    // Then, assign them according to the scenario
    std::string scenario = parameters.simulation.scenario;

    if (scenario == "channel"){
        // To the left, we have the input
        _BoundaryConditionStencil[0] = _inlet;

        // To the right, there is an outflow boundary
        _BoundaryConditionStencil[1] = _outflow;

        // The other walls are moving walls
        for (int i = 2; i < 6; i++){
            _BoundaryConditionStencil[i] = _wall;
        }
    }
    else if (scenario == "shock tube")
    {
        for (int i = 0; i < 6; i++){
            _BoundaryConditionStencil[i] = _wall;
        }
    } 
    else 
    {
        handleError(1, "Scenario not recognized");
    }
}

InviscidGlobalBoundaryFactory::~InviscidGlobalBoundaryFactory()
{
    delete _inlet;

    delete _wall;

    delete _outflow;
}

GlobalBoundaryIterator<InviscidFlowField> InviscidGlobalBoundaryFactory::
    getUFGHGlobalBoundaryIterator(InviscidFlowField & inviscidFlowField){
    if (_parameters.geometry.dim == 2){
        return GlobalBoundaryIterator<InviscidFlowField>(inviscidFlowField, _parameters,
                                      *(_BoundaryConditionStencil[0]), *(_BoundaryConditionStencil[1]),
                                      *(_BoundaryConditionStencil[2]), *(_BoundaryConditionStencil[3]),
                                      1, 0);
     }
    return GlobalBoundaryIterator<InviscidFlowField>(inviscidFlowField, _parameters,
                                  *(_BoundaryConditionStencil[0]), *(_BoundaryConditionStencil[1]),
                                  *(_BoundaryConditionStencil[2]), *(_BoundaryConditionStencil[3]),
                                  *(_BoundaryConditionStencil[4]), *(_BoundaryConditionStencil[5]),
                                  1, 0);
}
