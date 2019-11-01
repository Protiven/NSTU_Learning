using System;
using System.Collections.Generic;
using System.Numerics;

namespace Lab_2
{
    class Program
    {
        static bool prime_check(BigInteger p) 
        {
            BigInteger i = 2;
            while (i * i <= p)
            {
                if (p % i == 0)
                    return false;
                i++;
            }

            return true;
        }

        static List<BigInteger> create_list_of_div(BigInteger n) 
        {
            List<BigInteger> dividers = new List<BigInteger>();
            

            BigInteger current_num = n;
            BigInteger supp = 2;
            bool flag; 
            while (current_num != 1 && supp * supp <= current_num)
            { 
                flag = false;
                while (current_num % supp == 0)
                {
                    current_num /= supp;
                    flag = true;
                }
                if (flag == true)
                    dividers.Add(supp);
                supp++;
            }
            return dividers;
        }

        static bool check_root(BigInteger p, BigInteger g)
        {
            List<BigInteger> dividers = new List<BigInteger>();
            dividers = create_list_of_div(p - 1);

            
            foreach (var d in dividers)
            {
                BigInteger exp = (p - 1) / d;
                BigInteger res = BigInteger.ModPow(g, exp, p);
                if (res == 1)
                    return false;
            }
            return true;
        }

        static BigInteger ElGamal(BigInteger p, BigInteger g)
        {
            var x = RandomBigInteger(p);
            var y = BigInteger.ModPow(g, x, p);
            Console.WriteLine("y = " + y);
            return x;
        }
        static void ElGamal_encryption(BigInteger p, BigInteger g)
        {
            Console.WriteLine("Введите открытый ключ y: ");
            string str = Console.ReadLine();
            BigInteger y = BigInteger.Parse(str);
            Console.WriteLine("Введите сообщение: ");
            str = Console.ReadLine();
            BigInteger M = BigInteger.Parse(str);
            BigInteger k = RandomBigInteger(p);
            var a = BigInteger.ModPow(g, k, p);
            var b = BigInteger.ModPow(y, k, p) * (M % p);
            b %= p;
            Console.WriteLine("a = " + a + " b = " + b);

        }
        static void ElGamal_decryption(BigInteger x, BigInteger a, BigInteger b, BigInteger p)
        {
            BigInteger ret = BigInteger.ModPow(a, x, p);
            var ret2 = BigInteger.ModPow(ret, p - 2, p);
            BigInteger M = ((b % p) * ret2) % p;

            Console.WriteLine("Расшифрованное сообщение M = " + M);
        }

        static BigInteger RandomBigInteger(BigInteger p)
        {
            byte[] bytes = p.ToByteArray();
            BigInteger a;
            Random random = new Random();
            do
            {
                random.NextBytes(bytes);
                bytes[bytes.Length - 1] &= (byte)0x7F; 
                a = new BigInteger(bytes);
            } while (a >= p);

            return a;
        }


        static void Main(string[] args)
        {

            BigInteger p, g;
            Console.WriteLine("Введите p.");
            string str = Console.ReadLine();
            BigInteger x, a, b;
            p = BigInteger.Parse(str);

            Console.WriteLine("Введите g.");
            str = Console.ReadLine();
            g = BigInteger.Parse(str);

            if (prime_check(p))
            { 
                Console.Write("р - простое\n");
               
                if (check_root(p, g))
                {
                    Console.WriteLine("g - первообразный");

                    x = ElGamal(p, g);
                    ElGamal_encryption(p, g);

                    Console.WriteLine("Введите a: ");
                    str = Console.ReadLine();
                    a = BigInteger.Parse(str);


                    Console.WriteLine("Введите b: ");
                    str = Console.ReadLine();
                    b = BigInteger.Parse(str);
                    ElGamal_decryption(x, a, b, p);
                }
                else Console.WriteLine("g - не первообразный");
            }
            else Console.Write("p - не простое\n");

            Console.WriteLine("Программа завершена.");
            Console.ReadKey();
        }
    } 
}
