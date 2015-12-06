#include "GomoryFirstSolverSimplex.h"

using namespace solver;
#include <map>
using std::map;

void GomoryFirstSolverSimplex::_initialize() {
  _r = 0;
  _sizeX = _sizeY + _task->countLimits();
  for(int i = 0; i < _sizeX; i++) _lblX.push_back(i);

  _addGomoryLimitsToTable();
  _addLimitsToTable();
}

bool GomoryFirstSolverSimplex::_stepOptimalIntegerWork() {
  if(!_addSection()) return false;

  int k = -1;
  for (int i = 0; i < _sizeX; i++){
    if (_table[i][0] < 0){ k = i; break; }
  }

  if (k != -1) {
    for (int i = 0; i < _sizeY; i++)
    if (_table[k][i].integer()){
      _errorMessage = "Optimal Integer plan. In line for section are integer value!";
      _state = solver::SS_ErrorOptimalInteger;
      return false;
    }

    _lMethod(k, _generateColumns(k));
    _cutTableException(k);
  }
  _r++;
  return true;
}

bool GomoryFirstSolverSimplex::_addSection(){
  int k = -1;
  for (int i = 0; i < _sizeX; i++) {
    if (_table[i][0].digitType() != math::DigitType::DT_Definite) {
      _state = solver::SS_ErrorOptimalInteger;
      _errorMessage = "Optimal Integer plan. One Digit is undefined!";
      return false;
    }
    if (!_table[i][0].integer()) {
      k = i; break;
    }
  }

  if (k == -1) { _state = solver::SS_Finish; return false; }

  int index = _sizeX + _r;
  vector<Digit> row;
  for (int i = 0; i < _sizeY; i++)
    row.push_back(-_table[k][i].left());

  _sizeX++;
  _table.push_back(row);
  _lblX.push_back(index);

  return true;
}

void GomoryFirstSolverSimplex::_lMethod(int k, vector<vector<Digit>>& vecs){
  vector<vector<Digit>> clmns = vecs;

  int l = 0;
  auto min = clmns[l];
  for (int i = 1; i < static_cast<int>(clmns.size()); i++){
    if(_compareLexicalMinimal(clmns[i], min)) {
      min = clmns[i];
      l = i;
    }
  }

  _modifyJordanException(k, l + 1);
}

void GomoryFirstSolverSimplex::_cutTableException(int k){
  _table.erase(_table.begin() + k);
  _lblX.erase(_lblX.begin() + k);
  _sizeX--;
}

vector<vector<Digit>>& GomoryFirstSolverSimplex::_generateColumns(int k){
  vector<vector<Digit>>* clmns = new vector<vector<Digit>>;
  for (int j = 1; j < _sizeY; j++){
    vector<Digit> clm;
    if (_table[k][j] >= 0)
      continue;
    for (int i = 0; i < _sizeX; i++){
      clm.push_back(_table[i][j] / _table[k][j].absD());
    }
    clmns->push_back(clm);
  }
  return *clmns;
}

bool GomoryFirstSolverSimplex::_compareLexicalMinimal(vector<Digit>& vec1, vector<Digit>& vec2) {
  for (int i = 0; i < static_cast<int>(vec1.size()); i++){
    if (vec1[i] == vec2[i])
      continue;
    if (vec1[i] < vec2[i])
      return true;
    return false;
  }
  return false;
}

void GomoryFirstSolverSimplex::_afterMJEWork(int r, int l) {
  _lblY[l] = _lblX[r];

  if(static_cast<int>(_table.size()) <= _lblY[l])
    return;

  for(int i = 0; i < _sizeY; i++) {
    if(l != i) _table[_lblY[l]][i] = Digit(0);
    else _table[_lblY[l]][i] = Digit(-1);
  }
}

void GomoryFirstSolverSimplex::_addGomoryLimitsToTable() {
  for(int i = 0; i < _task->equation()->countX(); i++) {
    vector<Digit> digs;
    digs.push_back(Digit(0));
    for(int j = 0; j < _task->equation()->countX(); j++) {
      if(j == i) digs.push_back(Digit(-1));
      else digs.push_back(Digit(0));
    }
    _table.push_back(digs);
  }
}
