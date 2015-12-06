using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using LinearProgrammingGUI.src;
using Task = LinearProgrammingGUI.src.Task;

namespace LinearProgrammingGUI {
  public partial class LPForm : Form {
    Solver ss = null;
    public LPForm() {
      InitializeComponent();
      var lt1 = new Equation(new Digit[] { new Digit(1), new Digit(-1) }, new Digit(-1));
      //var lt2 = new Equation(new Digit[] { new Digit(-2, 3), new Digit(-1) }, new Digit(7, 2));
      var lt2 = new Equation(new Digit[] { new Digit(-4), new Digit(-6) }, new Digit(21));
      var mainEqua = new Equation(new Digit[] { new Digit(1), new Digit(10) });
      
      Task task = new Task(Task.TaskType.Max, new Limit[] { 
        new Limit(Limit.LimitType.Equal, lt1), new Limit(Limit.LimitType.More, lt2),
      }, mainEqua);
      ss = new SimplexSolver(task);
    }

    public void fillDgvSolver(Solver solver) {
      dgvSolver.Rows.Clear();
      dgvSolver.Columns.Clear();
      var numClmns = solver.SizeY() + 1;
      for (int i = 0; i < numClmns; i++) dgvSolver.Columns.Add("", "");

      for (int i = 0; i < solver.SizeX(); i++) {
        String[] strings = new String[numClmns];
        for (int j = 0; j < solver.SizeY(); j++) {
          strings[j] = solver.Table(i, j).GetDouble().ToString();
        }
        dgvSolver.Rows.Add(strings);
      }
    }

    private void button1_Click(object sender, EventArgs e) {
      var state = ss.State();
      if (state == Solver.SolverState.ErrorZeroStr ||
        state == Solver.SolverState.ErrorSupport ||
        state == Solver.SolverState.ErrorOptimal ||
        state == Solver.SolverState.ErrorOptimalInteger ||
        state == Solver.SolverState.Finish) {
          MessageBox.Show(state.ToString());
        return;
      }
      ss.StepWork();
      fillDgvSolver(ss);
    }
  }
}
