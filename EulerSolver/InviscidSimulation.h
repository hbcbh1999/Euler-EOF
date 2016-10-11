#ifndef _INVISCID_SIMULATION_H_
#define _INVISCID_SIMULATION_H_

#include <algorithm>
#include <float.h>
// #include "../Simulation.h"
#include "../EulerSolver/InviscidFlowField.h"
#include "../stencils/PointCoordinateStencil.h"
#include "../stencils/TransformMetricesStencil.h"
#include "../stencils/InitialConditionStencil.h"
#include "../stencils/DomainTransformStencil.h"
#include "../stencils/BoundaryConditionStencil.h"
#include "../stencils/ReconstructStencil.h"
#include "../stencils/HalfTimeStepUpdateStencil.h"
#include "../stencils/SMaxStencil.h"
#include "../stencils/MUSCLStencil.h"
#include "../stencils/RecoverStencil.h"
#include "../stencils/ResidualStencil.h"
#include "../stencils/VTKGeoStencil.h"
#include "../stencils/DebugStencil.h"
#include "../Iterators.h"
#include "../EulerSolver/InviscidGlobalBoundaryFactory.h"
#include "Iterators.h"
#include "Definitions.h"

class InviscidSimulation{
protected:
  Parameters &_parameters;
	InviscidFlowField &_inviscidFlowField;

	PointCoordinateStencil _pointCoordinateStencil;
	FieldIterator<InviscidFlowField> _pointCoordinateIterator;
  GlobalBoundaryIterator<InviscidFlowField> _pointCoordinateBoundaryIterator;

	TransformMetricesStencil _transformMetricesStencil;
	FieldIterator<InviscidFlowField> _transformMetricesIterator;
	GlobalBoundaryIterator<InviscidFlowField> _transformMetricesBoundaryIterator;

  InitialConditionStencil _initialConditionStencil;
  FieldIterator<InviscidFlowField> _initialConditionIterator;

  DomainTransformStencil _domainTransformStencil;
  FieldIterator<InviscidFlowField> _domainTransformIterator;
  GlobalBoundaryIterator<InviscidFlowField> _domainTransformBoundaryIterator;

  InviscidGlobalBoundaryFactory _inviscidGlobalBoundaryFactory;
  GlobalBoundaryIterator<InviscidFlowField> _boundaryConditionIterator;

  ReconstructStencil _reconstructStencil;
  FieldIterator<InviscidFlowField> _reconstructIterator;
  GlobalBoundaryIterator<InviscidFlowField> _reconstructBoundaryIterator;

  HalfTimeStepUpdateStencil _halfTimeStepUpdateStencil;
  FieldIterator<InviscidFlowField> _halfTimeStepUpdateIterator;

  SMaxStencil _sMaxStencil;
	FieldIterator<InviscidFlowField> _sMaxIterator;
	// GlobalBoundaryIterator<InviscidFlowField> _sMaxBoundaryIterator;

  MUSCLStencil _musclStencil;
  FieldIterator<InviscidFlowField> _musclIterator;

  RecoverStencil _recoverStencil;
  FieldIterator<InviscidFlowField> _recoverIterator;

  ResidualStencil _residualStencil;
  FieldIterator<InviscidFlowField> _residualIterator;

  DebugStencil _debugStencil;
  FieldIterator<InviscidFlowField> _debugIterator;
  GlobalBoundaryIterator<InviscidFlowField> _debugBoundaryIterator;

  VTKGeoStencil _vtkGeoStencil;
	FieldIterator<InviscidFlowField> _vtkGeoIterator;

public:

	InviscidSimulation(Parameters &parameters, InviscidFlowField &inviscidFlowField):

  _parameters(parameters),
  _inviscidFlowField(inviscidFlowField),

	_pointCoordinateStencil(parameters),
	_pointCoordinateIterator(_inviscidFlowField,parameters,_pointCoordinateStencil),
  _pointCoordinateBoundaryIterator(_inviscidFlowField, parameters, _pointCoordinateStencil),

  _transformMetricesStencil(parameters),
	_transformMetricesIterator(_inviscidFlowField,
        parameters,_transformMetricesStencil),
  _transformMetricesBoundaryIterator(_inviscidFlowField, parameters, _transformMetricesStencil),

  _initialConditionStencil(parameters),
  _initialConditionIterator(_inviscidFlowField, parameters, _initialConditionStencil),

  _domainTransformStencil(parameters),
  _domainTransformIterator(_inviscidFlowField,parameters,_domainTransformStencil),
  _domainTransformBoundaryIterator(_inviscidFlowField,parameters,_domainTransformStencil,1,0),

  _inviscidGlobalBoundaryFactory(parameters),
	_boundaryConditionIterator(_inviscidGlobalBoundaryFactory.getUFGHGlobalBoundaryIterator(_inviscidFlowField)),

  _reconstructStencil(parameters),
  _reconstructIterator(_inviscidFlowField,parameters,_reconstructStencil),
  _reconstructBoundaryIterator(_inviscidFlowField,parameters,_reconstructStencil,1,0),

  _halfTimeStepUpdateStencil(parameters),
  _halfTimeStepUpdateIterator(_inviscidFlowField,parameters, _halfTimeStepUpdateStencil),

  _sMaxStencil(parameters),
  _sMaxIterator(_inviscidFlowField,
        parameters,_sMaxStencil),
  // _sMaxBoundaryIterator(_inviscidFlowField, parameters, _sMaxStencil),

 //  _roeStencil(parameters),
	// _roeIterator(_inviscidFlowField, parameters,_roeStencil),

  // _godunovStencil(parameters),
  // _godunovIterator(_inviscidFlowField, parameters, _godunovStencil),

  _musclStencil(parameters),
  _musclIterator(_inviscidFlowField, parameters, _musclStencil),

  _recoverStencil(parameters),
  _recoverIterator(_inviscidFlowField, parameters, _recoverStencil),

  _residualStencil(parameters),
  _residualIterator(_inviscidFlowField, parameters, _residualStencil),

// /*********************** Debug*********************** /
  _debugStencil(parameters),
  _debugIterator(_inviscidFlowField, parameters, _debugStencil),
  _debugBoundaryIterator(_inviscidFlowField, parameters, _debugStencil),
// /*********************** Debug*********************** /
  _vtkGeoStencil(parameters),
  _vtkGeoIterator(_inviscidFlowField,parameters,_vtkGeoStencil)

	{}

  void inviscid_initialization()
  {
    _initialConditionIterator.iterate();
    _pointCoordinateIterator.iterate();
    _pointCoordinateBoundaryIterator.iterate();
    _transformMetricesIterator.iterate();
    _transformMetricesBoundaryIterator.iterate();
    _boundaryConditionIterator.iterate(); 
  }

  void inviscid_solveTimeSteps()
  {
    _domainTransformIterator.iterate();
    _domainTransformBoundaryIterator.iterate();
    inviscid_setTimeStep(); 
   // // /*** MUSCL scheme ***/
    _reconstructBoundaryIterator.iterate();
    _reconstructIterator.iterate();
    _halfTimeStepUpdateIterator.iterate();
    _musclIterator.iterate();
   // // //  // _roeIterator.iterate();
  	// // // // _godunovIterator.iterate(); 
    _recoverIterator.iterate();
    _boundaryConditionIterator.iterate();
  }

  void debugPlot(int timeStep)
  {
    _debugIterator.iterate();
    _debugBoundaryIterator.iterate();
    _debugStencil.write(_inviscidFlowField, timeStep);
  }

  void plotGeoVTK(int timeStep){
    _vtkGeoStencil.clear();
    _vtkGeoIterator.iterate();
    _vtkGeoStencil.write(_inviscidFlowField,timeStep);
  }

  FLOAT convergenceCheck()
  {
    _residualStencil.reset();
    _residualIterator.iterate();
    return _residualStencil.getMaxResidual();
  }

  void inviscid_setTimeStep()
  {
 	// determine maximum velocity
    _sMaxStencil.reset();
    _sMaxIterator.iterate();
    // _sMaxBoundaryIterator.iterate();
    // Take Cfl number = 0.9
    // if (_parameters.geometry.dim == 3) 
    // {
    //   _parameters.timestep.dt = 0.01 / std::max(std::max(_sMaxStencil.getMaxValues()[0],_sMaxStencil.getMaxValues()[1]),_sMaxStencil.getMaxValues()[2]);
    // } 
    // else 
    // {
      // _parameters.timestep.dt = 0.01 /_sMaxStencil.getMaxValues();
     _parameters.timestep.dt = 0.05;
    // }
  }

};

#endif // _INVISCID_SIMULATION_H_
