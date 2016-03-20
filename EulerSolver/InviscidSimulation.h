#ifndef _INVISCID_SIMULATION_H_
#define _INVISCID_SIMULATION_H_


#include "../Simulation.h"
#include "../EulerSolver/InviscidFlowField.h"
#include "../stencils/DomainTransformStencil.h"
#include "../Iterators.h"

class InviscidSimulation : public Simulation {
protected:
	InviscidFlowField &_inviscidFlowField;

	DomainTransformStencil _domainTransformStencil;
	FieldIterator<InviscidFlowField> _domainTransformIterator;

public:
	InviscidSimulation(Parameters &parameters, InviscidFlowField &inviscidFlowField):
	Simulation(parameters,inviscidFlowField),
	_inviscidFlowField(inviscidFlowField),
	_domainTransformStencil(parameters),
	_domainTransformIterator(inviscidFlowField,parameters,_domainTransformStencil)
	{}

	void computeTransformMetrics(){
		_domainTransformIterator.iterate();
	}

virtual void plotVTK(int timeStep){
      VTKStencil _vtkStencil(_parameters);
      FieldIterator<FlowField> _vtkIterator(_inviscidFlowField,_parameters,_vtkStencil);
      _vtkIterator.iterate();
      _vtkStencil.write(_inviscidFlowField,timeStep);
    }

};

#endif // _INVISCID_SIMULATION_H_
