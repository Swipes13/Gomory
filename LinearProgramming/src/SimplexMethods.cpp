#include <iostream>
#include <conio.h>
#include "method\GomoryFirstSolver.h"

using namespace solver;
using math::Digit;
using std::cout;

void main() {
  Equation eq1 = Equation(2, new Digit*[2] { new Digit(1), new Digit(-1) }, Digit(1));
  //Equation eq2 = Equation(2, new Digit*[2] { new Digit(-2, 3), new Digit(-1) }, Digit(7, 2));
  Equation eq2 = Equation(2, new Digit*[2] { new Digit(-4), new Digit(-6) }, Digit(21));
  
  Task task = Task(TaskType::TT_Max, 2, new Limit*[2] {
    new Limit(LimitType::LT_More, eq1), new Limit(LimitType::LT_More, eq2)}, 
      Equation(2, new Digit*[2] { new Digit(1), new Digit(10) }) );


  GomoryFirstSolverSimplex gom;
  gom.initialize(task);
  while (gom.stepWork()) {
  }

  if (gom.state() != solver::SS_Finish)
    getchar();

  getchar();

}