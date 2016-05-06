#ifndef _POINT_COORDINATE_STENCIL_H
#define _POINT_COORDINATE_STENCIL_H

#include "../Definitions.h"
#include "../Parameters.h"
#include "../Stencil.h"
#include "../FlowField.h"
#include "../EulerSolver/InviscidFlowField.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <numeric>
#include <algorithm>
#include <vector>

/** Stencil for writting point coordinate on the physics domain
 *
 */
class PointCoordinateStencil : public FieldStencil<InviscidFlowField>, public BoundaryStencil<InviscidFlowField> {
	private:
      int sizeX, sizeY;
      std::array<FLOAT,2> point_mid,point_in,point_out;
	public:
		 /** Constructor
         * @moulin parameters Parameters of the problem
         */
		PointCoordinateStencil(const Parameters & parameters);
		/** Apply the stencil in 2D
         * @moulin get the point coordinates information from the physical domain
         * @moulin i Position in the X direction
         * @moulin j Position in the Y direction
         */
      void apply ( InviscidFlowField & inviscidFlowField, int i, int j );
	   void apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
      void applyLeftWall ( InviscidFlowField & inviscidFlowField, int i, int j );
      void applyRightWall ( InviscidFlowField & inviscidFlowField, int i, int j );
      void applyTopWall ( InviscidFlowField & inviscidFlowField, int i, int j );
      void applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j );
// TODO: 3D
      void applyLeftWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k);
      void applyRightWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k);
      void applyTopWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k);
      void applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k);
      void applyFrontWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k);
      void applyBackWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k);

      std::array<double,2> MirrorPoint2D(std::array<double,2> point1_on_wall, std::array<double,2> point2_on_wall,std::array<double,2> point_in);
};



#endif //_POINT_COORDINATE_STENCIL_H