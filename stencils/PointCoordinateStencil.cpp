#include "PointCoordinateStencil.h"
// #include "../Preprocessor/SlopeChannel/ComputePosition2D_test1.cpp"
#include "../Preprocessor/ScaleChannel/ComputePosition2D_test1.cpp"
PointCoordinateStencil::PointCoordinateStencil ( const Parameters & parameters ): FieldStencil<InviscidFlowField> ( parameters ),BoundaryStencil<InviscidFlowField>(parameters) {
	sizeX = parameters.geometry.sizeX;
	sizeY = parameters.geometry.sizeY;
}

void PointCoordinateStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j)
{
	//TODO: read from the vtk file directly in future
	std::array<FLOAT,2> point = ComputePosition2D_test1(i,j,input1);
	//-------------------------------------------
	inviscidFlowField.getPointCoordinate().getVector(i, j)[0] = point[0];		// x
	inviscidFlowField.getPointCoordinate().getVector(i, j)[1] = point[1];		// y
	// if (i == 1){
	// std::cout<< inviscidFlowField.getPointCoordinate().getVector(i, j)[0] << std::endl;}
}

void PointCoordinateStencil::apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k){

	// TODO: 3D case
}

// Point corrdinate at the ghost layer. Extrapolate from the interior domain
void PointCoordinateStencil::applyLeftWall ( InviscidFlowField & inviscidFlowField, int i, int j ){
 
	if ( j == 0 )	// Left bottom corner
	{
		point_mid = ComputePosition2D_test1(i+1,j+1,input1);
		point_in = ComputePosition2D_test1(i+2,j+2,input1);

		inviscidFlowField.getPointCoordinate().getVector(i, j)[0] = 2.0 * point_mid[0] - point_in[0];
		inviscidFlowField.getPointCoordinate().getVector(i, j)[1] = 2.0 * point_mid[1] - point_in[1];
	} 	
	else if ( j == (sizeY + 2))		// Left top corner
	{
		point_mid = ComputePosition2D_test1(i+1,j-1,input1);
		point_in = ComputePosition2D_test1(i+2,j-2,input1);

		inviscidFlowField.getPointCoordinate().getVector(i, j)[0] = 2.0 * point_mid[0] - point_in[0];
		inviscidFlowField.getPointCoordinate().getVector(i, j)[1] = 2.0 * point_mid[1] - point_in[1];
	}
	else
	{
		std::array<FLOAT,2> point_a = ComputePosition2D_test1(i+1,j+1,input1);
		std::array<FLOAT,2> point_b = ComputePosition2D_test1(i+1,j,input1);
		std::array<FLOAT,2> point_c = ComputePosition2D_test1(i+2,j,input1);

		std::array<FLOAT,2> point_mirror = MirrorPoint2D(point_a,point_b,point_c);

		inviscidFlowField.getPointCoordinate().getVector(i, j)[0] = point_mirror[0];
		inviscidFlowField.getPointCoordinate().getVector(i, j)[1] = point_mirror[1];
	}
}
void PointCoordinateStencil::applyRightWall ( InviscidFlowField & inviscidFlowField, int i, int j )
{

	if ( j == 0 )	// Right bottom corner
	{
		point_mid = ComputePosition2D_test1(i-1,j+1,input1);
		point_in = ComputePosition2D_test1(i-2,j+2,input1);

		inviscidFlowField.getPointCoordinate().getVector(i, j)[0] = 2.0 * point_mid[0] - point_in[0];
		inviscidFlowField.getPointCoordinate().getVector(i, j)[1] = 2.0 * point_mid[1] - point_in[1];
	} 	
	else if ( j == (sizeY + 2))		// Right top corner
	{
		point_mid = ComputePosition2D_test1(i-1,j-1,input1);
		point_in = ComputePosition2D_test1(i-2,j-2,input1);

		inviscidFlowField.getPointCoordinate().getVector(i, j)[0] = 2.0 * point_mid[0] - point_in[0];
		inviscidFlowField.getPointCoordinate().getVector(i, j)[1] = 2.0 * point_mid[1] - point_in[1];
	}
	else
	{
		std::array<FLOAT,2> point_a = ComputePosition2D_test1(i-1,j-1,input1);
		std::array<FLOAT,2> point_b = ComputePosition2D_test1(i-1,j,input1);
		std::array<FLOAT,2> point_c = ComputePosition2D_test1(i-2,j,input1);

		std::array<FLOAT,2> point_mirror = MirrorPoint2D(point_a,point_b,point_c);

		inviscidFlowField.getPointCoordinate().getVector(i, j)[0] = point_mirror[0];
		inviscidFlowField.getPointCoordinate().getVector(i, j)[1] = point_mirror[1];
	}
}

void PointCoordinateStencil::applyTopWall( InviscidFlowField & inviscidFlowField, int i, int j )
{
	if (i==0 || i == sizeX+2 )
	{

	}else
	{
		std::array<FLOAT,2> point_a = ComputePosition2D_test1(i+1,j-1,input1);
		std::array<FLOAT,2> point_b = ComputePosition2D_test1(i,j-1,input1);
		std::array<FLOAT,2> point_c = ComputePosition2D_test1(i,j-2,input1);

		std::array<FLOAT,2> point_mirror = MirrorPoint2D(point_a,point_b,point_c);

		inviscidFlowField.getPointCoordinate().getVector(i, j)[0] = point_mirror[0];
		inviscidFlowField.getPointCoordinate().getVector(i, j)[1] = point_mirror[1];
	}
}
void PointCoordinateStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j )
{
	if (i==0 || i == sizeX+2 )
	{

	}else
	{
		std::array<FLOAT,2> point_a = ComputePosition2D_test1(i-1,j+1,input1);
		std::array<FLOAT,2> point_b = ComputePosition2D_test1(i,j+1,input1);
		std::array<FLOAT,2> point_c = ComputePosition2D_test1(i,j+2,input1);

		std::array<FLOAT,2> point_mirror = MirrorPoint2D(point_a,point_b,point_c);

		inviscidFlowField.getPointCoordinate().getVector(i, j)[0] = point_mirror[0];
		inviscidFlowField.getPointCoordinate().getVector(i, j)[1] = point_mirror[1];
	}
}


void PointCoordinateStencil::applyLeftWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
	
}
void PointCoordinateStencil::applyRightWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
	
}
void PointCoordinateStencil::applyTopWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
	
}
void PointCoordinateStencil::applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
	
}

void PointCoordinateStencil::applyFrontWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
	
}
void PointCoordinateStencil::applyBackWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k){
	
}

std::array<FLOAT,2> PointCoordinateStencil::MirrorPoint2D(std::array<FLOAT,2> point1_on_wall, std::array<FLOAT,2> point2_on_wall,std::array<FLOAT,2> point_in)
{
	FLOAT N = sqrt(pow((point2_on_wall[0] - point1_on_wall[0]),2) + pow((point2_on_wall[1] - point1_on_wall[1]),2));
	std::vector<FLOAT> r{	point_in[0] - point2_on_wall[0], point_in[1] - point2_on_wall[1] };
	std::vector<FLOAT> n{	(point2_on_wall[0] - point1_on_wall[0])/N,(point2_on_wall[1] - point1_on_wall[1])/N };

	FLOAT n_dot_r = r[0] * n[0] + r[1] * n[1];
	
	std::array<FLOAT,2> point_mirror;
	for (int k = 0; k < 2; ++k)
	{
		point_mirror[k] = point2_on_wall[k] + ( 2 * n_dot_r * n[k] - r[k] );
	}

	return point_mirror;
}

