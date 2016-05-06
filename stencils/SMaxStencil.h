#ifndef _S_MAX_STENCIL_H_
#define _S_MAX_STENCIL_H_

#include "../Stencil.h"
#include "../Parameters.h"
#include "../EulerSolver/InviscidFlowField.h"


/** this class computes the maximum value of max(velocity)/meshsize for all grid cells.

 *  @author 
 */
class SMaxStencil : public FieldStencil<InviscidFlowField>, public BoundaryStencil<InviscidFlowField> {

    private:

        FLOAT _maxValues[3];  //! Stores the maximum module of every component

        /** Sets the maximum value arrays to the value of the cell if it surpasses the current one.
         *
         * 2D version of the function
         * @param inviscidFlowField Flow field
         * @param i Position in the X direction.
         * @param j Position in the Y direction.
         */
        void cellMaxValue(InviscidFlowField & inviscidFlowField, int i, int j);

        /** Sets the maximum value arrays to the value of the cell if it surpasses the current one.
         *
         * 3D version of the function
         * @param inviscidFlowField Flow field
         * @param i Position in the X direction.
         * @param j Position in the Y direction.
         * @param k Position in the Z direction.
         */
        void cellMaxValue(InviscidFlowField & inviscidFlowField, int i, int j, int k);

    public:

        /** Constructor
         *
         * @param parameters Parameters of the problem
         */
        SMaxStencil (const Parameters & parameters);

        //@ brief Body iterations
        //@{
        void apply (InviscidFlowField & inviscidFlowField, int i, int j);
        void apply (InviscidFlowField & inviscidFlowField, int i, int j, int k);
        //@}

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
        //@}

        /** Resets the maximum values to zero before computing the timestep
         */
        void reset ();

        /** Returns the array with the maximum modules of the components of the velocity,
         *  divided by the respective local meshsize
         */
        const FLOAT * getMaxValues() const;
};

#endif
