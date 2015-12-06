#ifndef __LINEAR_PROGRAMMING_H
#define __LINEAR_PROGRAMMING_H

#ifdef LP_DLL_EXPORTS
#define DLL_SPEC extern "C" __declspec(dllexport)

#else
#define DLL_SPEC extern "C" __declspec(dllimport)
#endif // LP_DLL_EXPORTS

#include "method\GomoryFirstSolver.h"
using namespace solver;

DLL_SPEC void release(Solver*);
DLL_SPEC Solver* getSimplex();
DLL_SPEC Solver* getGomoryFirstSimplex();
DLL_SPEC Task* getTask(int type, int countLimits, Limit**, Equation* equation);

#endif // __LINEAR_PROGRAMMING_H 