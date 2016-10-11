#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Configuration.h"
#include "parallelManagers/PetscParallelConfiguration.h"
#include "MeshsizeFactory.h"
#include <iomanip>
#include <array>
#include "../EulerSolver/InviscidSimulation.h"

int main (int argc, char *argv[]) {

    // Parallelization related. Initialize and identify
    // ---------------------------------------------------
    int rank;   // This processor's identifier
    int nproc;  // Number of processors in the group
    PetscInitialize(&argc, &argv, "petsc_commandline_arg", PETSC_NULL);
    MPI_Comm_size(PETSC_COMM_WORLD, &nproc);
    MPI_Comm_rank(PETSC_COMM_WORLD, &rank);
    std::cout << "Rank: " << rank << ", Nproc: " << nproc << std::endl;
    //-------------------------------------------------------
    // read configuration and store information in parameters object
    Configuration configuration(argv[1]);
    Parameters parameters;
    configuration.loadParameters(parameters);
    PetscParallelConfiguration parallelConfiguration(parameters);
    MeshsizeFactory::getInstance().initMeshsize(parameters);
    FlowField *flowField = NULL;
    InviscidFlowField *inviscidFlowField = NULL;
    InviscidSimulation *simulation = NULL;
 
    if (parameters.simulation.type=="inviscid")
    {
        inviscidFlowField = new InviscidFlowField(parameters);
        flowField = inviscidFlowField;
        if(flowField == NULL)
        { 
          handleError(1, "flowField==NULL!"); 
        }
        simulation = new InviscidSimulation(parameters,*inviscidFlowField);
    }
    else 
    {
      handleError(1, "Unknown simulation type! Currently supported: inviscid");
    }
    // call initialization of simulation (initialize flow field)
    if(simulation == NULL)
    { 
      handleError(1, "simulation==NULL!"); 
    }
    ((InviscidSimulation*) simulation)->inviscid_initialization();

    FLOAT time = 0.0;
    FLOAT timeStdOut=parameters.stdOut.interval;
    int timeSteps = 0;  
    int OutputTimes = 1;
    FLOAT residual = 1;

    while (timeSteps < 4e5 && residual > 1e-5)
    {
        ((InviscidSimulation*) simulation)->inviscid_solveTimeSteps();
        residual = ((InviscidSimulation*) simulation)->convergenceCheck();
        if (time > parameters.vtk.interval*OutputTimes)
        {
            ((InviscidSimulation*) simulation)->plotGeoVTK(timeSteps);
            ((InviscidSimulation*) simulation)->debugPlot(timeSteps);
            OutputTimes++;
        }
        time += parameters.timestep.dt;
        std::cout << "timestep: " << timeSteps << " " << parameters.timestep.dt << " " << residual <<  std::endl;
        timeSteps++;
    // ((InviscidSimulation*) simulation)->debugPlot(timeSteps);

    }
    ((InviscidSimulation*) simulation)->plotGeoVTK(timeSteps);
    ((InviscidSimulation*) simulation)->debugPlot(timeSteps);
    delete simulation; simulation=NULL;
    delete flowField;  flowField= NULL;
    delete inviscidFlowField;  inviscidFlowField= NULL;


    PetscFinalize();

}
