#include "SimplexSolver.h"
#include <map>

using std::map;
using namespace solver;

void SimplexSolver::_initialize(){
  _sizeX = _task->countLimits() + 1;

  _lblX.push_back(-1);
  int xInd = _task->equation()->countX();
  for(int i = 0; i < _sizeX - 1; i++) {
    _task->limit(i)->limitType() == LimitType::LT_Equal ?
      _lblX.push_back(0) : _lblX.push_back(++xInd);
  }
  _addLimitsToTable();
}

bool SimplexSolver::_stepSupportWork() {
  vector<int> negStr;

  for(int i = 0; i < _sizeX - 1; i++)
  if(_table[i][0] < 0) negStr.push_back(i);

  if(negStr.size() == 0) {
    _state = solver::SS_Optimal;
    return true;
  }
  vector<int> accElemClmns;

  for(auto ind : negStr) {
    for(int i = 1; i < _sizeY - 1; i++) {
      if(_table[ind][i] < 0)
        accElemClmns.push_back(i);
    }
  }

  if(accElemClmns.size() == 0) {
    _errorMessage = "Error in finding support plan. System is conflicting.";
    return false;
  }

  for(auto ind : accElemClmns) {
    map<int, Digit> divisions;
    for(int i = 0; i < _sizeX-1; i++) {
      auto div = _table[i][0] / _table[i][ind];
      if(div > 0) divisions[i] = div;
    }
    if(divisions.size() <= 0) continue;

    std::pair<int, Digit> min = *divisions.begin();
    for(auto& elem : divisions) {
      if(elem.second < min.second)
        min = elem;
    }
    int r = min.first;

    _modifyJordanException(r, ind);
    return true;
  }
  _errorMessage = "Error in finding support plan. System is conflicting.";
  return false;
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

  _errorMessage = "Error in finding optimal plan. Function not bonds.";
  _state = solver::SS_ErrorOptimal;
  return false;
}

void SimplexSolver::_afterMJEWork(int r, int l) {
  auto temp = _lblY[l];
  _lblY[l] = _lblX[r];
  _lblX[r] = temp;
}