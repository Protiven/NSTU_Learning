using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class Program
{
    public static void Main()
    {
        Console.WriteLine("Введите имя файла: ");
        string str = Console.ReadLine(); // 1072 - а, 1103 - я, 1105 - ё

        // Заполняем алфавит
        char[] f = new char[33];
        for (int i = 0; i < 32; i++)
        {
            f[i] = Convert.ToChar(1072 + i);
        }
        f[32] = Convert.ToChar(1105);
        //

        // Перемешивание
        Random rand = new Random();
        int j;
        char sup;

        for (int i = f.Length - 1; i != 0; i--)
        {
            j = rand.Next(i);
            sup = f[i];
            f[i] = f[j];
            f[j] = sup;
        }
        //    
        
        // Запись ключа в файл 
        Stream stream= new FileStream(str, FileMode.OpenOrCreate);
        StreamWriter sw = new StreamWriter(stream, Encoding.UTF8);

        for (int i = 0; i < 33; i++)
            sw.WriteLine(f[i]);
        sw.Close();
        // 
    }
}