#ifndef _BOUNDARY_CONDITION_STENCIL_H_
#define _BOUNDARY_CONDITION_STENCIL_H_

#include "../DataStructures.h"
#include "../Stencil.h"
#include "../Parameters.h"
#include "../EulerSolver/InviscidFlowField.h"
#include "../stencils/DomainTransformStencil.h"

class InletBoundaryConditionStencil: public BoundaryStencil<InviscidFlowField>
{
private:
    FLOAT FreeStreamVelocity[3];
    FLOAT HeatCapacityRatio;
public:
	// Constructor
    InletBoundaryConditionStencil (const Parameters & parameters);

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

class WallBoundaryConditionStencil: public BoundaryStencil<InviscidFlowField>
{
private:
    FLOAT HeatCapacityRatio;
public:
	// Constructor
    WallBoundaryConditionStencil (const Parameters & parameters);

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


class OutflowBoundaryConditionStencil: public BoundaryStencil<InviscidFlowField>
{
private:
    FLOAT HeatCapacityRatio;
    FLOAT FreeStreamVelocity[3];

public:
	// Constructor
    OutflowBoundaryConditionStencil (const Parameters & parameters);

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