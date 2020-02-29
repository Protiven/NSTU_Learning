using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


class Program
{
    static double func(double t, double y)
    {
        return 2 * y * t;
    }
    static void Main()
    {
        double h = 0.1, t = 0;
        int i = 0;

        double[] y_ideal = new double[401];
        double[] method1 = new double[401];
        double[] method2 = new double[401];
        double[] method3 = new double[401];

        method1[0] = 0;
        method2[0] = 0;
        method3[0] = 0;


        for (; t <= 1; t += h)
        {
            y_ideal[i] = Math.Exp(Math.Pow(t, 2));

            if (i != 0)
            {
                method1[i] = y_ideal[i - 1] + h * func(t, y_ideal[i - 1]);
                method2[i] = y_ideal[i - 1] + h / 2 * (func(t, y_ideal[i - 1]) + func(t + h, y_ideal[i - 1] + h * func(t, y_ideal[i - 1])));
                method3[i] = y_ideal[i - 1] + h * func(1 / 2 * (t + t + h), y_ideal[i - 1] + h / 2 * func(t, y_ideal[i - 1]));
            }
            i++;
        }


        Stream stream1 = new FileStream("out1.txt", FileMode.OpenOrCreate);
        Stream stream2 = new FileStream("out2.txt", FileMode.OpenOrCreate);
        Stream stream3 = new FileStream("out3.txt", FileMode.OpenOrCreate);
        StreamWriter sw1 = new StreamWriter(stream1, Encoding.UTF8);
        StreamWriter sw2 = new StreamWriter(stream2, Encoding.UTF8);
        StreamWriter sw3 = new StreamWriter(stream3, Encoding.UTF8);


        i = 0;
        t = 0;
        for (i = 0; i <= 10; i++)
        {
            sw1.WriteLine(t + "\t" + y_ideal[i] + "\t" + method1[i] + "\t" + Math.Abs(y_ideal[i] - method1[i]));
            sw2.WriteLine(t + "\t" + y_ideal[i] + "\t" + method2[i] + "\t" + Math.Abs(y_ideal[i] - method2[i]));
            sw3.WriteLine(t + "\t" + y_ideal[i] + "\t" + method3[i] + "\t" + Math.Abs(y_ideal[i] - method3[i]));
            t += h;
        }

        sw1.Close();
        sw2.Close();
        sw3.Close();



        
        i = 0;
        t = 0;
        h = 0.05;

        for (; t <= 1; t += h)
        {
            y_ideal[i] = Math.Exp(Math.Pow(t, 2));

            if (i != 0)
            {
                method1[i] = y_ideal[i - 1] + h * func(t, y_ideal[i - 1]);
                method2[i] = y_ideal[i - 1] + h / 2 * (func(t, y_ideal[i - 1]) + func(t + h, y_ideal[i - 1] + h * func(t, y_ideal[i - 1])));
                method3[i] = y_ideal[i - 1] + h * func(1 / 2 * (t + t + h), y_ideal[i - 1] + h / 2 * func(t, y_ideal[i - 1]));
            }
            i++;
        }



        Stream stream4 = new FileStream("out4.txt", FileMode.OpenOrCreate);
        Stream stream5 = new FileStream("out5.txt", FileMode.OpenOrCreate);
        Stream stream6 = new FileStream("out6.txt", FileMode.OpenOrCreate);
        StreamWriter sw4 = new StreamWriter(stream4, Encoding.UTF8);
        StreamWriter sw5 = new StreamWriter(stream5, Encoding.UTF8);
        StreamWriter sw6 = new StreamWriter(stream6, Encoding.UTF8);


        i = 0;
        t = 0;
        for (i = 0; i <= 20; i++)
        {
            sw4.WriteLine(t + "\t" + y_ideal[i] + "\t" + method1[i] + "\t" + Math.Abs(y_ideal[i] - method1[i]));
            sw5.WriteLine(t + "\t" + y_ideal[i] + "\t" + method2[i] + "\t" + Math.Abs(y_ideal[i] - method2[i]));
            sw6.WriteLine(t + "\t" + y_ideal[i] + "\t" + method3[i] + "\t" + Math.Abs(y_ideal[i] - method3[i]));
            t += h;
        }

        sw4.Close();
        sw5.Close();
        sw6.Close();



        i = 0;
        t = 0;
        h = 0.0025;

        for (; t <= 1; t += h)
        {
            y_ideal[i] = Math.Exp(Math.Pow(t, 2));

            if (i != 0)
            {
                method1[i] = y_ideal[i - 1] + h * func(t, y_ideal[i - 1]);
                method2[i] = y_ideal[i - 1] + h / 2 * (func(t, y_ideal[i - 1]) + func(t + h, y_ideal[i - 1] + h * func(t, y_ideal[i - 1])));
                method3[i] = y_ideal[i - 1] + h * func(1 / 2 * (t + t + h), y_ideal[i - 1] + h / 2 * func(t, y_ideal[i - 1]));
            }
            i++;
        }


        Stream stream7 = new FileStream("out7.txt", FileMode.OpenOrCreate);
        Stream stream8 = new FileStream("out8.txt", FileMode.OpenOrCreate);
        Stream stream9 = new FileStream("out9.txt", FileMode.OpenOrCreate);
        StreamWriter sw7 = new StreamWriter(stream7, Encoding.UTF8);
        StreamWriter sw8 = new StreamWriter(stream8, Encoding.UTF8);
        StreamWriter sw9 = new StreamWriter(stream9, Encoding.UTF8);


        i = 0;
        t = 0;
        for (i = 0; i <= 400; i++)
        {
            sw7.WriteLine(t + "\t" + y_ideal[i] + "\t" + method1[i] + "\t" + Math.Abs(y_ideal[i] - method1[i]));
            sw8.WriteLine(t + "\t" + y_ideal[i] + "\t" + method2[i] + "\t" + Math.Abs(y_ideal[i] - method2[i]));
            sw9.WriteLine(t + "\t" + y_ideal[i] + "\t" + method3[i] + "\t" + Math.Abs(y_ideal[i] - method3[i]));
            t += h;
        }

        sw7.Close();
        sw8.Close();
        sw9.Close();
    }
}

