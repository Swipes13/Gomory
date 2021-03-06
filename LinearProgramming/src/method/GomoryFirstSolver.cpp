#include "GomoryFirstSolver.h"

using namespace solver;

bool GomoryFirstSolver::_stepSupportWork(){
  if (!_preOptimalWork()) {
    _state = SS_ErrorOptimal;
    _errorMessage = "PreOptimal plan(lMethod) error.";
    return false;
  }
  _state = SS_Optimal;
  return true;
}

bool GomoryFirstSolver::_stepOptimalWork(){
  int k = -1;
  for (int i = 0; i < _sizeX; i++) {
    if (_table[i][0].digitType() != math::DigitType::DT_Definite) {
      _state = solver::SS_ErrorOptimal;
      _errorMessage = "Optimal plan. Onde Digit is undefined.";
      return false;
    }
    if (_table[i][0] < 0) { k = i; break; }
  }

  if (k == -1) {
    _state = solver::SS_OptimalInteger;
    return true;
  }

  _lMethod(k, _generateColumnsPreOptimal(k));
//  _cutTableException(k);

  return true;
}

bool GomoryFirstSolver::_preOptimalWork(){
  SimplexSolver tempSolver;
  Task* newTask = new Task(*_task);

  Digit** digits = new Digit*[_task->equation()->countX()];
  for(int i = 0; i < _task->equation()->countX(); i++)
    digits[i] = new Digit(1);

  Equation* eq = new Equation(_task->equation()->countX(), digits);
  newTask->setEquation(eq);
  tempSolver.initialize(newTask);

  while (tempSolver.stepWork());
  if (tempSolver.state() != SS_Finish)
    return false;

  auto simplexResult = tempSolver.result()->getInteger();
  vector<Digit> line;
  line.push_back(simplexResult);
  for (int i = 0; i < _sizeY - 1; i++)
    line.push_back(1);

  _table.push_back(line);
  _lblX.push_back(_lblX.size());
  _sizeX++;
  int k = _sizeX - 1;
  _lMethod(k, _generateColumnsPreOptimal(k));
  _cutTableException(k);

  return true;
}

vector<vector<Digit>>& GomoryFirstSolver::_generateColumnsPreOptimal(int k){
  vector<vector<Digit>>* clmns = new vector<vector<Digit>>;
  for (int j = 1; j < _sizeY; j++){
    vector<Digit> clm;
    for (int i = 0; i < _sizeX; i++)
      clm.push_back(_table[i][j]);
    clmns->push_back(clm);
  }
  return *clmns;
}

/*bool GomoryFirstSolver::_stepOptimalIntegerWork(){
  if (_usePreOptimal){
    if (!_preOptimalWork()) {
      _state = SS_ErrorOptimalInteger;
      return false;
    }
    _usePreOptimal = false;
  }

  return __stepOptimalIntegerWork();
}*/