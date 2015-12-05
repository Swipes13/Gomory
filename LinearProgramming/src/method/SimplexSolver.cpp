#include "SimplexSolver.h"
#include <map>

using std::map;
using namespace solver;

void SimplexSolver::initialize(Task& task){
  _state = solver::SS_Support;
  _task = task;

  _sizeY = _task.equation().countX() + 1;
  _sizeX = _task.countLimits() + 1;

  _lblX.push_back(0);
  for (int i = 1; i < _sizeX; i++) 
    _lblX.push_back(i + _task.equation().countX());
  _lblY.push_back(-1);
  for (int i = 1; i < _sizeY; i++) _lblY.push_back(i);

  vector<Digit> digs;
  digs.push_back(_task.equation().forConst());

  for (int i = 0; i < _task.equation().countX(); i++)
    digs.push_back(-_task.equation().x(i));
  _table.push_back(digs);

  for (int i = 0; i < _task.countLimits(); i++) {
    vector<Digit> digs_;
    digs_.push_back(_task.limit(i).equation().forConst());
    for (int j = 0; j < _task.equation().countX(); j++)
      digs_.push_back(-_task.limit(i).equation().x(j));
    _table.push_back(digs_);
  }
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