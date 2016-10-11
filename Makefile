#### The petsc environment can also be fixed in the makefile
# PETSC_DIR =
# PETSC_ARCH =
PETSC_DIR = /home/moulin/Downloads/petsc-3.5.4
include ${PETSC_DIR}/conf/variables

# default gnu compiler (currently not used)
# CC = g++
# compiler wrapper for mac-cluster
#CC = mpiCC
# compiler on Ubuntu
#
#
CC = mpic++
CFLAGS = -Wall -std=c++0x
SRCDIR = ./
INCLUDE = -I. -Istencils ${PETSC_CC_INCLUDES}


NSMAIN = main_test.o

OBJ = DataStructures.o Configuration.o 3rdparty/tinyxml2/tinyxml2.o SimpleTimer.o

NSOBJ = FlowField.o LinearSolver.o Meshsize.o\
stencils/MaxUStencil.o \
solvers/SORSolver.o solvers/PetscSolver.o \
stencils/VTKStencil.o \
EulerSolver/InviscidFlowField.o \
stencils/PointCoordinateStencil.o \
stencils/TransformMetricesStencil.o \
stencils/InitialConditionStencil.o \
stencils/DomainTransformStencil.o \
stencils/ReconstructStencil.o \
stencils/HalfTimeStepUpdateStencil.o \
stencils/BoundaryConditionStencil.o \
stencils/SMaxStencil.o \
stencils/MUSCLStencil.o\
stencils/RecoverStencil.o\
stencils/ResidualStencil.o\
stencils/DebugStencil.o\
stencils/VTKGeoStencil.o\
parallelManagers/PetscParallelConfiguration.o \
EulerSolver/InviscidGlobalBoundaryFactory.o\

all: ns

ns: $(OBJ) $(NSOBJ) $(NSMAIN)
	$(CC) -o ns $(OBJ) $(NSOBJ) $(NSMAIN) $(PETSC_KSP_LIB) -lstdc++ $(CFLAGS)


%.o: %.cpp
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $*.o $*.cpp $(PETSC_KSP_LIB) -lstdc++

cleanall clean:
	for name in  ns main.o main_test.o $(NSOBJ) $(OBJ) ; do \
	if [ -f $$name ]; then rm $$name; fi; \
	done;
