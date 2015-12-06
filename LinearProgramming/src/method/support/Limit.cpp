#include "Limit.h"

using namespace solver;

Limit::Limit() { }

Limit::Limit(LimitType ltype, Equation *equa) {
  _limitType = ltype;
  _equation = equa;
}

Limit::Limit(const Limit& limit) {
  _limitType = limit._limitType;
  _equation = new Equation(*limit._equation);
}

Limit::~Limit() {
  delete _equation;
}

Equation* Limit::equation() {
  return _equation;
}

LimitType Limit::limitType() {
  return _limitType; 
}

void Limit::setLimitType(LimitType type) {
  _limitType = type;
}