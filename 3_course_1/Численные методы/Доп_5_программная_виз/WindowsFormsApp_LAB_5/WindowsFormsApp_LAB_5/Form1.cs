using System;
using System.IO;
using System.Windows.Forms.DataVisualization;
using System.Windows.Forms.DataVisualization.Charting;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp_LAB_5
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

        }

        private void button1_Click(object sender, EventArgs e)
        {
            var g = panel1.CreateGraphics();
            var size = new Size(10, 10);
            ControlPaint.DrawGrid(g, Rectangle.FromLTRB(-10, 10, 10, -10), size, Color.Black);

            g.DrawLine(new Pen(Color.Black), 2, 5, 120, 200);


            if (!string.IsNullOrWhiteSpace(textBox1.Text))
            {
                string str_from_file;
                
                switch (comboBox2.SelectedIndex)
                {
                }

                chart1.Series["Series1"].ChartType = SeriesChartType.
                try
                {
                    using (var sr = new StreamReader(textBox1.Text))
                    {
                        str_from_file = sr.ReadToEnd();
                    }

                    var symbols = str_from_file.Split();

                    if (symbols.Length % 2 == 0)
                    {
                        var X_values = new double[symbols.Length / 2];
                        var Y_values = new double[symbols.Length / 2];

                        for (int i = 0; i < symbols.Length; i++)
                        {
                            X_values[i] = Convert.ToDouble(symbols[2 * i]);
                            Y_values[i] = Convert.ToDouble(symbols[2 * i + 1]);
                        }



                    }
                
                } catch (Exception exc)
                {
                    // Let the user know what went wrong.
                    Console.WriteLine("The file could not be read:");
                    Console.WriteLine(exc.Message);
                }
            }
        }

        /*
        private void button1_Click(object sender, EventArgs e)
        {

            bool flag = true;

            double x_min = -5;
            double x_max = 10;
            double y_min = 7;
            double y_max = 10;

            if (flag)
                if (x_min < x_max && y_min < y_max)
                {
                    chart1.ChartAreas[0].AxisX.Minimum = x_min;
                    chart1.ChartAreas[0].AxisX.Maximum = x_max;

                    chart1.ChartAreas[0].AxisX.Minimum = y_min;
                    chart1.ChartAreas[0].AxisX.Maximum = y_max;
                }

            chart1.ChartAreas[0].AxisX.Minimum = x_min;
            chart1.ChartAreas[0].AxisX.Maximum = x_max;

            chart1.ChartAreas[0].AxisX.Minimum = y_min;
            chart1.ChartAreas[0].AxisX.Maximum = y_max;


            chart1.Series.Add("Series2");
            chart1.Series["Series1"].ChartType = SeriesChartType.FastLine;
            chart1.Series["Series2"].ChartType = SeriesChartType.FastLine;
            

            for (int i = 0; i < 10; i++)
                chart1.Series["Series1"].Points.AddXY(i, -i + 1);

            

            for (int i = 0; i < 10; i++)
                chart1.Series["Series2"].Points.AddXY(i, -i + 3);
               
        }
        */
    }
}
