#include "GomoryFirstSolver.h"

using namespace solver;

/*bool GomoryFirstSolver::_stepSupportWork(){
  _state = SS_Optimal;
  return true;
}*/

bool GomoryFirstSolver::_stepOptimalWork(){
  _state = SS_OptimalInteger;
  return true;
}