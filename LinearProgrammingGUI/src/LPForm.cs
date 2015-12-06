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
      var lt2 = new Equation(new Digit[] { new Digit(-2,3), new Digit(-1) }, new Digit(7,2));
      Task task = new Task(Task.TaskType.Max, new Limit[] { 
        new Limit(Limit.LimitType.More, lt1), new Limit(Limit.LimitType.More, lt2),
      }, mainEqua);

      using (SimplexSolver ss = new SimplexSolver(task)) {
        do {
          MessageBox.Show(ss.State().ToString());
        } while (ss.StepWork());
      }
    }
  }
}
