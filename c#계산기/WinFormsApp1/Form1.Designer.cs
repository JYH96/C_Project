namespace WinFormsApp1
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            tableLayoutPanel1 = new TableLayoutPanel();
            AC = new Button();
            B0 = new Button();
            B_dot = new Button();
            B_min = new Button();
            B1 = new Button();
            B2 = new Button();
            B3 = new Button();
            B_plus = new Button();
            B4 = new Button();
            B5 = new Button();
            B6 = new Button();
            B_mul = new Button();
            B_div = new Button();
            B9 = new Button();
            B8 = new Button();
            B7 = new Button();
            B_eqe = new Button();
            formula = new Label();
            tableLayoutPanel1.SuspendLayout();
            SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            tableLayoutPanel1.ColumnCount = 4;
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 25F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 25F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 25F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 25F));
            tableLayoutPanel1.Controls.Add(AC, 0, 3);
            tableLayoutPanel1.Controls.Add(B0, 1, 3);
            tableLayoutPanel1.Controls.Add(B_dot, 2, 3);
            tableLayoutPanel1.Controls.Add(B_min, 3, 3);
            tableLayoutPanel1.Controls.Add(B1, 0, 2);
            tableLayoutPanel1.Controls.Add(B2, 1, 2);
            tableLayoutPanel1.Controls.Add(B3, 2, 2);
            tableLayoutPanel1.Controls.Add(B_plus, 3, 2);
            tableLayoutPanel1.Controls.Add(B4, 0, 1);
            tableLayoutPanel1.Controls.Add(B5, 1, 1);
            tableLayoutPanel1.Controls.Add(B6, 2, 1);
            tableLayoutPanel1.Controls.Add(B_mul, 3, 1);
            tableLayoutPanel1.Controls.Add(B_div, 3, 0);
            tableLayoutPanel1.Controls.Add(B9, 2, 0);
            tableLayoutPanel1.Controls.Add(B8, 1, 0);
            tableLayoutPanel1.Controls.Add(B7, 0, 0);
            tableLayoutPanel1.Location = new Point(2, 76);
            tableLayoutPanel1.Name = "tableLayoutPanel1";
            tableLayoutPanel1.RowCount = 4;
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 25F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 25F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 25F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 25F));
            tableLayoutPanel1.Size = new Size(480, 400);
            tableLayoutPanel1.TabIndex = 0;
            // 
            // AC
            // 
            AC.Location = new Point(3, 303);
            AC.Name = "AC";
            AC.Size = new Size(114, 94);
            AC.TabIndex = 15;
            AC.Text = "AC";
            AC.UseVisualStyleBackColor = true;
            AC.Click += AC_Click;
            // 
            // B0
            // 
            B0.Location = new Point(123, 303);
            B0.Name = "B0";
            B0.Size = new Size(114, 94);
            B0.TabIndex = 14;
            B0.Text = "0";
            B0.UseVisualStyleBackColor = true;
            B0.Click += B0_Click;
            // 
            // B_dot
            // 
            B_dot.Location = new Point(243, 303);
            B_dot.Name = "B_dot";
            B_dot.Size = new Size(114, 94);
            B_dot.TabIndex = 13;
            B_dot.Text = ".";
            B_dot.UseVisualStyleBackColor = true;
            B_dot.Click += B_dot_Click;
            // 
            // B_min
            // 
            B_min.Location = new Point(363, 303);
            B_min.Name = "B_min";
            B_min.Size = new Size(114, 94);
            B_min.TabIndex = 12;
            B_min.Text = "-";
            B_min.UseVisualStyleBackColor = true;
            B_min.Click += B_min_Click;
            // 
            // B1
            // 
            B1.Location = new Point(3, 203);
            B1.Name = "B1";
            B1.Size = new Size(114, 94);
            B1.TabIndex = 11;
            B1.Text = "1";
            B1.UseVisualStyleBackColor = true;
            B1.Click += B1_Click;
            // 
            // B2
            // 
            B2.Location = new Point(123, 203);
            B2.Name = "B2";
            B2.Size = new Size(114, 94);
            B2.TabIndex = 10;
            B2.Text = "2";
            B2.UseVisualStyleBackColor = true;
            B2.Click += B2_Click;
            // 
            // B3
            // 
            B3.Location = new Point(243, 203);
            B3.Name = "B3";
            B3.Size = new Size(114, 94);
            B3.TabIndex = 9;
            B3.Text = "3";
            B3.UseVisualStyleBackColor = true;
            B3.Click += B3_Click;
            // 
            // B_plus
            // 
            B_plus.Location = new Point(363, 203);
            B_plus.Name = "B_plus";
            B_plus.Size = new Size(114, 94);
            B_plus.TabIndex = 8;
            B_plus.Text = "+";
            B_plus.UseVisualStyleBackColor = true;
            B_plus.Click += B_plus_Click;
            // 
            // B4
            // 
            B4.Location = new Point(3, 103);
            B4.Name = "B4";
            B4.Size = new Size(114, 94);
            B4.TabIndex = 7;
            B4.Text = "4";
            B4.UseVisualStyleBackColor = true;
            B4.Click += B4_Click;
            // 
            // B5
            // 
            B5.Location = new Point(123, 103);
            B5.Name = "B5";
            B5.Size = new Size(114, 94);
            B5.TabIndex = 6;
            B5.Text = "5";
            B5.UseVisualStyleBackColor = true;
            B5.Click += B5_Click;
            // 
            // B6
            // 
            B6.Location = new Point(243, 103);
            B6.Name = "B6";
            B6.Size = new Size(114, 94);
            B6.TabIndex = 5;
            B6.Text = "6";
            B6.UseVisualStyleBackColor = true;
            B6.Click += B6_Click;
            // 
            // B_mul
            // 
            B_mul.Location = new Point(363, 103);
            B_mul.Name = "B_mul";
            B_mul.Size = new Size(114, 94);
            B_mul.TabIndex = 4;
            B_mul.Text = "×";
            B_mul.UseVisualStyleBackColor = true;
            B_mul.Click += B_mul_Click;
            // 
            // B_div
            // 
            B_div.Location = new Point(363, 3);
            B_div.Name = "B_div";
            B_div.Size = new Size(114, 94);
            B_div.TabIndex = 3;
            B_div.Text = "÷";
            B_div.UseVisualStyleBackColor = true;
            B_div.Click += B_div_Click;
            // 
            // B9
            // 
            B9.Location = new Point(243, 3);
            B9.Name = "B9";
            B9.Size = new Size(114, 94);
            B9.TabIndex = 2;
            B9.Text = "9";
            B9.UseVisualStyleBackColor = true;
            B9.Click += B9_Click;
            // 
            // B8
            // 
            B8.Location = new Point(123, 3);
            B8.Name = "B8";
            B8.Size = new Size(114, 94);
            B8.TabIndex = 1;
            B8.Text = "8";
            B8.UseVisualStyleBackColor = true;
            B8.Click += B8_Click;
            // 
            // B7
            // 
            B7.Location = new Point(3, 3);
            B7.Name = "B7";
            B7.Size = new Size(114, 94);
            B7.TabIndex = 0;
            B7.Text = "7";
            B7.UseVisualStyleBackColor = true;
            B7.Click += B7_Click;
            // 
            // B_eqe
            // 
            B_eqe.BackColor = SystemColors.Control;
            B_eqe.Dock = DockStyle.Bottom;
            B_eqe.Location = new Point(0, 473);
            B_eqe.Name = "B_eqe";
            B_eqe.Size = new Size(482, 80);
            B_eqe.TabIndex = 1;
            B_eqe.Text = "=";
            B_eqe.UseVisualStyleBackColor = false;
            B_eqe.Click += B_eqe_Click;
            // 
            // formula
            // 
            formula.Dock = DockStyle.Top;
            formula.Font = new Font("맑은 고딕", 20F);
            formula.Location = new Point(0, 0);
            formula.Name = "formula";
            formula.Size = new Size(482, 73);
            formula.TabIndex = 2;
            formula.TextAlign = ContentAlignment.MiddleRight;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(9F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(482, 553);
            Controls.Add(formula);
            Controls.Add(B_eqe);
            Controls.Add(tableLayoutPanel1);
            Name = "Form1";
            Text = "Form1";
            tableLayoutPanel1.ResumeLayout(false);
            ResumeLayout(false);
        }

        #endregion

        private TableLayoutPanel tableLayoutPanel1;
        private Button B_eqe;
        private Button AC;
        private Button B0;
        private Button B_dot;
        private Button B_min;
        private Button B1;
        private Button B2;
        private Button B3;
        private Button B_plus;
        private Button B4;
        private Button B5;
        private Button B6;
        private Button B_div;
        private Button B9;
        private Button B8;
        private Button B7;
        private Label formula;
        private Button B_mul;
    }
}
