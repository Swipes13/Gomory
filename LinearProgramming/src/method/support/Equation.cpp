#include "Equation.h"

using namespace solver;

Equation::Equation() {
}

Equation::~Equation() {
  delete _forConst;
  for(auto eq : _equa)
    delete eq;
  _equa.clear();
  _equa.shrink_to_fit();
}

Equation::Equation(const Equation& eq) {
  for(int i = 0; i < static_cast<int>(eq._equa.size()); i++)
    this->_equa.push_back(eq._equa[i]);
  _forConst = eq._forConst;
}

Equation::Equation(int count, Digit** digits, Digit* forConst) {
  for(int i = 0; i < count; i++)
    this->_equa.push_back(digits[i]);
  _forConst = forConst;
}

Equation::Equation(int count, Digit** digits) {
  for(int i = 0; i < count; i++)
    this->_equa.push_back(digits[i]);
  _forConst = new Digit();
}

Digit* Equation::x(int index) {
  if(index < static_cast<int>(_equa.size()))
    return _equa[index];
  return new Digit();
}

Digit* Equation::forConst() {
  return _forConst;
}

int Equation::countX() {
  return static_cast<int>(_equa.size());
}

void Equation::changeSigns() {
  for(int i = 0; i < static_cast<int>(_equa.size()); i++)
    (*this->_equa[i]) = -(*this->_equa[i]);
  *(this->_forConst) = -(*this->_forConst);
}