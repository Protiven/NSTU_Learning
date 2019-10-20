using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace test1
{
    class Program
    {
        static void Main(string[] args)
        {
            Thread s = new Thread(read);
            s.Start();
            do 
            {
                Console.WriteLine("Line");
                Thread.Sleep(2000);
            } while (true);


        }
        public static void read()
        {
            string s;
            s = Console.ReadLine();
            if (s == "Hello")
                Console.WriteLine("Ok");
        }
    }
}
