#ifndef _INVISCID_GLOBAL_BOUNDARY_FACTORY_H_
#define _INVISCID_GLOBAL_BOUNDARY_FACTORY_H_

#include <string>
#include "Parameters.h"
#include "Iterators.h"
#include "../stencils/UFGHBoundaryStencil.h"
#include "../EulerSolver/InviscidFlowField.h"

/** Class that returns instances of the global boundary iterator. It also contains the stencils.
 * Right now, it works only with Dirichlet and periodic boundary conditions
 */
class InviscidGlobalBoundaryFactory{

    private:
        // List of all the stencils
        BoundaryStencil<InviscidFlowField> * _UFGHBoundaryStencil[6];    //! A stencil for each face
        BoundaryStencil<InviscidFlowField> * _wall;        //! Pointers to wall conditions
        BoundaryStencil<InviscidFlowField> * _outflow;     //! Pointers for the outflow conditions
        BoundaryStencil<InviscidFlowField> * _inlet;    //! For the velocity input
        const Parameters & _parameters;         //! Reference to the parameters

    public:

        /** Constructor. Will initialize all the references to the boundaries and create the
         * stencils.
         * @param parameters Parameters of the problem
         */
        InviscidGlobalBoundaryFactory(Parameters & parameters);

        /** Destructor. Necessary to remove the stencils at the end
         */
        ~InviscidGlobalBoundaryFactory();

        /** Returns an instance of the global boundary iterator for velocities.
         * @param flowField Flow field information
         */
         
        GlobalBoundaryIterator<InviscidFlowField> getUFGHGlobalBoundaryIterator(InviscidFlowField & inviscidFlowField);

};

#endif
