using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


// Необходимо установить OpenPop.NET
using OpenPop.Mime;
using OpenPop.Pop3;
using OpenPop.Common;

using Message = OpenPop.Mime.Message;


namespace test_dop_pop3
{
    class Program
    {
        static private void get_all_message(Pop3Client client)
        {
            // Получение количества сообщений в почтовом ящике
            int messageCount = client.GetMessageCount();

            //client.

            // Выделяем память под список сообщений. Мы хотим получить все сообщения
            List<Message> allMessages = new List<Message>(messageCount);

            // Сообщения нумеруются от 1 до messageCount включительно
            // Другим языком нумерация начинается с единицы
            // Большинство серверов присваивают новым сообщениям наибольший номер (чем меньше номер тем старее сообщение)
            // Т.к. цикл начинается с messageCount, то последние сообщения должны попасть в начало списка
            int add_val = 1;
            for (int i = messageCount; i > 0; i--)
            {
                allMessages.Add(client.GetMessage(i));

                Message message = client.GetMessage(i);

                string subject = message.Headers.Subject + '\n'; //заголовок

                var help_val = message.FindFirstPlainTextVersion();
                string text_mes = "";
                if (help_val != null)
                    text_mes = help_val.GetBodyAsText() + '\n';
                string date = message.Headers.Date.ToString() + '\n'; //Дата/Время
                string from = message.Headers.From.ToString() + '\n'; //от кого

                string str = "---------------------------------------------------------------------------------------------";
                string text = "Сообщение №: " + add_val + '\n' + subject + text_mes + date + from + str;
                add_val++;

                Console.WriteLine(text);
            }
        }
        static private void function_pop3()
        {
            // Используем using чтобы соединение автоматически закрывалось
            using (OpenPop.Pop3.Pop3Client client = new Pop3Client())
            {
                Console.Write("Введите имя сервера: ");
                string name_server = /*"pop.mail.ru";/*/ Console.ReadLine();

                Console.Write("Введите порт (110 или 995): ");
                var port = /*995;/*/ Convert.ToInt32(Console.ReadLine());
                bool usessl = false;
               
                if (port == 995)
                    usessl = true;
                else
                    if (port == 110)
                    usessl = false;
                else
                    Environment.Exit(0);
             
                Console.Write("Введите почту: ");
                string login = /*"PM-74.nstu2017@mail.ru";/*/ Console.ReadLine();

                Console.Write("Введите пароль: ");
                string password = /*"student2017";*/ Console.ReadLine();


                // Подключение к серверу
                client.Connect(name_server, port, usessl);
                
                // Аутентификация (проверка логина и пароля)
                client.Authenticate(login, password, AuthenticationMethod.UsernameAndPassword);
       

                if (client.Connected)
                {
                    var flag = true;
                    for (; flag; )
                    {
                        Console.WriteLine("\nВыберите действие:");
                        Console.WriteLine("1 - выход");              // Работает
                        Console.WriteLine("2 - проверить текущее состояние почты");       // Работает
                        Console.WriteLine("3 - вывод списка сообщений");      // Работает
                        Console.WriteLine("4 - вывод всех сообщений");   // Работает
                        Console.WriteLine("5 - прочитать сообщение номер");    // Работает
                        Console.WriteLine("6 - удалить сообщение номер");     // Работает
                        var choice = Convert.ToInt32(Console.ReadLine());

                        switch (choice)
                        {
                            case 1:  
                                flag = false;
                                client.Disconnect();
                                break;
                            case 2:
                                var count = client.GetMessageCount();
                                var mem = client.GetMessageSizes();
                                int sum = 0;
                                foreach (var mem1 in mem)
                                    sum += mem1;
                                Console.WriteLine("Всего {0} сообщений с общим размером {1} байт", count, sum);
                                break;
                            case 3:
                                int messageCount = client.GetMessageCount();
                                List<Message> allMessages = new List<Message>(messageCount);

                                int s = 1;
                                for (int i = messageCount; i > 0; i--)
                                {
                                    Message message = client.GetMessage(i);
                                    allMessages.Add(message);
                                    Console.WriteLine("{0}        {1} {2} {3}", i, message.Headers.Subject, message.Headers.From, message.Headers.DateSent);
                                    s++;
                                }
                                break;
                            case 4:
                                get_all_message(client);
                                break;
                            case 5: 
                                Console.WriteLine("Номер сообщения.");
                                var ch = Convert.ToInt32(Console.ReadLine());
                                var bytes = client.GetMessage(ch);

                                string subject = bytes.Headers.Subject + '\n'; //заголовок

                                var help_val = bytes.FindFirstPlainTextVersion();
                                string text_mes = "";
                                if (help_val != null)
                                    text_mes = help_val.GetBodyAsText() + '\n';
                                string date = bytes.Headers.Date.ToString() + '\n'; //Дата/Время
                                string from = bytes.Headers.From.ToString() + '\n'; //от кого

                                string text = subject + text_mes + date + from;

                                Console.WriteLine(text);
                                break;
                            case 6:
                                Console.WriteLine("Номер сообщения.");
                                var ch1 = Convert.ToInt32(Console.ReadLine());
                                client.DeleteMessage(ch1);
                                break;
                            default:
                                Console.WriteLine("Ошибка выбора!");
                                break;
                        }
                    }
                }
                else
                    Console.WriteLine("ошибка аутентификации! Повторите снова!");
            }
        }

        static void Main(string[] args)
        {
            function_pop3();
            Console.WriteLine("Программа выполнена успешно!");
        }
    }
}
