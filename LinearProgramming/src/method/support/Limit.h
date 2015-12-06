#ifndef LIMIT_H_
#define LIMIT_H_

#include "Equation.h"

namespace solver {

  enum LimitType {
    LT_Less,
    LT_More,
    LT_Equal
  };

  class Limit {
  public:
    Limit(LimitType, Equation*);
    Limit(const Limit&);
    Limit();
    ~Limit();
    Equation* equation();
    LimitType limitType();
    void setLimitType(LimitType);

  private:
    Equation* _equation;
    LimitType _limitType;
  };

}

#endif
