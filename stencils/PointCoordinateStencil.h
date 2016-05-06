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

/** Stencil for writting point coordinate on the physics domain
 *
 */
class PointCoordinateStencil : public FieldStencil<InviscidFlowField>, public BoundaryStencil<InviscidFlowField> {
	private:
      int sizeX, sizeY;
      std::array<double,2> point_out,point_mid,point_in;
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

      void extrapolatePoint2D(std::array<double,2> point_mid, std::array<double,2> point_in);
};



#endif //_POINT_COORDINATE_STENCIL_H