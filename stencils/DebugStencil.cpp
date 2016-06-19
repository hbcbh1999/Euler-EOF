#include "DebugStencil.h"

DebugStencil::DebugStencil(const Parameters & parameters) :
		FieldStencil<InviscidFlowField>(parameters), BoundaryStencil<InviscidFlowField>(parameters)  {
			sizeX = parameters.geometry.sizeX;
			sizeY = parameters.geometry.sizeY;
}

void DebugStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j )
{
	JValue[i][j] = inviscidFlowField.getJ().getScalar(i,j);
	xi0Value[i][j] = inviscidFlowField.getXi().getVector(i,j)[0];
	xi1Value[i][j] = inviscidFlowField.getXi().getVector(i,j)[1];
	eta0Value[i][j] = inviscidFlowField.getEta().getVector(i,j)[0];
	eta1Value[i][j] = inviscidFlowField.getEta().getVector(i,j)[1];

	XValue[i][j] = inviscidFlowField.getPointCoordinate().getVector(i,j)[0];
	YValue[i][j] = inviscidFlowField.getPointCoordinate().getVector(i,j)[1];

	PressureValue[i][j] =  inviscidFlowField.getPressure().getScalar(i,j);
	DensityValue[i][j] = inviscidFlowField.getDensity().getScalar(i,j);
	uValue[i][j] = inviscidFlowField.getVelocity().getVector(i,j)[0];
	vValue[i][j] = inviscidFlowField.getVelocity().getVector(i,j)[1];

	U0[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[0];
	U1[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[1];
	U2[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[2];
	U3[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[3];

	Ul0[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[0];
	Ul1[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[1];
	Ul2[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[2];
	Ul3[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[3];

	Ur0[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[0];
	Ur1[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[1];
	Ur2[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[2];
	Ur3[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[3];

	Ub0[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[0];
	Ub1[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[1];
	Ub2[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[2];
	Ub3[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[3];

	Ut0[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[0];
	Ut1[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[1];
	Ut2[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[2];
	Ut3[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[3];

	Fl0[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[0];
	Fl1[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[1];
	Fl2[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[2];
	Fl3[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[3];

	Fr0[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[0];
	Fr1[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[1];
	Fr2[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[2];
	Fr3[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[3];

	Gb0[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[0];
	Gb1[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[1];
	Gb2[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[2];
	Gb3[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[3];

	Gt0[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[0];
	Gt1[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[1];
	Gt2[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[2];
	Gt3[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[3];


	F0[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[0];
	F1[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[1];
	F2[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[2];
	F3[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[3];

	G0[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[0];
	G1[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[1];
	G2[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[2];
	G3[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[3];

	Fmid0[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[0];
	Fmid1[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[1];
	Fmid2[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[2];
	Fmid3[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[3];

	Gmid0[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[0];
	Gmid1[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[1];
	Gmid2[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[2];
	Gmid3[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[3];

}

void DebugStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k )
{

}


void DebugStencil::applyLeftWall ( InviscidFlowField & inviscidFlowField, int i, int j )
{
	JValue[i][j] = inviscidFlowField.getJ().getScalar(i,j);
	xi0Value[i][j] = inviscidFlowField.getXi().getVector(i,j)[0];
	xi1Value[i][j] = inviscidFlowField.getXi().getVector(i,j)[1];
	eta0Value[i][j] = inviscidFlowField.getEta().getVector(i,j)[0];
	eta1Value[i][j] = inviscidFlowField.getEta().getVector(i,j)[1];
	PressureValue[i][j] =  inviscidFlowField.getPressure().getScalar(i,j);
	DensityValue[i][j] = inviscidFlowField.getDensity().getScalar(i,j);
	uValue[i][j] = inviscidFlowField.getVelocity().getVector(i,j)[0];
	vValue[i][j] = inviscidFlowField.getVelocity().getVector(i,j)[1];

	XValue[i][j] = inviscidFlowField.getPointCoordinate().getVector(i,j)[0];
	YValue[i][j] = inviscidFlowField.getPointCoordinate().getVector(i,j)[1];


	U0[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[0];
	U1[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[1];
	U2[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[2];
	U3[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[3];




	Ul0[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[0];
	Ul1[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[1];
	Ul2[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[2];
	Ul3[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[3];

	Ur0[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[0];
	Ur1[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[1];
	Ur2[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[2];
	Ur3[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[3];

	Ub0[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[0];
	Ub1[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[1];
	Ub2[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[2];
	Ub3[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[3];

	Ut0[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[0];
	Ut1[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[1];
	Ut2[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[2];
	Ut3[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[3];


	Fl0[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[0];
	Fl1[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[1];
	Fl2[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[2];
	Fl3[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[3];


	Fr0[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[0];
	Fr1[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[1];
	Fr2[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[2];
	Fr3[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[3];

	Gb0[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[0];
	Gb1[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[1];
	Gb2[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[2];
	Gb3[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[3];

	Gt0[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[0];
	Gt1[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[1];
	Gt2[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[2];
	Gt3[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[3];


	F0[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[0];
	F1[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[1];
	F2[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[2];
	F3[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[3];

	G0[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[0];
	G1[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[1];
	G2[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[2];
	G3[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[3];

	Fmid0[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[0];
	Fmid1[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[1];
	Fmid2[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[2];
	Fmid3[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[3];

	Gmid0[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[0];
	Gmid1[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[1];
	Gmid2[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[2];
	Gmid3[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[3];

}


void DebugStencil::applyRightWall ( InviscidFlowField & inviscidFlowField, int i, int j )
{
	JValue[i][j] = inviscidFlowField.getJ().getScalar(i,j);
	xi0Value[i][j] = inviscidFlowField.getXi().getVector(i,j)[0];
	xi1Value[i][j] = inviscidFlowField.getXi().getVector(i,j)[1];
	eta0Value[i][j] = inviscidFlowField.getEta().getVector(i,j)[0];
	eta1Value[i][j] = inviscidFlowField.getEta().getVector(i,j)[1];
	PressureValue[i][j] =  inviscidFlowField.getPressure().getScalar(i,j);
	DensityValue[i][j] = inviscidFlowField.getDensity().getScalar(i,j);
	uValue[i][j] = inviscidFlowField.getVelocity().getVector(i,j)[0];
	vValue[i][j] = inviscidFlowField.getVelocity().getVector(i,j)[1];

	XValue[i][j] = inviscidFlowField.getPointCoordinate().getVector(i,j)[0];
	YValue[i][j] = inviscidFlowField.getPointCoordinate().getVector(i,j)[1];

	U0[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[0];
	U1[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[1];
	U2[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[2];
	U3[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[3];

	Ul0[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[0];
	Ul1[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[1];
	Ul2[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[2];
	Ul3[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[3];

	Ur0[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[0];
	Ur1[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[1];
	Ur2[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[2];
	Ur3[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[3];

	Ub0[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[0];
	Ub1[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[1];
	Ub2[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[2];
	Ub3[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[3];

	Ut0[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[0];
	Ut1[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[1];
	Ut2[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[2];
	Ut3[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[3];



	Fl0[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[0];
	Fl1[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[1];
	Fl2[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[2];
	Fl3[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[3];

	Fr0[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[0];
	Fr1[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[1];
	Fr2[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[2];
	Fr3[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[3];

	Gb0[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[0];
	Gb1[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[1];
	Gb2[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[2];
	Gb3[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[3];

	Gt0[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[0];
	Gt1[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[1];
	Gt2[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[2];
	Gt3[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[3];






	F0[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[0];
	F1[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[1];
	F2[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[2];
	F3[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[3];

	G0[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[0];
	G1[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[1];
	G2[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[2];
	G3[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[3];

	Fmid0[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[0];
	Fmid1[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[1];
	Fmid2[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[2];
	Fmid3[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[3];

	Gmid0[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[0];
	Gmid1[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[1];
	Gmid2[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[2];
	Gmid3[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[3];

}


void DebugStencil::applyTopWall ( InviscidFlowField & inviscidFlowField, int i, int j )
{
	JValue[i][j] = inviscidFlowField.getJ().getScalar(i,j);
	xi0Value[i][j] = inviscidFlowField.getXi().getVector(i,j)[0];
	xi1Value[i][j] = inviscidFlowField.getXi().getVector(i,j)[1];
	eta0Value[i][j] = inviscidFlowField.getEta().getVector(i,j)[0];
	eta1Value[i][j] = inviscidFlowField.getEta().getVector(i,j)[1];
	PressureValue[i][j] =  inviscidFlowField.getPressure().getScalar(i,j);
	DensityValue[i][j] = inviscidFlowField.getDensity().getScalar(i,j);
	uValue[i][j] = inviscidFlowField.getVelocity().getVector(i,j)[0];
	vValue[i][j] = inviscidFlowField.getVelocity().getVector(i,j)[1];


	XValue[i][j] = inviscidFlowField.getPointCoordinate().getVector(i,j)[0];
	YValue[i][j] = inviscidFlowField.getPointCoordinate().getVector(i,j)[1];

	Ul0[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[0];
	Ul1[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[1];
	Ul2[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[2];
	Ul3[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[3];

	Ur0[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[0];
	Ur1[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[1];
	Ur2[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[2];
	Ur3[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[3];

	Ub0[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[0];
	Ub1[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[1];
	Ub2[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[2];
	Ub3[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[3];

	Ut0[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[0];
	Ut1[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[1];
	Ut2[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[2];
	Ut3[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[3];


	Fl0[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[0];
	Fl1[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[1];
	Fl2[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[2];
	Fl3[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[3];

	Fr0[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[0];
	Fr1[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[1];
	Fr2[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[2];
	Fr3[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[3];

	Gb0[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[0];
	Gb1[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[1];
	Gb2[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[2];
	Gb3[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[3];

	Gt0[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[0];
	Gt1[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[1];
	Gt2[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[2];
	Gt3[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[3];



	U0[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[0];
	U1[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[1];
	U2[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[2];
	U3[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[3];

	F0[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[0];
	F1[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[1];
	F2[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[2];
	F3[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[3];

	G0[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[0];
	G1[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[1];
	G2[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[2];
	G3[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[3];

	Fmid0[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[0];
	Fmid1[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[1];
	Fmid2[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[2];
	Fmid3[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[3];

	Gmid0[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[0];
	Gmid1[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[1];
	Gmid2[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[2];
	Gmid3[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[3];

}


void DebugStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j )
{
	JValue[i][j] = inviscidFlowField.getJ().getScalar(i,j);
	xi0Value[i][j] = inviscidFlowField.getXi().getVector(i,j)[0];
	xi1Value[i][j] = inviscidFlowField.getXi().getVector(i,j)[1];
	eta0Value[i][j] = inviscidFlowField.getEta().getVector(i,j)[0];
	eta1Value[i][j] = inviscidFlowField.getEta().getVector(i,j)[1];
	PressureValue[i][j] =  inviscidFlowField.getPressure().getScalar(i,j);
	DensityValue[i][j] = inviscidFlowField.getDensity().getScalar(i,j);
	uValue[i][j] = inviscidFlowField.getVelocity().getVector(i,j)[0];
	vValue[i][j] = inviscidFlowField.getVelocity().getVector(i,j)[1];


	XValue[i][j] = inviscidFlowField.getPointCoordinate().getVector(i,j)[0];
	YValue[i][j] = inviscidFlowField.getPointCoordinate().getVector(i,j)[1];

	U0[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[0];
	U1[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[1];
	U2[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[2];
	U3[i][j] = inviscidFlowField.getUhat().getFlux(i,j)[3];

	Ul0[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[0];
	Ul1[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[1];
	Ul2[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[2];
	Ul3[i][j] = inviscidFlowField.getUhatLeft().getFlux(i,j)[3];

	Ur0[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[0];
	Ur1[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[1];
	Ur2[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[2];
	Ur3[i][j] = inviscidFlowField.getUhatRight().getFlux(i,j)[3];

	Ub0[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[0];
	Ub1[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[1];
	Ub2[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[2];
	Ub3[i][j] = inviscidFlowField.getUhatBottom().getFlux(i,j)[3];

	Ut0[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[0];
	Ut1[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[1];
	Ut2[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[2];
	Ut3[i][j] = inviscidFlowField.getUhatTop().getFlux(i,j)[3];



	Fl0[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[0];
	Fl1[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[1];
	Fl2[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[2];
	Fl3[i][j] = inviscidFlowField.getFhatLeft().getFlux(i,j)[3];

	Fr0[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[0];
	Fr1[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[1];
	Fr2[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[2];
	Fr3[i][j] = inviscidFlowField.getFhatRight().getFlux(i,j)[3];

	Gb0[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[0];
	Gb1[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[1];
	Gb2[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[2];
	Gb3[i][j] = inviscidFlowField.getGhatBottom().getFlux(i,j)[3];

	Gt0[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[0];
	Gt1[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[1];
	Gt2[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[2];
	Gt3[i][j] = inviscidFlowField.getGhatTop().getFlux(i,j)[3];




	F0[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[0];
	F1[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[1];
	F2[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[2];
	F3[i][j] = inviscidFlowField.getFhat().getFlux(i,j)[3];

	G0[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[0];
	G1[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[1];
	G2[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[2];
	G3[i][j] = inviscidFlowField.getGhat().getFlux(i,j)[3];

	Fmid0[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[0];
	Fmid1[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[1];
	Fmid2[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[2];
	Fmid3[i][j] = inviscidFlowField.getFmid().getFlux(i,j)[3];

	Gmid0[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[0];
	Gmid1[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[1];
	Gmid2[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[2];
	Gmid3[i][j] = inviscidFlowField.getGmid().getFlux(i,j)[3];

}

void DebugStencil::applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}
void DebugStencil::applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}
void DebugStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}
void DebugStencil::applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}
void DebugStencil::applyFrontWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}
void DebugStencil::applyBackWall    ( InviscidFlowField & inviscidFlowField, int i, int j, int k)
{

}

void DebugStencil::write (InviscidFlowField & inviscidFlowField, int timeStep)
{
	std::ofstream vtkFile;
	std::stringstream vtkFileName;
	std::string fileName;
	std::stringstream PressureValueOutput, uValueOutput, vValueOutput, DensityValueOutput, U0Output,U1Output,U2Output,U3Output, JValueOutput, xi0ValueOutput,xi1ValueOutput,eta0ValueOutput,eta1ValueOutput,XValueOutput, YValueOutput, F0Output, F1Output, F2Output, F3Output, G0Output, G1Output, G2Output, G3Output, Fmid0Output, Fmid1Output, Fmid2Output, Fmid3Output, Gmid0Output, Gmid1Output, Gmid2Output, Gmid3Output, Ul0Output, Ul1Output, Ul2Output, Ul3Output, Ur0Output, Ur1Output, Ur2Output, Ur3Output, Ub0Output, Ub1Output, Ub2Output, Ub3Output, Ut0Output, Ut1Output, Ut2Output, Ut3Output, Fl0Output, Fl1Output, Fl2Output, Fl3Output, Fr0Output, Fr1Output, Fr2Output, Fr3Output, Gb0Output, Gb1Output, Gb2Output, Gb3Output, Gt0Output, Gt1Output, Gt2Output, Gt3Output;

	for (int j = 62; j>= 0; --j)
	{
		for (int i = 0; i<= 212; ++i)
		{
			JValueOutput << JValue[i][j] << ",";
			xi0ValueOutput << xi0Value[i][j] << ",";
			xi1ValueOutput << xi1Value[i][j] << ",";
			eta0ValueOutput << eta0Value[i][j] << ",";
			eta1ValueOutput << eta1Value[i][j] << ",";

			DensityValueOutput << DensityValue[i][j] << ",";
			uValueOutput << uValue[i][j] <<",";
			vValueOutput << vValue[i][j] << ",";
			PressureValueOutput << PressureValue[i][j] << ",";

			Ul0Output << Ul0[i][j]<<",";
			Ul1Output << Ul1[i][j]<<",";
			Ul2Output << Ul2[i][j]<<",";
			Ul3Output << Ul3[i][j]<<",";

			Ur0Output << Ur0[i][j]<<",";
			Ur1Output << Ur1[i][j]<<",";
			Ur2Output << Ur2[i][j]<<",";
			Ur3Output << Ur3[i][j]<<",";

			Ub0Output << Ub0[i][j]<<",";
			Ub1Output << Ub1[i][j]<<",";
			Ub2Output << Ub2[i][j]<<",";
			Ub3Output << Ub3[i][j]<<",";

			Ut0Output << Ut0[i][j]<<",";
			Ut1Output << Ut1[i][j]<<",";
			Ut2Output << Ut2[i][j]<<",";
			Ut3Output << Ut3[i][j]<<",";



			Fl0Output << Fl0[i][j]<<",";
			Fl1Output << Fl1[i][j]<<",";
			Fl2Output << Fl2[i][j]<<",";
			Fl3Output << Fl3[i][j]<<",";

			Fr0Output << Fr0[i][j]<<",";
			Fr1Output << Fr1[i][j]<<",";
			Fr2Output << Fr2[i][j]<<",";
			Fr3Output << Fr3[i][j]<<",";

			Gb0Output << Gb0[i][j]<<",";
			Gb1Output << Gb1[i][j]<<",";
			Gb2Output << Gb2[i][j]<<",";
			Gb3Output << Gb3[i][j]<<",";

			Gt0Output << Gt0[i][j]<<",";
			Gt1Output << Gt1[i][j]<<",";
			Gt2Output << Gt2[i][j]<<",";
			Gt3Output << Gt3[i][j]<<",";



			U0Output << U0[i][j]<<",";
			U1Output << U1[i][j]<<",";
			U2Output << U2[i][j]<<",";
			U3Output << U3[i][j]<<",";

			F0Output << F0[i][j]<<",";
			F1Output << F1[i][j]<<",";
			F2Output << F2[i][j]<<",";
			F3Output << F3[i][j]<<",";

			G0Output << G0[i][j]<<",";
			G1Output << G1[i][j]<<",";
			G2Output << G2[i][j]<<",";
			G3Output << G3[i][j]<<",";

			Fmid0Output << Fmid0[i][j]<<",";
			Fmid1Output << Fmid1[i][j]<<",";
			Fmid2Output << Fmid2[i][j]<<",";
			Fmid3Output << Fmid3[i][j]<<",";

			Gmid0Output << Gmid0[i][j]<<",";
			Gmid1Output << Gmid1[i][j]<<",";
			Gmid2Output << Gmid2[i][j]<<",";
			Gmid3Output << Gmid3[i][j]<<",";

			XValueOutput << XValue[i][j] << ",";
			YValueOutput << YValue[i][j] << ",";
		}
	// 
		XValueOutput << "\n";
		YValueOutput << "\n";

		JValueOutput << "\n";
		xi0ValueOutput << "\n";
		xi1ValueOutput << "\n";
		eta0ValueOutput << "\n";
		eta1ValueOutput << "\n";

		DensityValueOutput << "\n";
		uValueOutput << "\n";
		vValueOutput << "\n";
		PressureValueOutput << "\n";

		U0Output << "\n";
		U1Output << "\n";
		U2Output << "\n";
		U3Output << "\n";

		Ul0Output << "\n";
		Ul1Output << "\n";
		Ul2Output << "\n";
		Ul3Output << "\n";

		Ur0Output << "\n";
		Ur1Output << "\n";
		Ur2Output << "\n";
		Ur3Output << "\n";

		Ub0Output << "\n";
		Ub1Output << "\n";
		Ub2Output << "\n";
		Ub3Output << "\n";

		Ut0Output << "\n";
		Ut1Output << "\n";
		Ut2Output << "\n";
		Ut3Output << "\n";

		Fl0Output << "\n";
		Fl1Output << "\n";
		Fl2Output << "\n";
		Fl3Output << "\n";

		Fr0Output << "\n";
		Fr1Output << "\n";
		Fr2Output << "\n";
		Fr3Output << "\n";

		Gb0Output << "\n";
		Gb1Output << "\n";
		Gb2Output << "\n";
		Gb3Output << "\n";

		Gt0Output << "\n";
		Gt1Output << "\n";
		Gt2Output << "\n";
		Gt3Output << "\n";		

		F0Output << "\n ";
		F1Output << "\n ";
		F2Output << "\n ";
		F3Output << "\n ";

		G0Output << "\n ";
		G1Output << "\n ";
		G2Output << "\n ";
		G3Output << "\n ";

		Fmid0Output << "\n";
		Fmid1Output << "\n";
		Fmid2Output << "\n";
		Fmid3Output << "\n";

		Gmid0Output << "\n";
		Gmid1Output << "\n";
		Gmid2Output << "\n";
		Gmid3Output << "\n";
	}

	std::ofstream X, Y, RHO, U, V, P;

	X.open("./result/post/X.csv");
	X << XValueOutput.str();
	X.close();	

	Y.open("./result/post/Y.csv");
	Y << YValueOutput.str();
	Y.close();

	RHO.open("./result/post/RHO.csv");
	RHO << DensityValueOutput.str();
	RHO.close();

	U.open("./result/post/U.csv");
	U << uValueOutput.str();
	U.close();

	V.open("./result/post/V.csv");
	V << vValueOutput.str();
	V.close();

	P.open("./result/post/P.csv");
	P << PressureValueOutput.str();
	P.close();

	vtkFileName <<"./result/test_" << timeStep << ".csv";
	fileName = vtkFileName.str();

	vtkFile.open(fileName.c_str());

	vtkFile << "X_Value" << "\n";
	vtkFile << XValueOutput.str();
	vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	vtkFile << "Y_Value" << "\n";
	vtkFile << YValueOutput.str();
	vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n"; 

	// vtkFile << "J_Value" << "\n";
	// vtkFile << JValueOutput.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "xi0_Value" << "\n";
	// vtkFile << xi0ValueOutput.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";

	// vtkFile << "xi1_Value" << "\n";
	// vtkFile << xi1ValueOutput.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";

	// vtkFile << "eta0_Value" << "\n";
	// vtkFile << eta0ValueOutput.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";

	// vtkFile << "eta1_Value" << "\n";
	// vtkFile << eta1ValueOutput.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n"; 

	// vtkFile << "Density_Value" << "\n";
	// vtkFile << DensityValueOutput.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n"; 

	// vtkFile << "u_Value" << "\n";
	// vtkFile << uValueOutput.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  
	// vtkFile << "v_Value" << "\n";
	// vtkFile << vValueOutput.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n"; 

	// vtkFile << "pressure_Value" << "\n";
	// vtkFile << PressureValueOutput.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  
	

	// vtkFile << "Transfer_Density_Value" << "\n";
	// vtkFile << U0Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Transfer_rho_u_Value" << "\n";
	// vtkFile << U1Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Transfer_rho_v_Value" << "\n";
	// vtkFile << U2Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Transfer_Energy_Value" << "\n";
	// vtkFile << U3Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	vtkFile << "Ul0_Value" << "\n";
	vtkFile << Ul0Output.str();
	vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Ul1_Value" << "\n";
	// vtkFile << Ul1Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Ul2_Value" << "\n";
	// vtkFile << Ul2Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Ul3_Value" << "\n";
	// vtkFile << Ul3Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	vtkFile << "Ur0_Value" << "\n";
	vtkFile << Ur0Output.str();
	vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Ur1_Value" << "\n";
	// vtkFile << Ur1Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Ur2_Value" << "\n";
	// vtkFile << Ur2Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Ur3_Value" << "\n";
	// vtkFile << Ur3Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	vtkFile << "Ub0_Value" << "\n";
	vtkFile << Ub0Output.str();
	vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Ub1_Value" << "\n";
	// vtkFile << Ub1Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Ub2_Value" << "\n";
	// vtkFile << Ub2Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Ub3_Value" << "\n";
	// vtkFile << Ub3Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	vtkFile << "Ut0_Value" << "\n";
	vtkFile << Ut0Output.str();
	vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Ut1_Value" << "\n";
	// vtkFile << Ut1Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Ut2_Value" << "\n";
	// vtkFile << Ut2Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Ut3_Value" << "\n";
	// vtkFile << Ut3Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";

	vtkFile << "Fl_Value" << "\n";
	vtkFile << Fl0Output.str();
	vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Fl_Value" << "\n";
	// vtkFile << Fl1Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Fl_Value" << "\n";
	// vtkFile << Fl2Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Fl_Value" << "\n";
	// vtkFile << Fl3Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	vtkFile << "Fr_Value" << "\n";
	vtkFile << Fr0Output.str();
	vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Fr_Value" << "\n";
	// vtkFile << Fr1Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Fr_Value" << "\n";
	// vtkFile << Fr2Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Fr_Value" << "\n";
	// vtkFile << Fr3Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	vtkFile << "Gb_Value" << "\n";
	vtkFile << Gb0Output.str();
	vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Gb_Value" << "\n";
	// vtkFile << Gb1Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Gb_Value" << "\n";
	// vtkFile << Gb2Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Gb_Value" << "\n";
	// vtkFile << Gb3Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	vtkFile << "Gt_Value" << "\n";
	vtkFile << Gt0Output.str();
	vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Gt_Value" << "\n";
	// vtkFile << Gt1Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Gt_Value" << "\n";
	// vtkFile << Gt2Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "Gt_Value" << "\n";
	// vtkFile << Gt3Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";    

	

	vtkFile << "F0_Value" << "\n";
	vtkFile << F0Output.str();
	vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "F1_Value" << "\n";
	// vtkFile << F1Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "F2_Value" << "\n";
	// vtkFile << F2Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	// vtkFile << "F3_Value" << "\n";
	// vtkFile << F3Output.str();
	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	

	vtkFile << "G0_Value" << "\n";

	vtkFile << G0Output.str();

	vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	

	// vtkFile << "G1_Value" << "\n";

	// vtkFile << G1Output.str();

	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  



	// vtkFile << "G2_Value" << "\n";

	// vtkFile << G2Output.str();

	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  



	// vtkFile << "G3_Value" << "\n";

	// vtkFile << G3Output.str();

	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	
	vtkFile << "Fmid0_Value" << "\n";
	vtkFile << Fmid0Output.str();
	vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  


	// vtkFile << "Fmid1_Value" << "\n";

	// vtkFile << Fmid1Output.str();

	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	

	// vtkFile << "Fmid2_Value" << "\n";

	// vtkFile << Fmid2Output.str();

	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	

	// vtkFile << "Fmid3_Value" << "\n";

	// vtkFile << Fmid3Output.str();

	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	

	vtkFile << "Gmid0_Value" << "\n";
	vtkFile << Gmid0Output.str();
	vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  

	

	// vtkFile << "Gmid1_Value" << "\n";

	// vtkFile << Gmid1Output.str();

	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  



	// vtkFile << "Gmid2_Value" << "\n";

	// vtkFile << Gmid2Output.str();

	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  



	// vtkFile << "Gmid3_Value" << "\n";

	// vtkFile << Gmid3Output.str();

	// vtkFile << "\n" << "\n"<< "\n"<< "\n"<< "\n"<< "\n"<< "\n";  


	vtkFile.close();


}