#ifndef GOMORY_H_
#define GOMORY_H_

#include "Task.h"
#include "Solver.h"

namespace solver {
  
  class Gomory : public Solver {
  public:
    Gomory(Task& t);
    void lMethod();

  protected:
    bool _stepSupportWork() override;
    bool _stepOptimalWork() override;
    bool _stepOptimalIntegerWork() override;
    void _afterMJEWork(int r, int l) override;

  private:
    void _lMethod();
    bool _compareLexicalMinimal(vector<Digit>&, vector<Digit>&);

  private:
    int _r;
  };

}
#endif
