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

        FLOAT DensityValue[123][78];
        FLOAT uValue[123][78];
        FLOAT vValue[123][78];
        FLOAT PressureValue[123][78];
        
        FLOAT JValue[123][78];
        FLOAT xi0Value[123][78];
        FLOAT xi1Value[123][78];
        FLOAT eta0Value[123][78];
        FLOAT eta1Value[123][78];

        FLOAT XValue[123][78];
        FLOAT YValue[123][78];
        
        FLOAT U0[123][78];
        FLOAT U1[123][78];
        FLOAT U2[123][78];
        FLOAT U3[123][78];

        FLOAT F0[123][78];
        FLOAT F1[123][78];
        FLOAT F2[123][78];
        FLOAT F3[123][78];

        FLOAT G0[123][78];
        FLOAT G1[123][78];
        FLOAT G2[123][78];
        FLOAT G3[123][78];

        FLOAT Fmid0[123][78];
        FLOAT Fmid1[123][78];
        FLOAT Fmid2[123][78];
        FLOAT Fmid3[123][78];

        FLOAT Gmid0[123][78];
        FLOAT Gmid1[123][78];
        FLOAT Gmid2[123][78];
        FLOAT Gmid3[123][78];

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
