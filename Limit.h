#ifndef LIMIT_H_
#define LIMIT_H_

#include "Equation.h"

namespace gomory {

  enum LimitType {
    LT_Less,
    LT_More,
    LT_Equal
  };

  class Limit {
  public:
    Limit(LimitType, Equation&);
    Limit(const Limit&);
    Limit();
    ~Limit();
    Equation& equation();
    LimitType limitType();

  private:
    Equation _equation;
    LimitType _limitType;
  };

}

#endif
