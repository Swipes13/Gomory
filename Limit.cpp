#include "Limit.h"

using namespace gomory;

Limit::Limit() { }

Limit::Limit(LimitType ltype, Equation &equa) {
  _limitType = ltype;
  _equation = equa;
}

Limit::Limit(const Limit& limit) {
  _limitType = limit._limitType;
  _equation = Equation(limit._equation);
}

Limit::~Limit() {}

Equation& Limit::equation() {
  return _equation;
}

LimitType Limit::limitType() {
  return _limitType; 
}