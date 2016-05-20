#ifndef _GODUNOV_STENCIL_H_
#define _GODUNOV_STENCIL_H_

#include "../Stencil.h"
#include "../Parameters.h"
#include "../EulerSolver/InviscidFlowField.h"
#include <array>
// An explicit method
class GodunovStencil : public FieldStencil<InviscidFlowField> {
protected:
    FLOAT U_np1[4], U_n[4], F_left[4], F_right[4], G_top[4], G_bottom[4];
    FLOAT dt, dx, dy; // dt/dx, in this case dx = 1 in the computational domain 

    FLOAT HeatCapacityRatio;

    void getInterfaceFlux(InviscidFlowField & inviscidFlowField, int i, int j);
    // This function treat Riemann problem on x, y, z direction by changing the sequency of the varible in the outside input. When calculate flux G on y direction, we pass U = [rho, v, u, E] from outside but assign in the function as [rho, u, v, E].
    void getInterfaceFlux(InviscidFlowField & inviscidFlowField, int i, int j, int k);  
public:

	/** Constructor
     * @param parameters Parameters of the problem
     */
     GodunovStencil(const Parameters & parameters);

    /** Apply the stencil in 2D
         * @param 
         * @param i Position in the X direction
         * @param j Position in the Y direction
         */
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j ); 
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
 
};
#endif //_GODUNOV_STENCIL_H_