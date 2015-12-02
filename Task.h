#ifndef TASK_H_
#define TASK_H_

#include "Limit.h"
#include "Equation.h"
using std::vector;

namespace gomory {

  enum TaskType {
    TT_Min,
    TT_Max
  };

  class Task {
  public:
    Task(TaskType, int count, Limit**, Equation&);
    Task();
    ~Task();
    Limit& limit(int index);
    Equation& equation();
    TaskType taskType();
    int countLimits();

  private:
    TaskType _taskType;
    Equation _equa;
    vector<Limit> _limits;
  };

}
#endif
