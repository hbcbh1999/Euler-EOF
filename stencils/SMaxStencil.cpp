#include "SMaxStencil.h"
#include <algorithm>
#include <math.h>


SMaxStencil::SMaxStencil (const Parameters & parameters) :
    FieldStencil<InviscidFlowField> (parameters), BoundaryStencil<InviscidFlowField> (parameters) {
    reset();
}

void SMaxStencil::apply (InviscidFlowField & inviscidFlowField, int i, int j){
    cellMaxValue(inviscidFlowField, i, j);
}

void SMaxStencil::apply (InviscidFlowField & inviscidFlowField, int i, int j, int k){
    cellMaxValue(inviscidFlowField, i, j, k);
}

void SMaxStencil::applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j ){
    cellMaxValue(inviscidFlowField, i, j);
}

void SMaxStencil::applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j ){
    cellMaxValue(inviscidFlowField, i, j);
}

void SMaxStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j ){
    cellMaxValue(inviscidFlowField, i, j);
}

void SMaxStencil::applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j ){
    cellMaxValue(inviscidFlowField, i, j);
}

void SMaxStencil::applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k ){
    cellMaxValue(inviscidFlowField, i, j, k);
}

void SMaxStencil::applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k ){
    cellMaxValue(inviscidFlowField, i, j, k);
}

void SMaxStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k ){
    cellMaxValue(inviscidFlowField, i, j, k);
}

void SMaxStencil::applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j, int k ){
    cellMaxValue(inviscidFlowField, i, j, k);
}

void SMaxStencil::applyFrontWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k ){
    cellMaxValue(inviscidFlowField, i, j, k);
}

void SMaxStencil::applyBackWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k ){
    cellMaxValue(inviscidFlowField, i, j, k);
}


void SMaxStencil::cellMaxValue(InviscidFlowField & inviscidFlowField, int i, int j){
    FLOAT rho = inviscidFlowField.getUhat().getFlux(i,j)[0];
    FLOAT u = inviscidFlowField.getUhat().getFlux(i,j)[1]/rho;
    FLOAT v = inviscidFlowField.getUhat().getFlux(i,j)[2]/rho;
    if (u > _maxValues[0]){
        _maxValues[0] = u;
    }
    if (v > _maxValues[1]){
        _maxValues[1] = v;
    }
}

void SMaxStencil::cellMaxValue(InviscidFlowField & inviscidFlowField, int i, int j, int k)
{
    FLOAT rho = inviscidFlowField.getUhat().getFlux(i,j,k)[0];
    FLOAT u = inviscidFlowField.getUhat().getFlux(i,j,k)[1]/rho;
    FLOAT v = inviscidFlowField.getUhat().getFlux(i,j,k)[2]/rho;
    FLOAT w = inviscidFlowField.getUhat().getFlux(i,j,k)[3]/rho;
    
    if (u > _maxValues[0])
    {
        _maxValues[0] = u;
    }
    if (v > _maxValues[1])
    {
        _maxValues[1] = v;
    }
    if (w > _maxValues[2])
    {
        _maxValues[2] = w;
    }   
}

void SMaxStencil::reset () {
    _maxValues[0] = 0;
    _maxValues[1] = 0;
    _maxValues[2] = 0;
}

const FLOAT * SMaxStencil::getMaxValues() const{
    return _maxValues;
}
