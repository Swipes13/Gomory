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
DLL_SPEC Solver* simplex();
DLL_SPEC Solver* gomoryFirstSimplex();
DLL_SPEC void initialize(Solver*, Task*);
DLL_SPEC Task* task(int type, int countLimits, Limit**, Equation* equation);
DLL_SPEC Digit* digit(int num, int denum);
DLL_SPEC Equation* equation(int xCount, Digit**, Digit*);
DLL_SPEC Limit* limit(int type, Equation*);
DLL_SPEC int state(Solver*);
DLL_SPEC Digit* result(Solver*);
DLL_SPEC bool stepWork(Solver*);
DLL_SPEC int numerator(Digit*);
DLL_SPEC int denominator(Digit*);
DLL_SPEC double value(Digit*);
DLL_SPEC Digit* table(Solver*, int i, int j);
DLL_SPEC int sizeX(Solver*);
DLL_SPEC int sizeY(Solver*);
DLL_SPEC int labelX(Solver*,int);
DLL_SPEC int labelY(Solver*, int);

#endif // __LINEAR_PROGRAMMING_H 