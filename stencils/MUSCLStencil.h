#ifndef _MUSCL_STENCIL_H_
#define _MUSCL_STENCIL_H_

#include "../Stencil.h"
#include "../Parameters.h"
#include "../EulerSolver/InviscidFlowField.h"
#include <array>
// An explicit method
class MUSCLStencil : public FieldStencil<InviscidFlowField> {
protected:
    FLOAT U_np1[4], U_n[4], F_left[4], F_right[4], G_top[4], G_bottom[4];

    FLOAT HeatCapacityRatio;

    void computeFlux(InviscidFlowField & inviscidFlowField, int i, int j);
    void computeFlux(InviscidFlowField & inviscidFlowField, int i, int j, int k);

public:

	/** Constructor
     * @param parameters Parameters of the problem
     */
     MUSCLStencil(const Parameters & parameters);

    /** Apply the stencil in 2D
         * @param 
         * @param i Position in the X direction
         * @param j Position in the Y direction
         */
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j ); 
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
 
};
#endif //_MUSCL_STENCIL_H_