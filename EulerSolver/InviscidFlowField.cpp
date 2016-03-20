#include "InviscidFlowField.h"

InviscidFlowField::InviscidFlowField(const Parameters & parameters):
    FlowField(parameters),
    _xi(parameters.geometry.dim==2?VectorField(getCellsX() + 3, getCellsY() + 3):
                      VectorField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),
    _eta(parameters.geometry.dim==2?VectorField(getCellsX() + 3, getCellsY() + 3):
                      VectorField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),
    _J(parameters.geometry.dim==2?ScalarField(getCellsX() + 3, getCellsY() + 3):
                      ScalarField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3))
  {}

	VectorField & InviscidFlowField::getXi () {
    return _xi;
	}

	VectorField & InviscidFlowField::getEta () {
    return _eta;
	}

  ScalarField & InviscidFlowField::getJ(){
    return _J;
  }
