#include "Solver.h"

using namespace solver;

Solver::Solver(){
  _state = SS_NotInit;
}

void Solver::initialize(Task& task) {
  _state = solver::SS_Support;
  _task = task;
  _makeUnifiedEquations();

  _sizeY = _task.equation().countX() + 1;
  _lblY.push_back(-1);
  for(int i = 1; i < _sizeY; i++) _lblY.push_back(i);

  vector<Digit> digs;
  digs.push_back(_task.equation().forConst());
  for(int i = 0; i < _task.equation().countX(); i++)
    digs.push_back(-_task.equation().x(i));
  _table.push_back(digs);

  _initialize();
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

void Solver::_makeUnifiedEquations() {
  if(this->_task.taskType() == TaskType::TT_Min) {
    this->_task.equation().changeSigns();
    this->_task.setTaskType(TaskType::TT_Max);
  }
  for(int i = 0; i < this->_task.countLimits(); i++) {
    switch(this->_task.limit(i).limitType()) {
    case LimitType::LT_Less:
      this->_task.limit(i).equation().changeSigns();
      this->_task.limit(i).setLimitType(LimitType::LT_More);
      break;
    case LimitType::LT_Equal:
      // TODO: null-strs!
      break;
    default: break;
    }
  }
}

void Solver::_addLimitsToTable() {
  for(int i = 0; i < _task.countLimits(); i++) {
    vector<Digit> digs_;
    digs_.push_back(_task.limit(i).equation().forConst());
    for(int j = 0; j < _task.equation().countX(); j++)
      digs_.push_back(-_task.limit(i).equation().x(j));
    _table.push_back(digs_);
  }
}