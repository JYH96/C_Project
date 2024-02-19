using System.Linq.Expressions;
using System.Text.RegularExpressions;
using System.Collections;
using System;
using System.Collections.Generic;
namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        static private float Cal(float x, float y, char z)
        {
            switch (z)
            {
                case '+':
                    return x + y;
                case '-':
                    return x - y;
                case '×':
                    return x * y;
                case '÷':
                    return x / y;
                default:
                    throw new Exception("잘못된 연산자");
            }
        }
        public List<char> opr = ['+', '-', '×', '÷'];

        public Form1()
        {
            InitializeComponent();
        }
        private void B1_Click(object sender, EventArgs e)
        {
            formula.Text += B1.Text;
        }
        private void B2_Click(object sender, EventArgs e)
        {
            formula.Text += B2.Text;
        }
        private void B3_Click(object sender, EventArgs e)
        {
            formula.Text += B3.Text;
        }
        private void B4_Click(object sender, EventArgs e)
        {
            formula.Text += B4.Text;
        }
        private void B5_Click(object sender, EventArgs e)
        {
            formula.Text += B5.Text;
        }
        private void B6_Click(object sender, EventArgs e)
        {
            formula.Text += B6.Text;
        }
        private void B7_Click(object sender, EventArgs e)
        {
            formula.Text += B7.Text;
        }
        private void B8_Click(object sender, EventArgs e)
        {
            formula.Text += B8.Text;
        }
        private void B9_Click(object sender, EventArgs e)
        {
            formula.Text += B9.Text;
        }
        private void B0_Click(object sender, EventArgs e)
        {
            formula.Text += B0.Text;
        }

        private void B_div_Click(object sender, EventArgs e)
        {
            formula.Text += B_div.Text;
        }

        private void AC_Click(object sender, EventArgs e)
        {
            formula.Text = "";
        }

        private void B_mul_Click(object sender, EventArgs e)
        {
            formula.Text += B_mul.Text;
        }

        private void B_plus_Click(object sender, EventArgs e)
        {
            formula.Text += B_plus.Text;
        }

        private void B_min_Click(object sender, EventArgs e)
        {
            formula.Text += B_min.Text;
        }

        private void B_dot_Click(object sender, EventArgs e)
        {
            formula.Text += B_dot.Text;
        }

        private void B_eqe_Click(object sender, EventArgs e)
        {
            List<string> devided_num_string = formula.Text.Split('+', '-', '×', '÷').ToList();

            try
            {
                List<char> devided_opr = [];
                List<float> devided_num = [];

                foreach (string i in devided_num_string)
                {
                    devided_num.Add(float.Parse(i));
                }
                for (int i = 0; i < formula.Text.Length; i++)
                {
                    if (opr.Contains(formula.Text[i]))
                    {
                        devided_opr.Add(formula.Text[i]);
                    }
                }

                int current_index = 0;
                while (current_index < devided_opr.Count)
                {
                    if (devided_opr[current_index] == '×' || devided_opr[current_index] == '÷')
                    {
                        devided_num[current_index] = Cal(devided_num[current_index], devided_num[current_index + 1], devided_opr[current_index]);
                        devided_num.RemoveAt(current_index + 1);
                        devided_opr.RemoveAt(current_index);
                    }
                    else
                    {
                        current_index++;
                    }
                }
                current_index = 0;
                while (current_index < devided_opr.Count)
                {
                    if (devided_opr[current_index] == '+' || devided_opr[current_index] == '-')
                    {
                        devided_num[current_index] = Cal(devided_num[current_index], devided_num[current_index + 1], devided_opr[current_index]);
                        devided_num.RemoveAt(current_index + 1);
                        devided_opr.RemoveAt(current_index);
                    }
                    else
                    {
                        current_index++;
                    }
                }
                formula.Text = devided_num[0].ToString();
            }
            catch
            {
                formula.Text = "잘못된 수식";
            }
        }
    }    
}


