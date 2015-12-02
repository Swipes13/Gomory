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
  Equation eq2 = Equation(2, new Digit*[2] { new Digit(-2,3), new Digit(-1) }, Digit(7,2));
  
  Task task = Task(gomory::TaskType::TT_Max, 2, new Limit*[2] {
    new Limit(gomory::LimitType::LT_More, eq1), new Limit(gomory::LimitType::LT_More, eq2)},
      Equation(2, new Digit*[2] { new Digit(1), new Digit(10) }) );

  Gomory gom = Gomory(task);
  getchar();
}