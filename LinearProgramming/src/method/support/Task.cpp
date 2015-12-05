#include "Task.h"

using namespace solver;

Task::Task(){
}

Task::Task(const Task& task){
  this->_equa = task._equa;
  this->_limits = task._limits;
  this->_taskType = task._taskType;
}

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

void Task::setEquation(const Equation& equa){
  _equa = equa;
}

void Task::setTaskType(TaskType type) {
  _taskType = type;
}
