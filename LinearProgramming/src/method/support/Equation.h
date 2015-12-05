#ifndef EQUATION_H_
#define EQUATION_H_

#include "../../math/Digit.h"
#include <vector>

using std::vector;
using math::Digit;

namespace solver {

  class Equation {
  public:
    Equation(int count, Digit**, Digit&);
    Equation(int count, Digit**);
    Equation(int count, Digit*, Digit&);
    Equation(int count, Digit*);
    Equation(const Equation&);
    Equation();
    ~Equation();
    Digit& x(int);
    Digit& forConst();
    int countX();

  private:
    vector<Digit> _equa;
    Digit _forConst;
  };

}

#endif
