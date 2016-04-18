#include "InviscidGlobalBoundaryFactory.h"

InviscidGlobalBoundaryFactory::InviscidGlobalBoundaryFactory(Parameters & parameters):
    _parameters(parameters){
    // The parameters will be modified, and therefore are not declared as constants.

    // All stencils are created, disregarding wether they will be used or not. This is less
    // complicated and doesn't seem that costly

    _inlet = new UFGHInletBoundaryStencil(parameters);

    _wall = new UFGHWallBoundaryStencil(parameters);

    _outflow = new UFGHOutflowBoundaryStencil(parameters);

    // Then, assign them according to the scenario
    std::string scenario = parameters.simulation.scenario;

    if (scenario == "slope channel"){
        // To the left, we have the input
        _UFGHBoundaryStencil[0] = _inlet;

        // To the right, there is an outflow boundary
        _UFGHBoundaryStencil[1] = _outflow;

        // The other walls are moving walls
        for (int i = 2; i < 6; i++){
            _UFGHBoundaryStencil[i] = _wall;
        }

        parameters.walls.typeLeft   = DIRICHLET;
        parameters.walls.typeRight  = NEUMANN;
        parameters.walls.typeBottom = DIRICHLET;
        parameters.walls.typeTop    = DIRICHLET;
        parameters.walls.typeFront  = DIRICHLET;
        parameters.walls.typeBack   = DIRICHLET;
    } else {
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
                                      *(_UFGHBoundaryStencil[0]), *(_UFGHBoundaryStencil[1]),
                                      *(_UFGHBoundaryStencil[2]), *(_UFGHBoundaryStencil[3]),
                                      1, 0);
     }
    return GlobalBoundaryIterator<InviscidFlowField>(inviscidFlowField, _parameters,
                                  *(_UFGHBoundaryStencil[0]), *(_UFGHBoundaryStencil[1]),
                                  *(_UFGHBoundaryStencil[2]), *(_UFGHBoundaryStencil[3]),
                                  *(_UFGHBoundaryStencil[4]), *(_UFGHBoundaryStencil[5]),
                                  1, 0);
}
