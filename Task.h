#ifndef TASK_H_
#define TASK_H_

#include "Limit.h"
#include "Equation.h"
using std::vector;

namespace solver {

  enum TaskType {
    TT_Min,
    TT_Max
  };

  class Task {
  public:
    Task();
    Task(TaskType, int count, Limit**, Equation&);
    Task(const Task&);
    Limit& limit(int index);
    Equation& equation();
    TaskType taskType();
    int countLimits();
    void setEquation(const Equation&);

  private:
    TaskType _taskType;
    Equation _equa;
    vector<Limit> _limits;
  };

}
#endif
