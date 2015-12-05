#ifndef GOMORY_FIRST_SOLVER_H_
#define GOMORY_FIRST_SOLVER_H_

#include "GomoryFirstSolverSimplex.h"

namespace solver {

  class GomoryFirstSolver : public GomoryFirstSolverSimplex {
  public:
  protected:
    bool _stepSupportWork() override;
    bool _stepOptimalWork() override;
    vector<vector<Digit>>& _generateColumnsPreOptimal(int k);

  private:
    bool _preOptimalWork();
  };

}

#endif //GOMORY_FIRST_SOLVER_H_