#ifndef _UFGH_BOUNDARY_STENCIL_H_
#define _UFGH_BOUNDARY_STENCIL_H_

#include "../Parameters.h"
#include "../DataStructures.h"
#include "../Stencil.h"
#include "../Parameters.h"
#include "../EulerSolver/InviscidFlowField.h"

class UFGHInletBoundaryStencil: public BoundaryStencil<InviscidFlowField>
{
private:
    FLOAT J, xi_x, xi_y, eta_x, eta_y , xi, eta;
    FLOAT U_g[4],F_g[4],G_g[4];   // State varibles U and flux F,G in ghost cell;
    FLOAT U_i[4],F_i[4],G_i[4];   // State varibles U and flux F,G in the first interior cell;
    FLOAT U_b[4],F_b[4],G_b[4];   // State varibles U and flux F,G in the first interior cell;
    FLOAT pv_fs[4], pv_b[4], pv_i[4], pv_g[4];  // primative varibles on freestream, boundary, interiorm and ghost cell
    FLOAT HeatCapacityRatio;

public:
	// Constructor
    UFGHInletBoundaryStencil (const Parameters & parameters);

    //@brief Functions for the 2D problem. Coordinates entered in alphabetical order.
    void applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j );

    // TODO: 3D
    void applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyFrontWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyBackWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    //@}	
};

class UFGHWallBoundaryStencil: public BoundaryStencil<InviscidFlowField>
{
    private:

    FLOAT J, xi_x, xi_y, eta_x, eta_y , xi, eta;
    FLOAT U_g[4],F_g[4],G_g[4];   // State varibles U and flux F,G in ghost cell;
    FLOAT U_i[4],F_i[4],G_i[4];   // State varibles U and flux F,G in the first interior cell;
    FLOAT U_b[4],F_b[4],G_b[4];   // State varibles U and flux F,G in the first interior cell;
    FLOAT pv_fs[4], pv_b[4], pv_i[4], pv_g[4];  // primative varibles on freestream, boundary, interiorm and ghost cell
    FLOAT HeatCapacityRatio;

public:
	// Constructor
    UFGHWallBoundaryStencil (const Parameters & parameters);

    void applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j );

    // TODO: 3D
    void applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyFrontWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyBackWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    //@}	
};


class UFGHOutflowBoundaryStencil: public BoundaryStencil<InviscidFlowField>
{
    private:

    FLOAT J, xi_x, xi_y, eta_x, eta_y , xi, eta;
    FLOAT U_g[4],F_g[4],G_g[4];   // State varibles U and flux F,G in ghost cell;
    FLOAT U_i[4],F_i[4],G_i[4];   // State varibles U and flux F,G in the first interior cell;
    FLOAT U_b[4],F_b[4],G_b[4];   // State varibles U and flux F,G in the first interior cell;
    FLOAT pv_fs[4], pv_b[4], pv_i[4], pv_g[4];  // primative varibles on freestream, boundary, interiorm and ghost cell
    FLOAT HeatCapacityRatio;
public:
	// Constructor
    UFGHOutflowBoundaryStencil (const Parameters & parameters);

    void applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j );
    void applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j );

    // TODO: 3D
    void applyLeftWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyRightWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyBottomWall ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyTopWall    ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyFrontWall  ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    void applyBackWall   ( InviscidFlowField & inviscidFlowField, int i, int j, int k );
    //@}	
};

#endif