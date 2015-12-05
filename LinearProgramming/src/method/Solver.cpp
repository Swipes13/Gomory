#include "Solver.h"

using namespace solver;

Solver::Solver(){
  _state = SS_NotInit;
}

bool Solver::stepWork() {
  switch(_state) {
  case solver::SS_Support:
    return _stepSupportWork();
  case solver::SS_Optimal:
    return _stepOptimalWork();
  case solver::SS_OptimalInteger:
    return _stepOptimalIntegerWork();
  case solver::SS_Finish:
    return false;
  default: return false;
  }
}

bool Solver::_stepOptimalIntegerWork() {
  _state = SS_Finish;
  return false;
}

void Solver::_modifyJordanException(int r, int l) {
  for(int i = 0; i < _sizeX; i++) {
    if(i == r) continue;
    for(int j = 0; j < _sizeY; j++) {
      if(j == l) continue;
      _table[i][j] = _table[i][j] - _table[r][j] * _table[i][l] / _table[r][l];
    }
  }
  for(int j = 0; j < _sizeY; j++) {
    if(j == l) continue;
    _table[r][j] /= _table[r][l];
  }

  for(int i = 0; i < _sizeX; i++) {
    if(i == r) continue;
    _table[i][l] /= -_table[r][l];
  }
  _table[r][l] = Digit(1) / _table[r][l];

  _afterMJEWork(r, l);
}

SolverState Solver::state() {
  return _state;
}

Digit& Solver::result(){
  if (_state != SS_Finish)
    return *(new Digit(0));
  return _table[0][0];
}