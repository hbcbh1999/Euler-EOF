#ifndef _HALFTIMESTEPUPDATE_STENCIL_H_
#define _HALFTIMESTEPUPDATE_STENCIL_H_

#include "../Stencil.h"
#include "../Parameters.h"
#include "../EulerSolver/InviscidFlowField.h"
#include <array>
// An explicit method
class HalfTimeStepUpdateStencil : public FieldStencil<InviscidFlowField> {
private:

    int sizeX, sizeY;
    FLOAT gamma;

    void halfTimeStepUpdate( InviscidFlowField & inviscidFlowField, int i, int j , std::array<FLOAT, 4> U, std::array<FLOAT, 4> F_l, std::array<FLOAT, 4> F_r, std::array<FLOAT, 4> G_b, std::array<FLOAT, 4> G_t, int edge);
    void halfTimeStepUpdate( InviscidFlowField & inviscidFlowField, int i, int j, int k, std::array<FLOAT, 5> U, std::array<FLOAT, 5> F_l, std::array<FLOAT, 5> F_r, std::array<FLOAT, 5> G_b, std::array<FLOAT, 5> G_t, std::array<FLOAT, 5> H_f, std::array<FLOAT, 5> H_back, int edge);

public:

	/** Constructor
     * @param parameters Parameters of the problem
     */
     HalfTimeStepUpdateStencil(const Parameters & parameters);

    /** Apply the stencil in 2D
         * @param 
         * @param i Position in the X direction
         * @param j Position in the Y direction
         */
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j ); 
    void apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
 
};
#endif //_HALFTIMESTEPUPDATE_STENCIL_H_