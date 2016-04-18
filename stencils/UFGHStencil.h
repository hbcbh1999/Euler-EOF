#ifndef _UFGH_STENCIL_H_
#define _UFGH_STENCIL_H_

#include "../Stencil.h"
#include "../Parameters.h"
#include "../EulerSolver/InviscidFlowField.h"

class UFGHStencil : public FieldStencil<InviscidFlowField> {
protected:

public:

	/** Constructor
     * @param parameters Parameters of the problem
     */
     UFGHStencil(const Parameters & parameters);

    /** Apply the stencil in 2D
         * @param 
         * @param i Position in the X direction
         * @param j Position in the Y direction
         */
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j ); 
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
 
};
#endif //_UFGH_STENCIL_H_