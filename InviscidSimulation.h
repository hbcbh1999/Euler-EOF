#ifndef _INVISCID_SIMULATION_H_
#define _INVISCID_SIMULATION_H_


#include "../Simulation.h"
#include "../InviscidFlowField.h"
#include "../Iterators.h"



class InviscidSimulation : public Simulation {
protected:
	InviscidFlowField &_InviscidFlowField;

	DomainTransformStencil _domainTransformStencil;
	FieldIterator<InviscidFlowField> _domainTransformIterator;

public:
	InviscidSimulation(Parameters &parameters, InviscidFlowField &InviscidFlowField):
	Simulation(parameters,InviscidFlowField),
	_InviscidFlowField(InviscidFlowField),
	_domainTransformStencil(parameters),
	_domainTransformIterator(InviscidFlowField,parameters,_domainTransformStencil)

}
