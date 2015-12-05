#ifndef GOMORY_FIRST_SOLVER_H_
#define GOMORY_FIRST_SOLVER_H_

#include "GomoryFirstSolverSimplex.h"

namespace solver {

  class GomoryFirstSolver : public GomoryFirstSolverSimplex {
  public:
  protected:
    bool _stepSupportWork() override;
    bool _stepOptimalWork() override;

  private:
    bool _preOptimalWork();
  };

}

#endif //GOMORY_FIRST_SOLVER_H_