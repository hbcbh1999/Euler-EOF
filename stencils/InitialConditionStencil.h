#ifndef _INITIAL_CONDITION_STENCIL_H_
#define _INITIAL_CONDITION_STENCIL_H_

#include "../Stencil.h"
#include "../Parameters.h"
#include "../EulerSolver/InviscidFlowField.h"

/** this class computes the maximum value of max(velocity)/meshsize for all grid cells.

 *  @author 
 */
class InitialConditionStencil : public FieldStencil<InviscidFlowField>
{
    private:
        FLOAT HeatCapacityRatio;
        FLOAT FreeStreamVelocity;
        int sizeX, sizeY;
        std::string scenario;
    public:

        /** Constructor
         *
         * @param parameters Parameters of the problem
         */
        InitialConditionStencil (const Parameters & parameters);

        //@ brief Body iterations
        //@{
        void apply (InviscidFlowField & inviscidFlowField, int i, int j);
        void apply (InviscidFlowField & inviscidFlowField, int i, int j, int k);
        //@}

};

#endif
