#ifndef _VTKGEO_STENCIL_H_
#define _VTKGEO_STENCIL_H_

#include "../Definitions.h"
#include "../Parameters.h"
#include "../Stencil.h"
#include "../FlowField.h"
#include "../EulerSolver/InviscidFlowField.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

/** Stencil for writting VTK files
 *
 * When iterated with, creates a VTK file.
 */
class VTKGeoStencil : public FieldStencil<InviscidFlowField> {
    private:
        // bool _inviscid;
        std::stringstream pointData,cellData,cellType,pressureValue;
        Meshsize* _meshsize;
        int _dim;
        int cellRefNum;
        int sizeX, sizeY;
        std::string _prefix;
    public:

        /** Constructor
         *
         * @param prefix String with the prefix of the name of the VTK files
         */
        VTKGeoStencil ( const Parameters & parameters );

        /** 2D operation for one position
facfa         *
         * @param flowField State of the flow field
         * @param i Position in the x direction
         * @param j Position in the y direction
         */
        void apply ( InviscidFlowField & inviscidFlowField, int i, int j );

        /** 3D operation for one position
         *
         * @param flowField State of the flow field
         * @param i Position in the x direction
         * @param j Position in the y direction
         * @param k Position in the z direction
         */
        void apply ( InviscidFlowField & inviscidflowField, int i, int j, int k );

        /** Writes the information to the file
         * @param flowField Flow field to be written
         */
        void write ( InviscidFlowField & inviscidflowField, int timeStep );
        void clear ();

};

#endif