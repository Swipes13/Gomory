#ifndef SOLVER_H_
#define SOLVER_H_

#include "support\Task.h"
using std::string;

namespace solver {

  enum SolverState {
    SS_NotInit,
    SS_ZeroStrs,
    SS_ErrorZeroStrs,
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
    ~Solver();
    void initialize(Task*);
    bool stepWork();
    SolverState state();
    Digit* result();
    Digit* table(int, int);
    int sizeX();
    int sizeY();
    int labelX(int);
    int labelY(int);
    string getError();
    string getResult();

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

    Task* _task;
    vector<vector<Digit>> _table;
    int _sizeX;
    int _sizeY;
    vector<int> _lblX;
    vector<int> _lblY;
    vector<bool> _zeroStr;

    string _errorMessage;

  private:
    bool _computeZeroStrs();
    void _cutTable(int l);
  };

}
#endif
