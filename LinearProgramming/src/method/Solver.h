#ifndef SOLVER_H_
#define SOLVER_H_

#include "support\Task.h"

namespace solver {

  enum SolverState {
    SS_NotInit,
    SS_Support,
    SS_ErrorSupport,
    SS_Optimal,
    SS_ErrorOptimal,
    SS_OptimalInteger,
    SS_ErrorOptimalInteger,
    SS_Finish
  };

  class Solver {
  public:
    Solver();
    void initialize(Task&t);
    bool stepWork();
    SolverState state();
    Digit& result();

  protected:
    virtual void _initialize() = 0;
    virtual bool _stepSupportWork() = 0;
    virtual bool _stepOptimalWork() = 0;
    virtual void _afterMJEWork(int r, int l) = 0;

    virtual bool _stepOptimalIntegerWork();

    void _modifyJordanException(int r, int l);
    void _makeUnifiedEquations();
    void _addLimitsToTable();
  protected:
    SolverState _state;

    Task _task;
    vector<vector<Digit>> _table;
    int _sizeX;
    int _sizeY;
    vector<int> _lblX;
    vector<int> _lblY;
  };

}
#endif
