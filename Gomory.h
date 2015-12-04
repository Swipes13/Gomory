#ifndef GOMORY_H_
#define GOMORY_H_

#include "Task.h"

namespace gomory {

  class Gomory {
  public:
    Gomory(Task& t);
    ~Gomory();
    bool generateSupportPlan();
    bool generateOptimaPlan();
    bool generateOptimaPlanSimplex();
    bool generateIntegerOptimaPlan();

    void lMethod();
  private:
    void _lMethod();

    void modifyJorik(int r, int l);
    bool _compareLess(vector<Digit>&, vector<Digit>&);

    Task _task;
    vector<vector<Digit>> _table;
    int _sizeX;
    int _sizeY;
    vector<int> _lblX;
    vector<int> _lblY;
  };

}
#endif
