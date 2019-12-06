using System;
using System.IO;
using System.Drawing;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Cryptography.X509Certificates;
using System.Security.Cryptography;

namespace LAB_3
{
    class Program
    {
        static protected int gener_cert()
        {

            using (var rsa = RSA.Create(2048))
            {
                var req1 = new CertificateRequest(
                    "CN=VOSTRIKOV_BASHTOVOY",
                    rsa,
                    HashAlgorithmName.SHA256,
                    RSASignaturePadding.Pkcs1);
                
                var cert1 = req1.CreateSelfSigned(DateTimeOffset.UtcNow, DateTimeOffset.UtcNow);


            
                File.WriteAllBytes("test.cer", cert1.Export(X509ContentType.Cert));
                File.WriteAllBytes("test.pem", cert1.Export(X509ContentType.Pkcs12));
            }

            return 1;
        }

        static protected int program_1() // Генерация подписи 
        {
            Console.WriteLine("Введите имя файла и сертификата с закрытым ключом.");
            string[] str = Console.ReadLine().Split(); // 0 - файл, 1 - сертификат
            string sgn_name = str[0].Split('.')[0] + ".sgn";

            // Получение байт изображения
            var b_file = File.ReadAllBytes(str[0]);

            // Шифрование Хэш-суммы
            var cert = new X509Certificate2(str[1]);
            var podpis = cert.GetRSAPrivateKey().SignData(b_file, HashAlgorithmName.SHA256, RSASignaturePadding.Pkcs1);

            // Вывод подписи
            File.WriteAllBytes(sgn_name, podpis);
           
            return 1;
        }

        static protected int program_2() // Вычисление хэш-суммы
        {
            Console.WriteLine("Введите имя файла и имя хэша.");
            string[] str = Console.ReadLine().Split(); // 0 - файл, 1 - сертификат
            
            // Получение байт изображения
            var b_file = File.ReadAllBytes(str[0]);
            
            // Хэш-сумма файла
            var hash = HashAlgorithm.Create("SHA-256");
            b_file = hash.ComputeHash(b_file);

            File.WriteAllBytes(str[1], b_file);
            return 1;
        }

        static protected int program_3() // Валидация подписи и хэша
        {
            Console.WriteLine("Введите имя подписи, имя файла, имя сертификата, имя хэша.");
            string[] str = Console.ReadLine().Split();
            string sgn_name = str[0];

            // Получение подписи
            byte[] podpis_bytes = File.ReadAllBytes(sgn_name);

            // Получение Байт изображения
            var b_file = File.ReadAllBytes(str[1]);

            // Расшифровка подписи с помощью сертифика
            var cert = new X509Certificate2(str[2]);
            
            if (cert.GetRSAPublicKey().VerifyData(b_file, podpis_bytes, HashAlgorithmName.MD5, RSASignaturePadding.Pkcs1))
                Console.WriteLine("Четкая подпись! (результат VerifyData)");
            else
                Console.WriteLine("НЕчеткая подпись! (результат VerifyData)");

            var hash_b = File.ReadAllBytes(str[3]);


            if (cert.GetRSAPublicKey().VerifyHash(hash_b, podpis_bytes, HashAlgorithmName.MD5, RSASignaturePadding.Pkcs1))
                Console.WriteLine("Четкий хэш! (результат VerifyHash)");
            else
                Console.WriteLine("НЕчеткий хэш! (результат VerifyHash)"); ;
            return 1;
        }
        static void Main()
        {
            int choice;
            bool flag = false;
            Console.WriteLine("1 - сгенерировать сертификаты, 2 - генерация подписи, 3 - Вычисление хэш функции файла, 4 - Валидация подписи.");
            choice = Convert.ToInt16(Console.ReadLine());

            switch (choice)
            {
                case 1:
                    flag = Convert.ToBoolean(gener_cert());
                    break;
                case 2:
                    flag = Convert.ToBoolean(program_1());
                    break;
                case 3:
                    flag = Convert.ToBoolean(program_2());
                    break;
                case 4:
                    flag = Convert.ToBoolean(program_3());
                    break;
            }

            if (!flag)
                Console.WriteLine("Программа завершилась некорректно!");
            Console.ReadKey();
        }
    }
}
