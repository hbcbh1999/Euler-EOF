#ifndef _INVISCID_SIMULATION_H_
#define _INVISCID_SIMULATION_H_


#include "../Simulation.h"
#include "../EulerSolver/InviscidFlowField.h"
#include "../stencils/PointCoordinateStencil.h"
#include "../stencils/DomainTransformStencil.h"
#include "../stencils/VTKGeoStencil.h"
#include "../stencils/UFGHStencil.h"
#include "../stencils/UFGHBoundaryStencil.h"
#include "../stencils/RoeStencil.h"
#include "../Iterators.h"
#include "../EulerSolver/InviscidGlobalBoundaryFactory.h"

class InviscidSimulation : public Simulation {
protected:
	InviscidFlowField &_inviscidFlowField;

	PointCoordinateStencil _pointCoordinateStencil;
	FieldIterator<InviscidFlowField> _pointCoordinateIterator;
	DomainTransformStencil _domainTransformStencil;
	FieldIterator<InviscidFlowField> _domainTransformIterator;
	GlobalBoundaryIterator<InviscidFlowField> _domainTransformBoundaryIterator; 

    InviscidGlobalBoundaryFactory _inviscidGlobalBoundaryFactory;
    GlobalBoundaryIterator<InviscidFlowField> _ufghBoundaryIterator;
    UFGHStencil _ufghStencil;
    FieldIterator<InviscidFlowField> _ufghIterator;
    RoeStencil _roeStencil;
    FieldIterator<InviscidFlowField> _roeIterator;
    GlobalBoundaryIterator<InviscidFlowField> _roeBoundaryIterator; 

	VTKGeoStencil _vtkGeoStencil;
	FieldIterator<InviscidFlowField> _vtkGeoIterator;


public:
	InviscidSimulation(Parameters &parameters, InviscidFlowField &inviscidFlowField):
	Simulation(parameters,inviscidFlowField),
	_inviscidFlowField(inviscidFlowField),

	_pointCoordinateStencil(parameters),
	_pointCoordinateIterator(_inviscidFlowField,parameters,_pointCoordinateStencil),
	_domainTransformStencil(parameters),
	_domainTransformIterator(_inviscidFlowField,
        parameters,_domainTransformStencil),
    _domainTransformBoundaryIterator(_inviscidFlowField, parameters, _domainTransformStencil),

	_inviscidGlobalBoundaryFactory(parameters),
	_ufghBoundaryIterator(_inviscidGlobalBoundaryFactory.getUFGHGlobalBoundaryIterator(_inviscidFlowField)),
	_ufghStencil(parameters),
	_ufghIterator(_inviscidFlowField,parameters,_ufghStencil),
	_roeStencil(parameters),
	_roeIterator(_inviscidFlowField,
        parameters,_roeStencil),
    _roeBoundaryIterator(_inviscidFlowField, parameters, _roeStencil),


	_vtkGeoStencil(parameters),
    _vtkGeoIterator(_inviscidFlowField,parameters,_vtkGeoStencil)
      
	{}

	void ApplyDomainTransformed(){
		_pointCoordinateIterator.iterate();
		_domainTransformIterator.iterate();
		_domainTransformBoundaryIterator.iterate();
	}

    void InviscidSolveTimeSteps()
    {
    	_ufghIterator.iterate();
    	_ufghBoundaryIterator.iterate();
    	_roeIterator.iterate();
    	_roeBoundaryIterator.iterate();
    }
    


    void plotGeoVTK(int timeStep){
      _vtkGeoIterator.iterate();
      _vtkGeoStencil.write(_inviscidFlowField,timeStep);
    }

};

#endif // _INVISCID_SIMULATION_H_
