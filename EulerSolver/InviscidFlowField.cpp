#include "InviscidFlowField.h"

InviscidFlowField::InviscidFlowField(const Parameters & parameters):
    FlowField(parameters),
    _density(parameters.geometry.dim==2?ScalarField(getCellsX() + 3, getCellsY() + 3):
                      ScalarField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),
    _xi(parameters.geometry.dim==2?VectorField(getCellsX() + 3, getCellsY() + 3):
                      VectorField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),
    _eta(parameters.geometry.dim==2?VectorField(getCellsX() + 3, getCellsY() + 3):
                      VectorField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),
    _J(parameters.geometry.dim==2?ScalarField(getCellsX() + 3, getCellsY() + 3):
                      ScalarField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),
    _pointCoordinate(parameters.geometry.dim==2?VectorField(getCellsX() + 3, getCellsY() + 3):
                      VectorField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),
    _energy(parameters.geometry.dim==2?ScalarField(getCellsX() + 3, getCellsY() + 3):
                      ScalarField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),

    _U(parameters.geometry.dim==2?FluxField(getCellsX() + 3, getCellsY() + 3):
                      FluxField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),
    _F(parameters.geometry.dim==2?FluxField(getCellsX() + 3, getCellsY() + 3):
                      FluxField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),
    _G(parameters.geometry.dim==2?FluxField(getCellsX() + 3, getCellsY() + 3):
                      FluxField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),
    _H(parameters.geometry.dim==2?FluxField(getCellsX() + 3, getCellsY() + 3):
                      FluxField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),

    _Uhat(parameters.geometry.dim==2?FluxField(getCellsX() + 3, getCellsY() + 3):
                      FluxField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),
    _Fhat(parameters.geometry.dim==2?FluxField(getCellsX() + 3, getCellsY() + 3):
                      FluxField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),
    _Ghat(parameters.geometry.dim==2?FluxField(getCellsX() + 3, getCellsY() + 3):
                      FluxField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),
    _Hhat(parameters.geometry.dim==2?FluxField(getCellsX() + 3, getCellsY() + 3):
                      FluxField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),
    _Fmid(parameters.geometry.dim==2?FluxField(getCellsX() + 3, getCellsY() + 3):
                      FluxField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),
    _Gmid(parameters.geometry.dim==2?FluxField(getCellsX() + 3, getCellsY() + 3):
                      FluxField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3)),
    _Hmid(parameters.geometry.dim==2?FluxField(getCellsX() + 3, getCellsY() + 3):
                      FluxField(getCellsX() + 3, getCellsY() + 3, getCellsZ() + 3))



  {}

  ScalarField & InviscidFlowField::getDensity(){
    return _density;
  }

	VectorField & InviscidFlowField::getXi () {
    return _xi;
	}

	VectorField & InviscidFlowField::getEta () {
    return _eta;
	}

  ScalarField & InviscidFlowField::getJ(){
    return _J;
  }

  VectorField & InviscidFlowField::getPointCoordinate(){
    return _pointCoordinate;
  }

  ScalarField & InviscidFlowField::getEnergy(){
    return _energy;
  }

  FluxField & InviscidFlowField::getU()
  {
    return _U;
  }

  FluxField & InviscidFlowField::getF()
  {
    return _F;
  }

  FluxField & InviscidFlowField::getG()
  {
    return _G;
  }

  FluxField & InviscidFlowField::getH()
  {
    return _H;
  }

  FluxField & InviscidFlowField::getUhat()
  {
    return _Uhat;
  }

  FluxField & InviscidFlowField::getFhat()
  {
    return _Fhat;
  }

  FluxField & InviscidFlowField::getGhat()
  {
    return _Ghat;
  }

  FluxField & InviscidFlowField::getHhat()
  {
    return _Hhat;
  }

  FluxField & InviscidFlowField::getFmid()
  {
    return _Fmid;   // Flux at right interface
  }

  FluxField & InviscidFlowField::getGmid()
  {
    return _Gmid;   // Flux at top interface
  }

  FluxField & InviscidFlowField::getHmid()
  {
    return _Hmid;   // Flux at front interfacc
  }