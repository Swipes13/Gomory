#include "GomoryFirstSolver.h"

using namespace solver;

bool GomoryFirstSolver::_stepSupportWork(){
  if (!_preOptimalWork()) {
    _state = SS_ErrorOptimal;
    return false;
  }
  _state = SS_Optimal;
  return true;
}

bool GomoryFirstSolver::_preOptimalWork(){
  SimplexSolver tempSolver;
  Task newTask = Task(_task);

  Digit** digits = new Digit*[_task.equation().countX()];
  for (int i = 0; i < _task.equation().countX(); i++)
    digits[i] = new Digit(1);

  Equation eq = Equation(_task.equation().countX(), digits);
  newTask.setEquation(eq);
  tempSolver.initialize(newTask);

  while (tempSolver.stepWork());
  if (tempSolver.state() != SS_Finish)
    return false;

  auto simplexResult = tempSolver.result().getInteger();
  vector<Digit> line;
  line.push_back(simplexResult);
  for (int i = 0; i < _sizeY - 1; i++)
    line.push_back(1);

  _table.push_back(line);
  _lblX.push_back(_lblX.size());


  int k = _sizeX - 1;

  vector<vector<Digit>> clmns;
  for (int j = 1; j < _sizeY; j++){
    vector<Digit> clm;
    for (int i = 0; i < _sizeX; i++)
      clm.push_back(_table[i][j]);
    clmns.push_back(clm);
  }

  int l = 0;
  auto min = clmns[l];
  for (int i = 1; i < static_cast<int>(clmns.size()); i++){
    if (_compareLexicalMinimal(clmns[i], min)) {
      min = clmns[i];
      l = i;
    }
  }

  _modifyJordanException(k, l + 1);
  _sizeX--;
  _table.pop_back();
  _lblX.pop_back();




  return true;
}

bool GomoryFirstSolver::_stepOptimalWork(){



  _state = SS_OptimalInteger;
  return true;
}