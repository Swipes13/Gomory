#include <iostream>
#include <conio.h>
#include "LinearProgramming.h"

using namespace solver;
using math::Digit;
using std::cout;

void main() {
  /*
  Equation eq1 = Equation(2, new Digit*[2] { new Digit(1), new Digit(-1) }, Digit(-1));
  Equation eq2 = Equation(2, new Digit*[2] { new Digit(-2, 3), new Digit(-1) }, Digit(7, 2));
  //Equation eq2 = Equation(2, new Digit*[2] { new Digit(-4), new Digit(-6) }, Digit(21));
  Equation mainEq = Equation(2, new Digit*[2] { new Digit(1), new Digit(10) });

  Task task = Task(TaskType::TT_Max, 2, new Limit*[2] { 
    new Limit(LimitType::LT_More, eq1),
      new Limit(LimitType::LT_More, eq2)},
      mainEq);
      */
  Equation* mainEq = new Equation(2, new Digit*[2] { new Digit(1, 15), new Digit(1, 5) }, new Digit());
  //Equation mainEq = Equation(2, new Digit*[2] { new Digit(7, 2), new Digit(25, 2) });
  Limit* lt1 = new Limit(LT_Less, new Equation(2, new Digit*[2] { new Digit(7, 2), new Digit(0) }, new Digit(-22000000)));
  Limit* lt2 = new Limit(LT_Less, new Equation(2, new Digit*[2] { new Digit(0), new Digit(25, 2) }, new Digit(-27000000)));
  Limit* lt3 = new Limit(LT_Less, new Equation(2, new Digit*[2] { new Digit(1, 150000), new Digit(5, 100000) }, new Digit(-360)));
  Limit* lt4 = new Limit(LT_Less, new Equation(2, new Digit*[2] { new Digit(1, 18750), new Digit(1, 36364) }, new Digit(-2500)));
  Limit* lt5 = new Limit(LT_Less, new Equation(2, new Digit*[2] { new Digit(1, 2), new Digit(2) }, new Digit(-15000000)));
  Limit* lt6 = new Limit(LT_Less, new Equation(2, new Digit*[2] { new Digit(1, 5), new Digit(1, 2) }, new Digit(-5000000)));
  Limit* lt7 = new Limit(LT_Less, new Equation(2, new Digit*[2] { new Digit(1, 40), new Digit(1, 10) }, new Digit(-900000)));

  Task* task = new Task(TaskType::TT_Max, 7, new Limit*[7] {
    lt1, lt2, lt3, lt4, lt5, lt6, lt7},
      mainEq);

  //GomoryFirstSolverSimplex ss;
  SimplexSolver ss;
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
        std::cout << ss.table(i, j)->toString() << "\t";
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

#pragma warning(push)
#pragma warning(disable:4273)

void release(Solver* solver) {
  delete solver;
}

Solver* simplex() {
  return new SimplexSolver();
}

Solver* gomoryFirstSimplex() {
  return new GomoryFirstSolverSimplex();
}

Task* task(int type, int countLimits, Limit** limits, Equation* equation) {
  TaskType tt = TaskType::TT_Max;
  if(type == 1) tt = TaskType::TT_Min;

  return new Task(tt, countLimits, limits, equation);
}

Digit* digit(int num, int denum) {
  return new Digit(num, denum);
}

Limit* limit(int type, Equation *equa) {
  LimitType lt;
  switch(type) {
  case 0: lt = LimitType::LT_Equal; break;
  case 1: lt = LimitType::LT_Less; break;
  case 2: lt = LimitType::LT_More; break;
  default:
    break;
  }
  return  new Limit(lt, equa);
}

Equation* equation(int xCount, Digit **digs, Digit *dig) {
  return new Equation(xCount, digs, dig);
}

void initialize(Solver* solver, Task* task) {
  solver->initialize(task);
}

int state(Solver *solver) {
  return solver->state();
}

Digit* result(Solver *solver) {
  return solver->result();
}

bool stepWork(Solver *solver) {
  return solver->stepWork();
}

int numerator(Digit *digit) {
  return digit->numerator();
}

int denominator(Digit *digit) {
  return digit->denominator();
}

double value(Digit *digit) {
  return digit->toDouble();
}

Digit* table(Solver *solver, int i, int j) {
  return solver->table(i, j);
}

int sizeX(Solver *solver) {
  return solver->sizeX();
}

int sizeY(Solver *solver) {
  return solver->sizeY();
}

int labelX(Solver *solver, int index) {
  return solver->labelX(index);
}

int labelY(Solver *solver, int index) {
  return solver->labelY(index);
}

#pragma warning(pop)

// end