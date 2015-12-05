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
    bool _compareLexicalMinimal(vector<Digit>&, vector<Digit>&);
    void _lMethod(int k, vector<vector<Digit>>&);
    vector<vector<Digit>>& _generateColumns(int k);

  protected:
    void _cutTableException();
    int _r;

  private:
    void _addSection(int k);
  };

}
#endif //GOMORY_FIRST_SOLVER_SIMPLEX_H_
