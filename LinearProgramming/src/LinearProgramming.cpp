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
  Equation mainEq = Equation(2, new Digit*[2] { new Digit(1), new Digit(10) });

  Task task = Task(TaskType::TT_Max, 2, new Limit*[2] { 
    new Limit(LimitType::LT_Equal, eq1),
      new Limit(LimitType::LT_More, eq2)},
      mainEq);

  GomoryFirstSolverSimplex ss;
  //SimplexSolver ss;
  ss.initialize(task);
  do {
    std::cout << "\t";
    for(int j = 0; j < ss.sizeY(); j++) {
      int lbly = ss.labelY(j);
      if(lbly == -1) {
        std::cout << 1 << "\t";
        continue;
      }
      if(lbly != 0) std::cout << "x";
      std::cout << lbly << "\t";
    }
    std::cout << std::endl;

    for(int i = 0; i < ss.sizeX(); i++) {
      int lbl = ss.labelX(i);
      if(lbl == -1) 
        std::cout << "Q\t";
      else    {
        if(lbl != 0) std::cout << "x";
        std::cout << lbl << "\t";
      }

      for(int j = 0; j < ss.sizeY(); j++) {
        std::cout << ss.table(i, j).toString() << "\t";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
  while(ss.stepWork());
  if(ss.state() != solver::SS_Finish) std::cout << ss.getError();
  else std::cout << ss.getResult();
  
  getchar();

}