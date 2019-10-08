using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class Program
{
    static void Main()
    {
        string str, str1;
        Console.ForegroundColor = ConsoleColor.Yellow;
        Console.WriteLine("Введите имя файла зашифровонного текста: ");
        Console.ResetColor();

        str1 = Console.ReadLine();


        Stream stream = new FileStream(str1, FileMode.Open);
        StreamReader sw = new StreamReader(stream);
        str = sw.ReadLine();
        sw.Close();

        char[] array_ch = str.ToCharArray();
        int[] flag = new int[str.Length];

        for (int i = 0; i < flag.Length; i++)
            flag[i] = 0;

        Console.WriteLine(array_ch);

        for (; ; )
        {
            char c1, c2;
            string s1, s2;

            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine("Введите 'что изменить' и 'на что изменить':");
            Console.ResetColor();


            s1 = Console.ReadLine();
            s2 = Console.ReadLine();

            c1 = s1[0];
            c2 = s2[0];

            for (int i = 0; i < array_ch.Length; i++)
                if (array_ch[i] == c1 && flag[i]!=1)
                {
                    int check = Convert.ToInt32(c2);
                    if (check >= 1072 && check <= 1103)
                        array_ch[i] = Convert.ToChar(check - 32);
                    else if (check == 1105)
                        array_ch[i] = Convert.ToChar(1025);
                    flag[i] = 1;
                }

            for (int i = 0; i < array_ch.Length; i++)
            {
                if (array_ch[i] >= 1040 && array_ch[i] <= 1071 || array_ch[i] == 1025)
                    Console.ForegroundColor = ConsoleColor.Green;
                Console.Write(array_ch[i]);
                Console.ResetColor();
            }
            Console.WriteLine();

            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine("Если текст расшифрован, нажмите Q.");
            if (Console.ReadKey().Key == ConsoleKey.Q)
                break;
            Console.WriteLine();
            Console.ResetColor();
        }
    }
}