#include "SimplexSolver.h"
#include <map>

using std::map;
using namespace solver;

void SimplexSolver::_initialize(){
  _sizeX = _task.countLimits() + 1;

  _lblX.push_back(-1);
  int xInd = _task.equation().countX();
  for(int i = 0; i < _sizeX - 1; i++) {
    _task.limit(i).limitType() == LimitType::LT_Equal ? 
      _lblX.push_back(0) : _lblX.push_back(++xInd);
    ;
  }
  
  _addLimitsToTable();
}

bool SimplexSolver::_stepSupportWork() {
  //TODO : DO!
  _state = solver::SS_Optimal;
  return true;
}

bool SimplexSolver::_stepOptimalWork() {
  vector<int> ll;
  for (int i = 0; i < _sizeY; i++) {
    if (_table[0][i] < 0)
      ll.push_back(i);
  }

  if (ll.size() == 0) {
    _state = solver::SS_OptimalInteger;
    return true;
  }

  for (auto l : ll) {
    map<int, Digit> toChoose;
    for (int i = 0; i < _sizeX; i++) {
      if (_table[i][l] > 0)
        toChoose[i] = _table[i][0] / _table[i][l];
    }
    if (toChoose.size() == 0) continue;

    std::pair<int, Digit> min = *toChoose.begin();
    for (auto& elem : toChoose) {
      if (elem.second < min.second)
        min = elem;
    }
    int r = min.first;

    _modifyJordanException(r, l);
    return true;
  }

  _state = solver::SS_ErrorOptimal;
  return false;
}

void SimplexSolver::_afterMJEWork(int r, int l) {
  auto temp = _lblY[l];
  _lblY[l] = _lblX[r];
  _lblX[r] = temp;
}