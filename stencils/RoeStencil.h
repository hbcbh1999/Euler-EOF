#ifndef _Roe_STENCIL_H_
#define _Roe_STENCIL_H_

#include "../Stencil.h"
#include "../Parameters.h"
#include "../EulerSolver/InviscidFlowField.h"
#include <vector>

class RoeStencil : public FieldStencil<InviscidFlowField>, public BoundaryStencil<InviscidFlowField> {
protected:

    FLOAT HeatCapacityRatio;

    void getInterfaceFlux(InviscidFlowField & inviscidFlowField, int i, int j);
    // This function treat Riemann problem on x, y, z direction by changing the sequency of the varible in the outside input. When calculate flux G on y direction, we pass U = [rho, v, u, E] from outside but assign in the function as [rho, u, v, E].
    void getInterfaceFlux(InviscidFlowField & inviscidFlowField, int i, int j, int k);  

public:

	/** Constructor
     * @param parameters Parameters of the problem
     */
     RoeStencil(const Parameters & parameters);

    /** Apply the stencil in 2D
         * @param 
         * @param i Position in the X direction
         * @param j Position in the Y direction
         */
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j ); 
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k );


    //@ brief Boundary iterations for the 2D problem
    //@param inviscidFlowField Flow field with the state of the fluid
    //@param i Position in the X direction
    //@param j Position in the Y direction
    //@{
    void applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j );
    //@}

    //@ brief Boundary iterations for the 3D problem
    //@param inviscidFlowField Flow field with the state of the fluid
    //@param i Position in the X direction
    //@param j Position in the Y direction
    //@param k Position in the Z direction
    //@{
    void applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyFrontWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyBackWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k );    

};
#endif //_Roe_STENCIL_H_