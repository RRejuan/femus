/*=========================================================================

 Program: FEMUS
 Module: LinearImplicitSystem
 Authors: Simone Bnà
 
 Copyright (c) FEMTTU
 All rights reserved. 

 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef __linear_implicit_system_h_
#define __linear_implicit_system_h_

//----------------------------------------------------------------------------
// includes :
//----------------------------------------------------------------------------
#include "ImplicitSystem.hpp"
#include "LinearEquationSolver.hpp"
#include "MgTypeEnum.hpp"
//------------------------------------------------------------------------------
// Forward declarations
//------------------------------------------------------------------------------

class LinearImplicitSystem : public ImplicitSystem {

public:

  /** Constructor.  Optionally initializes required data structures. */
  LinearImplicitSystem (MultiLevelProblem& ml_probl, const std::string& name, const unsigned int number);

  /** Destructor */
  virtual ~LinearImplicitSystem();
  
  /** The type of the parent. */
  typedef ImplicitSystem Parent;
  
  /** Solves the system. */
  virtual void solve ();
  
  /** Clear all the data structures associated with the system. */
  virtual void clear();

  /** Init the system PDE structures */
  virtual void init();
  
   /**
   * The \p NonlinearSolver defines the default interface used to
   * solve the nonlinear_implicit system.  This class handles all the
   * details of interfacing with various nonlinear algebra packages
   * like PETSc or LASPACK. Up to now also for the nonlinear case we use linear_solvers, in future we will add the nonlinear solver
   */
   vector<LinearEquationSolver*> _LinSolver;
   
   /** Set the max number of linear iterationsfor solving Ax=b */
   void SetMaxNumberOfLinearIterations(unsigned int max_lin_it) {_n_max_linear_iterations = max_lin_it;};
   
   /** Get the number of linear iterations for solving Ax=b*/
   unsigned int GetNumberOfLinearIterations() const {return _n_linear_iterations;}; 
   
   /** Get the final Linear Residual of the linear problem Ax=b*/
   double GetFinalLinearResidual() const {return _final_linear_residual;}; 
   
   /** Get the absolute convergence tolerance for the linear problem Ax=b*/
   double GetAbsoluteConvergenceTolerance() const {return _absolute_convergence_tolerance;}; 
   
   /** Set the absolute convergence tolerance for the linear problem Ax=b*/
   void SetAbsoluteConvergenceTolerance(double absolute_convergence_tolerance) { _absolute_convergence_tolerance = absolute_convergence_tolerance;};
   
   /** Set a parameter option for the SparseMatrix A */
   virtual void SetMatrixOption(MatOption op, bool flag);
   
   /** Set the type of multigrid */
   void SetMgType(const MgType mgtype) {_mg_type = mgtype;};
 

protected:
  
  /** The number of linear iterations required to solve the linear system Ax=b. */
  unsigned int _n_linear_iterations;

  /** The final residual for the linear system Ax=b. */
  double _final_linear_residual;
  
  /** The threshold residual for the linear system Ax=b. */
  double _absolute_convergence_tolerance;
  
  /** The max number of linear iterations */
  unsigned int _n_max_linear_iterations;

  /** The type of multigrid, F-cyle, V-cycle, M-cycle */
  MgType _mg_type;
  
  /** Create the Prolongator matrix for the Multigrid solver */
  void Prolongator(const unsigned &gridf);
  
  /** Create the Restrictor matrix for the Multigrid solver */
  void Restrictor(const unsigned &gridf, const unsigned &gridn, 
					    const unsigned &non_linear_iteration, const unsigned &linear_iteration, const bool &full_cycle);
  
  /** Prolongate the solution to a finer level */
  void ProlongatorSol(unsigned gridf);
  
  /** Create the Prolongator Matrix in order to get the coarser matrix for the Algebraic Multigrid Solver */ 
  void BuildProlongatorMatrix(unsigned gridf, const char pdename[]);
  
  
private:

  /** Initialize the PDE system structure */
  void CreateSystemPDEStructure();

};

inline void LinearImplicitSystem::SetMatrixOption(MatOption op, bool flag)
{
//   for (unsigned ig=0; ig<_equation_systems.GetNumberOfGrid(); ig++) {
//     MatSetOption(_LinSolver[ig]->_KK->mat(),op,flag);
//   }
}

#endif