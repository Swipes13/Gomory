#include <iostream>
#include <conio.h>
#include "Digit.h"
#include "Equation.h"
#include "Limit.h"
#include "Task.h"
#include "Gomory.h"

using gomory::Gomory;
using gomory::Task;
using gomory::Limit;
using gomory::Equation;
using math::Digit;
using std::cout;

void main() {
  Equation eq1 = Equation(2, new Digit*[2] { new Digit(1), new Digit(-1) }, Digit(1));
  Equation eq2 = Equation(2, new Digit*[2] { new Digit(-2, 3), new Digit(-1) }, Digit(7, 2));
  //Equation eq2 = Equation(2, new Digit*[2] { new Digit(-4), new Digit(-6) }, Digit(21));
  Equation eq3 = Equation(2, new Digit*[2] { new Digit(-1), new Digit(-1) }, Digit(5));
  
  Task task = Task(gomory::TaskType::TT_Max, 3, new Limit*[3] {
    new Limit(gomory::LimitType::LT_More, eq1), 
      new Limit(gomory::LimitType::LT_More, eq2),
      new Limit(gomory::LimitType::LT_More, eq3)
  },
    Equation(2, new Digit*[2] { new Digit(1), new Digit(10) }) );

  Gomory gom = Gomory(task);
  //gom.generateOptimaPlan();
  gom.lMethod();
  if(!gom.generateIntegerOptimaPlan())
    getchar();

  getchar();

}