#ifndef SIMPLEX_SOLVER_H_
#define SIMPLEX_SOLVER_H_

#include "Solver.h"

namespace solver{

  class SimplexSolver : public Solver {
  public:
    virtual void initialize(Task&) override;

  protected:
    bool _stepSupportWork() override;
    bool _stepOptimalWork() override;
    virtual void _afterMJEWork(int r, int l) override;
  };

}

#endif