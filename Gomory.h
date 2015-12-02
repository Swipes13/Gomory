#ifndef GOMORY_H_
#define GOMORY_H_

#include "Task.h"

namespace gomory {

  class Gomory {
  public:
    Gomory(Task& t);
    ~Gomory();

  private:
    Task _task;
    vector<vector<Digit>> _table;
    int _sizeX;
    int _sizeY;
    vector<int> _lblX;
    vector<int> _lblY;
  };

}
#endif
