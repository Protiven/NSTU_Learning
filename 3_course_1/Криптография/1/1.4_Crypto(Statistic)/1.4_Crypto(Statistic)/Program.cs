using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class elem
{
    public int count;
    public char ch;
    public elem()
    {
        count = 0;
        ch = new char();
    }

    public static bool operator >(elem c1, elem c2)
    {
        return c1.count > c2.count;
    }
    public static bool operator <(elem c1, elem c2)
    {
        return c1.count < c2.count;
    }
}

class Program
{
    static void Main()
    {
        elem[] array = new elem[33];

        for (int i = 0; i < 33; i++)
            array[i] = new elem();


        for (int i = 0; i < 6; i++)
            array[i].ch = Convert.ToChar(1072 + i);
        array[6].ch = 'ё';
        for (int i = 7; i < 33; i++)
            array[i].ch = Convert.ToChar(1072 + i);

        string addres, str;
        Console.WriteLine("Введите имя текста: ");
        addres = Console.ReadLine();        

        Stream stream = new FileStream(addres, FileMode.Open);
        StreamReader sw = new StreamReader(stream);
        str = sw.ReadLine();
        char[] text = str.ToCharArray();

        int add_counter = 0;

        for (int i = 0; i < array.Length && add_counter != text.Length; i++)
            for (int j = 0; j < text.Length; j++)
                if (array[i].ch == text[j])
                {
                    array[i].count++;
                    add_counter++;
                }
        elem temp;
        for (int i = 0; i < array.Length; i++)
        {
            for (int j = i + 1; j < array.Length; j++)
            {
                if (array[i] < array[j])
                {
                    temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }

        for (int i = 0; i < array.Length; i++)
            Console.WriteLine("{0} - {1}", array[i].ch, array[i].count);

        Console.WriteLine("Нажмите Q для выхода.");
        for (; ; )
            if (Console.ReadKey().Key == ConsoleKey.Q)
                break;
    }
}
