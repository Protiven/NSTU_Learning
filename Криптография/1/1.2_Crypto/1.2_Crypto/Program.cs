
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
        Console.WriteLine("Введите имя ключа, текста и куда зашифровать текст: ");
        string[] Names = new string[3];
        for(int i = 0; i<3; i++)
            Names[i] = Console.ReadLine();

        // Считали ключ
        string sup = null;
        Stream stream1 = new FileStream(Names[0], FileMode.Open);
        StreamReader sw = new StreamReader(stream1);

        for (int i = 0; i < 33; i++)
            sup = sup + sw.ReadLine(); 
        sw.Close();

        string key = sup;
        //
        
        // Считали текст
        string text = null;
        text = File.ReadAllText(Names[1], Encoding.UTF8);
        //

        // Форматирование текста
        string sup3 = null;

        foreach (char c in text)
        {
            int sup_3 = Convert.ToInt32(c);
            if (sup_3 >= 1040 && sup_3 <= 1071)
                sup3 = sup3 + Convert.ToChar(sup_3 + 32);
            else if (sup_3 == 1025)
                sup3 = sup3 + Convert.ToChar(1105);
            else
                sup3 = sup3 + c;
        }
        text = sup3;
        

        string sup_2 = null;
        foreach (char i1 in text)
        {
           
            int sup_1 = Convert.ToInt32(i1);
            if (sup_1 >= 1072 && sup_1 <= 1103 || sup_1 == 1105)
            {
                sup_2 = sup_2 + i1;
            }
        }
        text = sup_2;
        //
        Console.WriteLine(text);

        // Шифрование текста
        int flag = 1;
        char[] text1 = text.ToCharArray();
        char[] sup_4 = key.ToCharArray();
       

        for (int i = 0; i < text1.Length; i++)
        {
            for (int j = 0; j < 33 && flag == 1; j++)
            {
                if (text1[i] == 'ё')
                {
                    text1[i] = sup_4[6];
                    flag = 0;
                }
                else if (text1[i] == Convert.ToChar(1072 + j) && j < 6)
                {
                    text1[i] = sup_4[j];
                    flag = 0;
                }
                else if (text1[i] == Convert.ToChar(1072 + j) && j >= 6)
                {
                    text1[i] = sup_4[j+1];
                    flag = 0;
                }
            }
            flag = 1;
        }


        // Вывод текста в файл
        Stream stream2 = new FileStream(Names[2], FileMode.OpenOrCreate);
        StreamWriter sw2 = new StreamWriter(stream2, Encoding.UTF8);

        sw2.WriteLine(text1);
        sw2.Close();
        //
    }
}

