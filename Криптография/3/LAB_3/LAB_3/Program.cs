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
                
                
                
                
                //var cert2 = req2.CreateSelfSigned(DateTimeOffset.UtcNow, DateTimeOffset.UtcNow);

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
            Bitmap image = new Bitmap(str[0]);
            System.IO.MemoryStream memoryStream = new System.IO.MemoryStream();
            image.Save(memoryStream, System.Drawing.Imaging.ImageFormat.Png);
            byte[] b_file = memoryStream.ToArray();

            // Хэш-сумма файла
            var hash = HashAlgorithm.Create("SHA-256");
            hash.ComputeHash(b_file);

            // Шифрование Хэш-суммы
            var cert = new X509Certificate2(str[1]);
            RSACryptoServiceProvider crypt = (RSACryptoServiceProvider)cert.PrivateKey;
            Byte[] encryption_hash = crypt.Encrypt(Encoding.ASCII.GetBytes(hash.ToString()), true);

            // Вывод подписи
            File.WriteAllBytes(sgn_name, encryption_hash);
           
            return 1;
        }

        static protected int program_2() // Вычисление хэш-суммы
        {
            Console.WriteLine("Введите имя файла и имя хэша.");
            string[] str = Console.ReadLine().Split(); // 0 - файл, 1 - сертификат

            // Получение байт изображения
            Bitmap image = new Bitmap(str[0]);
            System.IO.MemoryStream memoryStream = new System.IO.MemoryStream();
            image.Save(memoryStream, System.Drawing.Imaging.ImageFormat.Png);
            byte[] b_file = memoryStream.ToArray();

            // Хэш-сумма файла
            var hash = HashAlgorithm.Create("SHA-256");
            hash.ComputeHash(b_file);

            File.WriteAllText(str[1], hash.ToString());

            return 1;
        }

        static protected int program_3() // Валидация подписи
        {
            Console.WriteLine("Введите имя файла, имя хэша, имя сертификата.");
            string[] str = Console.ReadLine().Split();
            string sgn_name = str[0].Split('.')[0] + ".sgn";

            // Получение подписи
            string hash_str = File.ReadAllText(sgn_name);

            // Расшифровка подписи с помощью сертифика
            var cert = new X509Certificate2(str[2]);
            RSACryptoServiceProvider publicKeyProvider = (RSACryptoServiceProvider)cert.PublicKey.Key;
            Byte[] decryption_hash = publicKeyProvider.Decrypt(Encoding.ASCII.GetBytes(hash_str), true);
            string decr_hash_str = Convert.ToString(decryption_hash);

            // Считываем Хэш файла
            string hash_origin = File.ReadAllText(str[1]);
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
        }
    }
}
