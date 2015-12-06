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
    public LPForm() {
      InitializeComponent();
      testFunc();
    }

    public void testFunc() {
      var mainEqua = new Equation(new Digit[]{new Digit(1),new Digit(10)});
      var lt1 = new Equation(new Digit[] { new Digit(1), new Digit(-1) }, new Digit(1));
      //var lt2 = new Equation(new Digit[] { new Digit(-2, 3), new Digit(-1) }, new Digit(7, 2));
      var lt2 = new Equation(new Digit[] { new Digit(-4), new Digit(-6) }, new Digit(21));
      Task task = new Task(Task.TaskType.Max, new Limit[] { 
        new Limit(Limit.LimitType.More, lt1), new Limit(Limit.LimitType.More, lt2),
      }, mainEqua);

      using (Solver ss = new GomoryFirstSimplexSolver(task)) {
        do {
          for (int i = 0; i < ss.SizeX(); i++) {
            for (int j = 0; j < ss.SizeY(); j++) {
              richTextBox1.Text += Math.Round(ss.Table(i, j).GetDouble(),2) + "\t";
            }
            richTextBox1.Text += Environment.NewLine;
          }
          richTextBox1.Text += Environment.NewLine;
        } while (ss.StepWork());
        richTextBox1.Text += ss.State();
        int val = ss.Result().Numerator();
        val = ss.Result().Denomerator();
      }
    }
  }
}
