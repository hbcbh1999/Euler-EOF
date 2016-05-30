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

        FLOAT DensityValue[143][53];
        FLOAT uValue[143][53];
        FLOAT vValue[143][53];
        FLOAT PressureValue[143][53];
        
        FLOAT JValue[143][53];
        FLOAT xi0Value[143][53];
        FLOAT xi1Value[143][53];
        FLOAT eta0Value[143][53];
        FLOAT eta1Value[143][53];

        FLOAT XValue[143][53];
        FLOAT YValue[143][53];
        
        FLOAT U0[143][53];
        FLOAT U1[143][53];
        FLOAT U2[143][53];
        FLOAT U3[143][53];

        FLOAT F0[143][53];
        FLOAT F1[143][53];
        FLOAT F2[143][53];
        FLOAT F3[143][53];

        FLOAT G0[143][53];
        FLOAT G1[143][53];
        FLOAT G2[143][53];
        FLOAT G3[143][53];

        FLOAT Fmid0[143][53];
        FLOAT Fmid1[143][53];
        FLOAT Fmid2[143][53];
        FLOAT Fmid3[143][53];

        FLOAT Gmid0[143][53];
        FLOAT Gmid1[143][53];
        FLOAT Gmid2[143][53];
        FLOAT Gmid3[143][53];

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
