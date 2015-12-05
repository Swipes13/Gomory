#ifndef GOMORY_FIRST_SOLVER_SIMPLEX_H_
#define GOMORY_FIRST_SOLVER_SIMPLEX_H_

#include "support\Task.h"
#include "SimplexSolver.h"

namespace solver {
  
  class GomoryFirstSolverSimplex : public SimplexSolver {
  public:
    virtual void _initialize() override;

  protected:
    bool _stepOptimalIntegerWork() override;
    void _afterMJEWork(int r, int l) override;
    bool _compareLexicalMinimal(vector<Digit>&, vector<Digit>&);
    void _lMethod(int k, vector<vector<Digit>>&);
    vector<vector<Digit>>& _generateColumns(int k);

  protected:
    void _cutTableException(int k);
    int _r;

  private:
    bool _addSection();
    void _addGomoryLimitsToTable();
  };

}
#endif //GOMORY_FIRST_SOLVER_SIMPLEX_H_
