#ifndef _TRANSFORM_FIELD_H_
#define _TRANSFORM_FIELD_H_

#include "../DataStructures.h"
#include "../Parameters.h"
#include "../FlowField.h"

class InviscidFlowField : public FlowField {

    private:
        ScalarField _density;
        VectorField _xi;
        VectorField _eta;
        // VectorField _phi; // TODO: 3D extension
        ScalarField _J;
        VectorField _pointCoordinate;

        ScalarField _energy;

        // @Mou: For debugging purpose right now all the intermedient variables are stored.
        FluxField _U;
        FluxField _F;
        FluxField _G;
        FluxField _H;

        FluxField _Uhat;
        FluxField _Fhat;
        FluxField _Ghat;
        FluxField _Hhat;
        // Interface Flux
        FluxField _Fmid;
        FluxField _Gmid;
        FluxField _Hmid;


//
    public:
        InviscidFlowField (const Parameters & parameters);
        /** Get domain transformation metrics field
         * @return Reference to inviscid field
         */

        ScalarField & getDensity();
        VectorField & getXi ();
        VectorField & getEta ();
        ScalarField & getJ ();
        VectorField & getPointCoordinate();
        ScalarField & getEnergy();

        // // Flux
        FluxField & getU();
        FluxField & getF();
        FluxField & getG();
        FluxField & getH();
        // Transformed Flux
        FluxField & getUhat();
        FluxField & getFhat();
        FluxField & getGhat();
        FluxField & getHhat();

        FluxField & getFmid();
        FluxField & getGmid();
        FluxField & getHmid();
};

#endif
