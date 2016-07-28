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

        FLOAT DensityValue[213][63];
        FLOAT uValue[213][63];
        FLOAT vValue[213][63];
        FLOAT PressureValue[213][63];

        FLOAT ResidualValue[213][63];
        
        FLOAT JValue[213][63];
        FLOAT xi0Value[213][63];
        FLOAT xi1Value[213][63];
        FLOAT eta0Value[213][63];
        FLOAT eta1Value[213][63];

        FLOAT XValue[213][63];
        FLOAT YValue[213][63];
        
        FLOAT U0[213][63];
        FLOAT U1[213][63];
        FLOAT U2[213][63];
        FLOAT U3[213][63];

        FLOAT Ul0[213][63];
        FLOAT Ul1[213][63];
        FLOAT Ul2[213][63];
        FLOAT Ul3[213][63];

        FLOAT Ur0[213][63];
        FLOAT Ur1[213][63];
        FLOAT Ur2[213][63];
        FLOAT Ur3[213][63];

        FLOAT Ub0[213][63];
        FLOAT Ub1[213][63];
        FLOAT Ub2[213][63];
        FLOAT Ub3[213][63];

        FLOAT Ut0[213][63];
        FLOAT Ut1[213][63];
        FLOAT Ut2[213][63];
        FLOAT Ut3[213][63];


        FLOAT Fl0[213][63];
        FLOAT Fl1[213][63];
        FLOAT Fl2[213][63];
        FLOAT Fl3[213][63];

        FLOAT Fr0[213][63];
        FLOAT Fr1[213][63];
        FLOAT Fr2[213][63];
        FLOAT Fr3[213][63];

        FLOAT Gb0[213][63];
        FLOAT Gb1[213][63];
        FLOAT Gb2[213][63];
        FLOAT Gb3[213][63];

        FLOAT Gt0[213][63];
        FLOAT Gt1[213][63];
        FLOAT Gt2[213][63];
        FLOAT Gt3[213][63];


        FLOAT F0[213][63];
        FLOAT F1[213][63];
        FLOAT F2[213][63];
        FLOAT F3[213][63];

        FLOAT G0[213][63];
        FLOAT G1[213][63];
        FLOAT G2[213][63];
        FLOAT G3[213][63];

        FLOAT Fmid0[213][63];
        FLOAT Fmid1[213][63];
        FLOAT Fmid2[213][63];
        FLOAT Fmid3[213][63];

        FLOAT Gmid0[213][63];
        FLOAT Gmid1[213][63];
        FLOAT Gmid2[213][63];
        FLOAT Gmid3[213][63];

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
