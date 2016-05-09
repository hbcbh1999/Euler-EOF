#ifndef _DEBUG_STENCIL_H_
#define _DEBUG_STENCIL_H_

#include "../Definitions.h"
#include "../Parameters.h"
#include "../Stencil.h"
#include "../EulerSolver/InviscidFlowField.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

class DebugStencil : public FieldStencil<InviscidFlowField>, public BoundaryStencil<InviscidFlowField>  {
    private:
        int sizeX, sizeY;

        FLOAT DensityValue[243][153];
        FLOAT uValue[243][153];
        FLOAT vValue[243][153];
        FLOAT PressureValue[243][153];
        
        FLOAT JValue[243][153];
        FLOAT xi0Value[243][153];
        FLOAT xi1Value[243][153];
        FLOAT eta0Value[243][153];
        FLOAT eta1Value[243][153];

        FLOAT XValue[243][153];
        FLOAT YValue[243][153];
        
        FLOAT U0[243][153];
        FLOAT U1[243][153];
        FLOAT U2[243][153];
        FLOAT U3[243][153];

        FLOAT F0[243][153];
        FLOAT F1[243][153];
        FLOAT F2[243][153];
        FLOAT F3[243][153];

        FLOAT G0[243][153];
        FLOAT G1[243][153];
        FLOAT G2[243][153];
        FLOAT G3[243][153];

        FLOAT Fmid0[243][153];
        FLOAT Fmid1[243][153];
        FLOAT Fmid2[243][153];
        FLOAT Fmid3[243][153];

        FLOAT Gmid0[243][153];
        FLOAT Gmid1[243][153];
        FLOAT Gmid2[243][153];
        FLOAT Gmid3[243][153];

    public:

        DebugStencil ( const Parameters & parameters );

        void apply ( InviscidFlowField & inviscidFlowField, int i, int j );
        void apply ( InviscidFlowField & inviscidFlowField, int i, int j, int k );        
        void write ( InviscidFlowField & inviscidflowField, int timeStep );

        void applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j );
        void applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j );
        void applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j );
        void applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j );


        void applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k);
        void applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k);
        void applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k);
        void applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j, int k);
        void applyFrontWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k);
        void applyBackWall    ( InviscidFlowField & inviscidFlowField, int i, int j, int k);
};

#endif
