#include "Solver.h"
#include <iostream>
#include <map>

using namespace solver;
using std::map;
using std::cout;

Solver::Solver(){
  _state = SS_NotInit;
}

void Solver::initialize(Task& task) {
  _state = solver::SS_ZeroStrs;
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
  _zeroStr.push_back(false);

  _initialize();
}

bool Solver::stepWork() {
  switch(_state) {
  case solver::SS_ZeroStrs:
    return _computeZeroStrs();
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

bool Solver::_computeZeroStrs() {
  for(int i = 0; i < static_cast<int>(_zeroStr.size()); i++) {
    if(_zeroStr[i]) {
      _zeroStr[i] = false;

      map<int, Digit> divisions;

      for(int j = 0; j < _sizeY - 1; j++) {
        if(_table[i][j] >= 0) 
          divisions[j] = _table[i][0] / _table[i][j];
      }

      if(divisions.size() <= 0) {
        _state = SS_ErrorZeroStrs;
        return false;
      }

      std::pair<int, Digit> min = *divisions.begin();
      for(auto& elem : divisions) {
        if(elem.second < min.second)
          min = elem;
      }
      int l = min.first;

      _modifyJordanException(i,l);
      _cutTable(l);
    }
  }
  _state = SolverState::SS_Support;
  return true;
}

void Solver::_cutTable(int l) {
  for(int i = 0; i < _sizeX; i++) {
    for(int j = l; j < _sizeY - 1; j++) 
      std::swap(_table[i][j], _table[i][j + 1]);
    
    _table[i].pop_back();
  }
  for(int j = l; j < _sizeY - 1; j++) 
    std::swap(_lblY[j], _lblY[j + 1]);
  _lblY.pop_back();
  _sizeY--;
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

    _task.limit(i).limitType() == LimitType::LT_Equal ?
      _zeroStr.push_back(true) : _zeroStr.push_back(false);

    for(int j = 0; j < _task.equation().countX(); j++)
      digs_.push_back(-_task.limit(i).equation().x(j));
    _table.push_back(digs_);
  }
}

Digit& Solver::table(int i, int j) {
  return _table[i][j];
}

int Solver::sizeX() {
  return _sizeX;
}

int Solver::sizeY() {
  return _sizeY;
}

int Solver::labelX(int index) {
  return _lblX[index];
}

int Solver::labelY(int index) {
  return _lblY[index];
}

std::string Solver::getError() {
  switch(_state) {
  case solver::SS_NotInit:
    return "NotInit!";
  case solver::SS_ErrorZeroStrs:
    return "Zero strings!";
  case solver::SS_ErrorSupport:
    return "Support!";
  case solver::SS_ErrorOptimal:
    return "Optimal!";
  case solver::SS_ErrorOptimalInteger:
    return "Optimal Integer!";
  default: return "Undefined!";
  }
}

std::string Solver::getResult() {
  if(_state != SS_Finish)
    return getError();
  
  std::string ret;
  int numBazis = _task.equation().countX();
  for(int i = 1; i <= numBazis; i++) {
    int ind = -1;
    for(int j = 0; j < _lblX.size(); j++) {
      if(_lblX[j] == i) {
        ind = j;
        break;
      }
    }
    char * dest = new char[10];
    ret += "x" + std::string(itoa(i, dest, 10));
    if(ind == -1) {
      ret += " = 0\t";
      continue;
    }
    ret += " = " + _table[ind][0].toString() + ", ";
  }
  ret += "Q = " + result().toString();
  return ret;
}