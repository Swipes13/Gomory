using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace LinearProgrammingGUI.src {
  public static class LP_DLL {
    const String _path = "../../../dll/LinearProgramming.dll";
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "simplex")]
    public extern static IntPtr Simplex();
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "release")]
    public extern static void Release(IntPtr solver);
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "gomoryFirstSimplex")]
    public extern static IntPtr GomoryFirstSimplex();
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "initialize")]
    public extern static void Initialize(IntPtr solver, IntPtr task);
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "task")]
    public extern static IntPtr Task(int type, int countLimits, IntPtr limits, IntPtr equation);
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "digit")]
    public extern static IntPtr Digit(int num, int denum);
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "equation")]
    public extern static IntPtr Equation(int xCount, IntPtr digs, IntPtr dig);
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "limit")]
    public extern static IntPtr Limit(int type, IntPtr equation);
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "state")]
    public extern static int State(IntPtr solver);
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "result")]
    public extern static IntPtr result(IntPtr solver);
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "stepWork")]
    public extern static bool StepWork(IntPtr solver);
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "numerator")]
    public extern static int Numerator(IntPtr digit);
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "denominator")]
    public extern static int Denomerator(IntPtr digit);
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "value")]
    public extern static double GetDouble(IntPtr digit);

    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "table")]
    public extern static IntPtr Table(IntPtr solver, int i, int j);
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "sizeX")]
    public extern static int SizeX(IntPtr solver);
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "sizeY")]
    public extern static int SizeY(IntPtr solver);
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "labelX")]
    public extern static int LabelX(IntPtr solver, int index);
    [DllImport(_path, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, EntryPoint = "labelY")]
    public extern static int LabelY(IntPtr solver, int index);
  }
  public class Digit {
    IntPtr digit;
    public Digit(IntPtr ptr) { digit = ptr; }
    public Digit(int num, int denum) { digit = LP_DLL.Digit(num, denum); }
    public Digit(int num) { digit = LP_DLL.Digit(num, 1); }
    public Digit() { digit = LP_DLL.Digit(0, 1); }
    public IntPtr IntPtr() { return digit; }
    public int Numerator() { return LP_DLL.Numerator(digit); }
    public int Denomerator() { return LP_DLL.Denomerator(digit); }
    public double GetDouble() { return LP_DLL.GetDouble(digit); }
  }
  public class Equation {
    IntPtr equation;
    public Equation(Digit[] digs, Digit digit) {
      IntPtr[] ptrs = new IntPtr[digs.Count()];
      for(int i=0;i<digs.Count();i++) ptrs[i] = digs[i].IntPtr();
      unsafe {
        fixed (IntPtr* pArray = ptrs) {
          IntPtr digitsPtr = new IntPtr((void*)pArray);
          equation = LP_DLL.Equation(digs.Count(), digitsPtr, digit.IntPtr());
        }
      }
    }
    public Equation(Digit[] digs) {
      IntPtr[] ptrs = new IntPtr[digs.Count()];
      for (int i = 0; i < digs.Count(); i++) ptrs[i] = digs[i].IntPtr();
      unsafe {
        fixed (IntPtr* pArray = ptrs) {
          IntPtr digitsPtr = new IntPtr((void*)pArray);
          equation = LP_DLL.Equation(digs.Count(), digitsPtr, new Digit().IntPtr());
        }
      }
    }
    public IntPtr IntPtr() { return equation; }
  }
  public class Limit {
    public enum LimitType { Equal, Less, More }
    IntPtr limit;
    public Limit(LimitType lt, Equation equa) {
      int type = 0;
      switch(lt){
        case LimitType.Less: type = 1; break;
        case LimitType.More: type = 2; break;
      }
      limit = LP_DLL.Limit(type, equa.IntPtr());
    }
    public IntPtr IntPtr() { return limit; }
  }
  public class Task {
    public enum TaskType { Max, Min }
    IntPtr task;
    public Task(TaskType taskType, Limit[] limits, Equation equation) {
      int tt = 0; 
      if(taskType == TaskType.Min) tt = 1;

      IntPtr[] ptrs = new IntPtr[limits.Count()];
      for (int i = 0; i < limits.Count(); i++) ptrs[i] = limits[i].IntPtr();
      unsafe {
        fixed (IntPtr* pArray = ptrs) {
          IntPtr limitsPtr = new IntPtr((void*)pArray);
          task = LP_DLL.Task(tt, limits.Count(), limitsPtr, equation.IntPtr());
        }
      }
    }
    public IntPtr IntPtr() { return task; }
  }
  public class Solver : IDisposable {
    public enum SolverState { 
      NotInit, ZeroStr, 
      ErrorZeroStr, Support, 
      ErrorSupport, Optimal, 
      ErrorOptimal, OptimalInteger, 
      ErrorOptimalInteger, Finish }
    protected bool initialized = false;
    protected IntPtr solver;

    public Digit Result() {
      if (!initialized) return null;
      return new Digit(LP_DLL.result(solver));
    }
    public bool StepWork() {
      if (!initialized) return false;

      return LP_DLL.StepWork(solver);
    }
    public SolverState State(){
      if (!initialized) return SolverState.NotInit;
      int state = LP_DLL.State(solver);
      switch (state) {
        case 0: return SolverState.NotInit;
        case 1: return SolverState.ZeroStr;
        case 2: return SolverState.ErrorZeroStr;
        case 3: return SolverState.Support;
        case 4: return SolverState.ErrorSupport;
        case 5: return SolverState.Optimal;
        case 6: return SolverState.ErrorOptimal;
        case 7: return SolverState.OptimalInteger;
        case 8: return SolverState.ErrorOptimalInteger;
        case 9: return SolverState.Finish;
        default: return SolverState.NotInit;
      }
    }
    public int SizeX() {
      if (!initialized) return 0;
      return LP_DLL.SizeX(solver);
    }
    public int SizeY() {
      if (!initialized) return 0;
      return LP_DLL.SizeY(solver);
    }
    public int LabelX(int index) {
      if (!initialized) return -42;
      return LP_DLL.LabelX(solver, index);
    }
    public int LabelY(int index) {
      if (!initialized) return -42;
      return LP_DLL.LabelY(solver, index);
    }
    public Digit Table(int i, int j) {
      if (!initialized) return null;
      return new Digit(LP_DLL.Table(solver,i,j));
    }

    protected Solver() { }
    protected void initialize(Task task) {
      if (initialized) Dispose();
      LP_DLL.Initialize(solver, task.IntPtr());
      initialized = true;
    }
    public void Dispose() { if (initialized) LP_DLL.Release(solver); initialized = false; }
  }
  public class SimplexSolver : Solver {
    public SimplexSolver(Task task) {
      solver = LP_DLL.Simplex();
      base.initialize(task);
    }
  }
  public class GomoryFirstSimplexSolver : Solver {
    public GomoryFirstSimplexSolver(Task task) {
      solver = LP_DLL.GomoryFirstSimplex();
      base.initialize(task);
    }
  }
}
