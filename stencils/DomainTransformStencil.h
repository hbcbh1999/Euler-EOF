#ifndef _DOMAIN_TRANSFORM_STENCIL_H_
#define _DOMAIN_TRANSFORM_STENCIL_H_

#include "../Stencil.h"
#include "../Parameters.h"
#include "../EulerSolver/InviscidFlowField.h"

class DomainTransformStencil : public FieldStencil<InviscidFlowField> {
protected:

public:

	/** Constructor
     * @param parameters Parameters of the problem
     */
     DomainTransformStencil(const Parameters & parameters);

    /** Apply the stencil in 2D
         * @param 
         * @param i Position in the X direction
         * @param j Position in the Y direction
         */
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j ); 
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
 
};
#endif //_DOMAIN_TRANSFORM_STENCIL_H_