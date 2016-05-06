#ifndef _TRANSFORM_METRICES_STENCIL_H_
#define _TRANSFORM_METRICES_STENCIL_H_

#include "../Stencil.h"
#include "../Parameters.h"
#include "../EulerSolver/InviscidFlowField.h"

class TransformMetricesStencil : public FieldStencil<InviscidFlowField>,public BoundaryStencil<InviscidFlowField>  {

public:

	/** Constructor
     * @param parameters Parameters of the problem
     */
     TransformMetricesStencil(const Parameters & parameters);

    /** Apply the stencil in 2D
         * @param 
         * @param i Position in the X direction
         * @param j Position in the Y direction
         */
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j ); 
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    // //@ brief Boundary iterations for the 2D problem
    // //@param inviscidFlowField Flow field with the state of the fluid
    // //@param i Position in the X direction
    // //@param j Position in the Y direction
    // //@{
    void applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j,int k );
    void applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j,int k );
    void applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j,int k );
    void applyFrontWall ( InviscidFlowField & inviscidFlowField, int i, int j,int k );
    void applyBackWall    ( InviscidFlowField & inviscidFlowField, int i, int j,int k );
 
};
#endif