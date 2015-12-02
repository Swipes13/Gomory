#include "Gomory.h"

using namespace gomory;

Gomory::Gomory(Task& t) {
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

Gomory::~Gomory() {}
