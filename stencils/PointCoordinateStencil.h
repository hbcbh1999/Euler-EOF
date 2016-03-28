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

/** Stencil for writting point coordinate on the physics domain
 *
 */
class PointCoordinateStencil : public FieldStencil<InviscidFlowField> {
	private:
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
         /** Apply the stencil in 2D

			TODO
         */
		   void apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
};



#endif //_POINT_COORDINATE_STENCIL_H