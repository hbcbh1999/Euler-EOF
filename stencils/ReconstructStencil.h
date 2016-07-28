#ifndef _RERCONSTRUCT_STENCIL_H_
#define _RERCONSTRUCT_STENCIL_H_

#include "../Stencil.h"
#include "../Parameters.h"
#include "../EulerSolver/InviscidFlowField.h"
#include <array> 
// An explicit method
class ReconstructStencil : public FieldStencil<InviscidFlowField>, public BoundaryStencil<InviscidFlowField> {

    FLOAT omega, gamma;
    int sizeX, sizeY;

    void reconstruct(InviscidFlowField & inviscidFlowField, int i, int j, int edge);
    void reconstruct(InviscidFlowField & inviscidFlowField, int i, int j, int k, int edge);
    void reconstructBoundary(InviscidFlowField & inviscidFlowField, int i, int j);
    void reconstructBoundary(InviscidFlowField & inviscidFlowField, int i, int j, int k);

    FLOAT MinMaxMod(FLOAT a, FLOAT b, int k);

public:

	/** Constructor
     * @param parameters Parameters of the problem
     */
     ReconstructStencil(const Parameters & parameters);

    /** Apply the stencil in 2D
         * @param 
         * @param i Position in the X direction
         * @param j Position in the Y direction
         */
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j ); 
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k );

            //@brief Functions for the 2D problem. Coordinates entered in alphabetical order.
    void applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j );

    // TODO: 3D
    void applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyFrontWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyBackWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
 
};
#endif //_RERCONSTRUCT_STENCIL_H_