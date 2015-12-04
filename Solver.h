#ifndef GOMORY_H_
#define GOMORY_H_

namespace solver {
  enum SolverState {
    SS_Start,
    SS_Support,
    SS_ErrorSupport,
    SS_Optimal,
    SS_ErrorOptimal,
    SS_Finish
  };
  class Solver {
  public:
    bool stepWork();

  protected:
    virtual bool _stepSupportWork();
    virtual bool _stepOptimalWork();

    SolverState _state;
  };

}
#endif
