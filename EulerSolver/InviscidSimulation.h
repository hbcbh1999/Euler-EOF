#ifndef _INVISCID_SIMULATION_H_
#define _INVISCID_SIMULATION_H_


#include "../Simulation.h"
#include "../EulerSolver/InviscidFlowField.h"
#include "../stencils/PointCoordinateStencil.h"
#include "../stencils/DomainTransformStencil.h"
#include "../stencils/VTKGeoStencil.h"
#include "../Iterators.h"

class InviscidSimulation : public Simulation {
protected:
	InviscidFlowField &_inviscidFlowField;
	PointCoordinateStencil _pointCoordinateStencil;
	FieldIterator<InviscidFlowField> _pointCoordinateIterator;
	DomainTransformStencil _domainTransformStencil;
	FieldIterator<InviscidFlowField> _domainTransformIterator;
	VTKGeoStencil _vtkGeoStencil;
	FieldIterator<InviscidFlowField> _vtkGeoIterator;

public:
	InviscidSimulation(Parameters &parameters, InviscidFlowField &inviscidFlowField):
	Simulation(parameters,inviscidFlowField),
	_inviscidFlowField(inviscidFlowField),
	_pointCoordinateStencil(parameters),
	_pointCoordinateIterator(inviscidFlowField,parameters,_pointCoordinateStencil),
	_domainTransformStencil(parameters),
	_domainTransformIterator(inviscidFlowField,parameters,_domainTransformStencil),
	_vtkGeoStencil(parameters),
    _vtkGeoIterator(inviscidFlowField,parameters,_vtkGeoStencil)
      
	{}

	void loadPointCoordinate(){
		_pointCoordinateIterator.iterate();
	}

	void computeTransformMetrics(){
		_domainTransformIterator.iterate();
	}

	void plotGeoVTK(int timeStep){
      _vtkGeoIterator.iterate();
      _vtkGeoStencil.write(_inviscidFlowField,timeStep);
    }

};

#endif // _INVISCID_SIMULATION_H_
