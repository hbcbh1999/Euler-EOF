#ifndef _TRANSFORM_FIELD_H_
#define _TRANSFORM_FIELD_H_

#include "../DataStructures.h"
#include "../Parameters.h"
#include "../FlowField.h"

class InviscidFlowField : public FlowField {

    private:
        VectorField _xi;
        VectorField _eta;
        // VectorField _phi; // TODO: 3D extension
        ScalarField _J;
        VectorField _pointCoordinate;
//
    public:
        InviscidFlowField (const Parameters & parameters);
        /** Get domain transformation metrics field
         * @return Reference to inviscid field
         */
        VectorField & getXi ();
        VectorField & getEta ();
        ScalarField & getJ ();
        VectorField & getPointCoordinate();

};

#endif
