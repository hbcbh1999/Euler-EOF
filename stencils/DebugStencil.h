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

        FLOAT DensityValue[241][151];
        FLOAT uValue[241][151];
        FLOAT vValue[241][151];
        FLOAT PressureValue[241][151];
        
        FLOAT JValue[241][151];
        FLOAT xi0Value[241][151];
        FLOAT xi1Value[241][151];
        FLOAT eta0Value[241][151];
        FLOAT eta1Value[241][151];

        FLOAT XValue[241][151];
        FLOAT YValue[241][151];
        
        FLOAT U0[241][151];
        FLOAT U1[241][151];
        FLOAT U2[241][151];
        FLOAT U3[241][151];

        FLOAT F0[241][151];
        FLOAT F1[241][151];
        FLOAT F2[241][151];
        FLOAT F3[241][151];

        FLOAT G0[241][151];
        FLOAT G1[241][151];
        FLOAT G2[241][151];
        FLOAT G3[241][151];

        FLOAT Fmid0[241][151];
        FLOAT Fmid1[241][151];
        FLOAT Fmid2[241][151];
        FLOAT Fmid3[241][151];

        FLOAT Gmid0[241][151];
        FLOAT Gmid1[241][151];
        FLOAT Gmid2[241][151];
        FLOAT Gmid3[241][151];

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
