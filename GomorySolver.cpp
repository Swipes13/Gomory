#include "GomorySolver.h"

using namespace solver;
#include <map>
using std::map;

GomorySolver::GomorySolver(Task& t) {
  _state = solver::SS_Start;
  _r = 0;
  _task = t;

  _sizeY = _task.equation().countX() + 1;
  _sizeX = _sizeY + _task.countLimits();

  for(int i = 0; i < _sizeX; i++) _lblX.push_back(i);
  _lblY.push_back(-1);
  for(int i = 1; i < _sizeY; i++) _lblY.push_back(i);

  vector<Digit> digs;
  digs.push_back(_task.equation().forConst());

  for(int i = 0; i < _task.equation().countX(); i++) 
    digs.push_back(-_task.equation().x(i));
  _table.push_back(digs);

  for(int i = 0; i < _task.equation().countX(); i++) {
    vector<Digit> digs_;
    digs_.push_back(Digit(0));
    for(int j = 0; j < _task.equation().countX(); j++) {
      if(j == i) 
        digs_.push_back(Digit(-1));
      else 
        digs_.push_back(Digit(0));
    }
    _table.push_back(digs_);
  }

  for(int i = 0; i < _task.countLimits(); i++) {
    vector<Digit> digs_;
    digs_.push_back(_task.limit(i).equation().forConst());
    for(int j = 0; j < _task.equation().countX(); j++) 
      digs_.push_back(-_task.limit(i).equation().x(j));
    _table.push_back(digs_);
  }

}

bool GomorySolver::_stepSupportWork() {
  //TODO : DO!
  _state = solver::SS_Optimal;
  return true;
}

bool GomorySolver::_stepOptimalWork() {
  vector<int> ll;
  for(int i = 0; i < _sizeY; i++) {
    if(_table[0][i] < 0)
      ll.push_back(i);
  }

  if(ll.size() == 0) {
    _state = solver::SS_OptimalInteger;
    return true;
  }

  for(auto l : ll) {
    map<int, Digit> toChoose;
    for(int i = 0; i < _sizeX; i++) {
      if(_table[i][l] > 0)
        toChoose[i] = _table[i][0] / _table[i][l];
    }
    if(toChoose.size() == 0) continue;

    std::pair<int, Digit> min = *toChoose.begin();
    for(auto& elem : toChoose) {
      if(elem.second < min.second)
        min = elem;
    }
    int r = min.first;

    _modifyJordanException(r, l);
    return true;
  }

  _state = solver::SS_ErrorOptimal;
  return false;
}

bool GomorySolver::_stepOptimalIntegerWork() {
  int k = -1;
  for(int i = 0; i < _sizeX; i++) {
    if(_table[i][0].digitType() != math::DigitType::DT_Definite) {
      _state = solver::SS_ErrorOptimalInteger;
      return false;
    }
    if(!_table[i][0].integer()) {
      k = i; break;
    }
  }

  if(k == -1) {
    _state = solver::SS_Finish;
    return true;
  }

  int index = _sizeX + _r;
  vector<Digit> row;
  for(int i = 0; i < _sizeY; i++)
    row.push_back(-_table[k][i].left());

  _sizeX++;
  _table.push_back(row);
  _lblX.push_back(index);

  _lMethod();
  _r++;
  return true;
}

void GomorySolver::_lMethod(){
  int k = -1;
  for (int i = 0; i < _sizeX; i++){
    if (_table[i][0] < 0){
      k = i; break;
    }
  }

  if (k == -1) return;


  vector<vector<Digit>> clmns;
  for (int j = 1; j < _sizeY; j++){
    vector<Digit> clm;
    for (int i = 0; i < _sizeX; i++){
      clm.push_back(_table[i][j] / _table[k][j].absD());
    }
    clmns.push_back(clm);
  }

  int l = 0;
  auto min = clmns[l];
  for (int i = 1; i < static_cast<int>(clmns.size()); i++){
    if(_compareLexicalMinimal(clmns[i], min)) {
      min = clmns[i];
      l = i;
    }
  }

  _modifyJordanException(k, l + 1);
  _sizeX--;
  _table.pop_back();
  _lblX.pop_back();
}

bool GomorySolver::_compareLexicalMinimal(vector<Digit>& vec1, vector<Digit>& vec2) {
  for (int i = 0; i < static_cast<int>(vec1.size()); i++){
    if (vec1[i] == vec2[i])
      continue;
    if (vec1[i] < vec2[i])
      return true;
    return false;
  }
  return false;
}

void GomorySolver::_afterMJEWork(int r, int l) {
  _lblY[l] = _lblX[r];

  if(static_cast<int>(_table.size()) >= _lblY[l])
    return;

  for(int i = 0; i < _sizeY; i++) {
    if(l != i) _table[_lblY[l]][i] = Digit(0);
    else _table[_lblY[l]][i] = Digit(-1);
  }
}

/*void GomorySolver::lMethod(){
int k = _sizeX - 1;

vector<vector<Digit>> clmns;
for (int j = 1; j < _sizeY; j++){
vector<Digit> clm;
for (int i = 0; i < _sizeX; i++){
clm.push_back(_table[i][j]);
}
clmns.push_back(clm);
}

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
*/