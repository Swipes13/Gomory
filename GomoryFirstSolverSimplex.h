#ifndef GOMORY_FIRST_SOLVER_SIMPLEX_H_
#define GOMORY_FIRST_SOLVER_SIMPLEX_H_

#include "Task.h"
#include "SimplexSolver.h"

namespace solver {
  
  class GomoryFirstSolverSimplex : public SimplexSolver {
  public:
    virtual void initialize(Task&) override;

  protected:
    bool _stepOptimalIntegerWork() override;
    void _afterMJEWork(int r, int l) override;

  private:
    void _lMethod();
    bool _compareLexicalMinimal(vector<Digit>&, vector<Digit>&);

  private:
    int _r;
  };

}
#endif //GOMORY_FIRST_SOLVER_SIMPLEX_H_
