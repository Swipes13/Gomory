namespace LinearProgrammingGUI {
  partial class LPForm {
    /// <summary>
    /// Требуется переменная конструктора.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Освободить все используемые ресурсы.
    /// </summary>
    /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
    protected override void Dispose(bool disposing) {
      if (disposing && (components != null)) {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Код, автоматически созданный конструктором форм Windows

    /// <summary>
    /// Обязательный метод для поддержки конструктора - не изменяйте
    /// содержимое данного метода при помощи редактора кода.
    /// </summary>
    private void InitializeComponent() {
      this.richTextBox1 = new System.Windows.Forms.RichTextBox();
      this.panel1 = new System.Windows.Forms.Panel();
      this.dgvSolver = new System.Windows.Forms.DataGridView();
      this.button1 = new System.Windows.Forms.Button();
      this.panel1.SuspendLayout();
      ((System.ComponentModel.ISupportInitialize)(this.dgvSolver)).BeginInit();
      this.SuspendLayout();
      // 
      // richTextBox1
      // 
      this.richTextBox1.Location = new System.Drawing.Point(393, 105);
      this.richTextBox1.Name = "richTextBox1";
      this.richTextBox1.Size = new System.Drawing.Size(284, 181);
      this.richTextBox1.TabIndex = 0;
      this.richTextBox1.Text = "";
      // 
      // panel1
      // 
      this.panel1.Controls.Add(this.dgvSolver);
      this.panel1.Dock = System.Windows.Forms.DockStyle.Left;
      this.panel1.Location = new System.Drawing.Point(0, 0);
      this.panel1.Name = "panel1";
      this.panel1.Size = new System.Drawing.Size(391, 377);
      this.panel1.TabIndex = 1;
      // 
      // dgvSolver
      // 
      this.dgvSolver.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgvSolver.Dock = System.Windows.Forms.DockStyle.Fill;
      this.dgvSolver.Location = new System.Drawing.Point(0, 0);
      this.dgvSolver.Name = "dgvSolver";
      this.dgvSolver.Size = new System.Drawing.Size(391, 377);
      this.dgvSolver.TabIndex = 0;
      // 
      // button1
      // 
      this.button1.Location = new System.Drawing.Point(462, 33);
      this.button1.Name = "button1";
      this.button1.Size = new System.Drawing.Size(145, 56);
      this.button1.TabIndex = 2;
      this.button1.Text = "button1";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new System.EventHandler(this.button1_Click);
      // 
      // LPForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(689, 377);
      this.Controls.Add(this.button1);
      this.Controls.Add(this.panel1);
      this.Controls.Add(this.richTextBox1);
      this.Name = "LPForm";
      this.ShowIcon = false;
      this.Text = "Linear Programming";
      this.panel1.ResumeLayout(false);
      ((System.ComponentModel.ISupportInitialize)(this.dgvSolver)).EndInit();
      this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.RichTextBox richTextBox1;
    private System.Windows.Forms.Panel panel1;
    private System.Windows.Forms.DataGridView dgvSolver;
    private System.Windows.Forms.Button button1;
  }
}

