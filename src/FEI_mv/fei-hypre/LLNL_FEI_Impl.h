/*BHEADER**********************************************************************
 * Copyright (c) 2006   The Regents of the University of California.
 * Produced at the Lawrence Livermore National Laboratory.
 * Written by the HYPRE team. UCRL-CODE-222953.
 * All rights reserved.
 *
 * This file is part of HYPRE (see http://www.llnl.gov/CASC/hypre/).
 * Please see the COPYRIGHT_and_LICENSE file for the copyright notice,
 * disclaimer, contact information and the GNU Lesser General Public License.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License (as published by the Free Software
 * Foundation) version 2.1 dated February 1999.
 *
 * HYPRE is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the IMPLIED WARRANTY OF MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the terms and conditions of the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * $Revision: 2.6 $
 ***********************************************************************EHEADER*/



/***************************************************************************
  Module:  LLNL_FEI_Impl.h
  Purpose: custom implementation of the FEI 
 ***************************************************************************/

#ifndef _LLNL_FEI_IMPL_H_
#define _LLNL_FEI_IMPL_H_

#include "HYPRE.h"
#include "_hypre_utilities.h"
#include "LLNL_FEI_LSCore.h"
#include "LLNL_FEI_Fei.h"
#include "LLNL_FEI_Solver.h"
#include "LLNL_FEI_Matrix.h"

/**************************************************************************
 definition of the class to capture the FEI information 
---------------------------------------------------------------------------*/

class LLNL_FEI_Impl
{
   MPI_Comm        mpiComm_;
   LLNL_FEI_Fei    *feiPtr_;
   LLNL_FEI_Solver *solverPtr_;
   LLNL_FEI_Matrix *matPtr_;
   int             solverLibID_;

public:

   LLNL_FEI_LSCore *lscPtr_;

public :

   LLNL_FEI_Impl(MPI_Comm comm);
   ~LLNL_FEI_Impl();
   int parameters(int numParams, char **paramString);

   int setSolveType(int solveType) { (void) solveType; return 0;}

   inline int initFields(int numFields, int *fieldSizes, int *fieldIDs)
                  {return feiPtr_->initFields(numFields,fieldSizes,fieldIDs);}

   inline int initElemBlock(int elemBlockID, int numElements, 
                   int numNodesPerElement, int *numFieldsPerNode, 
                   int **nodalFieldIDs, int numElemDOFFieldsPerElement, 
                   int *elemDOFFieldIDs, int interleaveStrategy)
                  {return feiPtr_->initElemBlock(elemBlockID, numElements, 
                   numNodesPerElement, numFieldsPerNode, nodalFieldIDs, 
                   numElemDOFFieldsPerElement, elemDOFFieldIDs, 
                   interleaveStrategy);}

   inline int initElem(int elemBlockID, int elemID, int *elemConn) 
                  {(void) elemBlockID; (void) elemID; (void) elemConn;
                   return 0;}

   inline int initSharedNodes(int nShared, int *sharedIDs, int *sharedLeng, 
                   int **sharedProcs)
                  {return feiPtr_->initSharedNodes(nShared,sharedIDs,
                                       sharedLeng,sharedProcs);}

   inline int initComplete() {return feiPtr_->initComplete();}

   inline int resetSystem(double s) {return feiPtr_->resetSystem(s);}

   inline int resetMatrix(double s) {return feiPtr_->resetMatrix(s);}

   inline int resetRHSVector(double s) {return feiPtr_->resetRHSVector(s);}

   inline int resetInitialGuess(double s) 
                  {return feiPtr_->resetInitialGuess(s);}

   inline int loadNodeBCs(int nNodes, int *nodeIDs, int fieldID, 
                   double **alpha, double **beta, double **gamma)
                  {return feiPtr_->loadNodeBCs(nNodes,nodeIDs,fieldID,
                                       alpha,beta,gamma);}

   inline int sumInElem(int elemBlock, int elemID, int *elemConn, 
                   double **elemStiff, double *elemLoad, int elemFormat)
                  {return feiPtr_->sumInElem(elemBlock,elemID,elemConn,
                                       elemStiff,elemLoad,elemFormat);}

   inline int sumInElemMatrix(int elemBlock, int elemID, int* elemConn, 
                   double **elemStiffness, int elemFormat)
                  {return feiPtr_->sumInElemMatrix(elemBlock,elemID,
                                       elemConn,elemStiffness,elemFormat);}

   inline int sumInElemRHS(int elemBlock, int elemID, int *elemConn,
                   double *elemLoad)
                  {return feiPtr_->sumInElemRHS(elemBlock,elemID,elemConn,
                                       elemLoad);}

   inline int loadComplete() {return feiPtr_->loadComplete();}

   int solve(int *status);

   inline int iterations(int *iterTaken) 
                  {return solverPtr_->iterations(iterTaken);}

   int residualNorm(int whichNorm, int numFields, int* fieldIDs,
                    double* norms);

   inline int getNumBlockActNodes(int blockID, int *nNodes)
                  {return feiPtr_->getNumBlockActNodes(blockID,nNodes);}
   inline int getNumBlockActEqns(int blockID, int *nEqns)
                  {return feiPtr_->getNumBlockActEqns(blockID,nEqns);}
   inline int getBlockNodeIDList(int blockID, int numNodes, int *nodeIDList)
                  {return feiPtr_->getBlockNodeIDList(blockID,numNodes,
                   nodeIDList);}
   inline int getBlockNodeSolution(int blockID, int numNodes, int *nodeIDList,
                   int *solnOffsets, double *solnValues)
                  {return feiPtr_->getBlockNodeSolution(blockID,numNodes,
                   nodeIDList,solnOffsets,solnValues);}

   inline int initCRMult(int CRListLen,int *CRNodeList,int *CRFieldList,
                   int *CRID)
                  {return feiPtr_->initCRMult(CRListLen,CRNodeList,
                   CRFieldList,CRID);}
   inline int loadCRMult(int CRID, int CRListLen, int *CRNodeList, 
                   int *CRFieldList, double *CRWeightList, double CRValue)
                  {return feiPtr_->loadCRMult(CRID,CRListLen,CRNodeList,
                   CRFieldList,CRWeightList,CRValue);}

private:
   int transferSolution();

};

#endif /* endif for _LLNL_FEI_IMPL_H_ */
