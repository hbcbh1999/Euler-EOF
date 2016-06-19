#ifndef _RESIDUAL_STENCIL_H_
#define _RESIDUAL_STENCIL_H_

#include "../Stencil.h"
#include "../Parameters.h"
#include "../EulerSolver/InviscidFlowField.h"

class ResidualStencil : public FieldStencil<InviscidFlowField> {
private:
    FLOAT MaxRhoRelRes;
public:

	/** Constructor
     * @param parameters Parameters of the problem
     */
     ResidualStencil(const Parameters & parameters);

    /** Apply the stencil in 2D
         * @param 
         * @param i Position in the X direction
         * @param j Position in the Y direction
         */
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j ); 
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k );

    FLOAT getMaxResidual();
    void reset();
 
};
#endif //_RESIDUAL_STENCIL_H_