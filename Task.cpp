#include "Task.h"

using namespace gomory;

Task::Task() {}

Task::~Task() {}

Task::Task(TaskType type, int count, Limit** limits, Equation& equa) {
  _taskType = type;
  for(int i = 0; i < count; i++) 
    _limits.push_back(Limit(*(limits[i])));
  _equa = Equation(equa);
}

Limit& Task::limit(int index) {
  if(index < static_cast<int>(_limits.size()))
    return _limits[index];
  else
    return *(new Limit());
}

Equation& Task::equation() {
  return _equa;
}

TaskType Task::taskType() {
  return _taskType;
}

int Task::countLimits() {
  return static_cast<int>(_limits.size());
}