#include "Solver.h"

using namespace solver;

bool Solver::stepWork() {
  switch(_state) {
  case solver::SS_Start:
    _state = SS_Support;
    return _stepSupportWork();
  case solver::SS_Support:
    return _stepSupportWork();
  case solver::SS_Optimal:
    return _stepOptimalWork();
  case solver::SS_Finish:
    return true;
  default: return false;
  }
}