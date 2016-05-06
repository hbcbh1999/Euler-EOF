#ifndef _Roe_STENCIL_H_
#define _Roe_STENCIL_H_

#include "../Stencil.h"
#include "../Parameters.h"
#include "../EulerSolver/InviscidFlowField.h"
#include <iostream>
#include <array>

class RoeStencil : public FieldStencil<InviscidFlowField>{
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

};
#endif //_Roe_STENCIL_H_