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
                Console.WriteLine("Введите имя сервера.");
                string name_server = Console.ReadLine();

                Console.WriteLine("Введите порт (110 или 995).");
                var port = Convert.ToInt32(Console.ReadLine());
                bool usessl = false;
               
                if (port == 995)
                    usessl = true;
                else
                    if (port == 110)
                    usessl = false;
                else
                    Environment.Exit(0);
             
                Console.WriteLine("Введите почту.");
                string login = Console.ReadLine();

                Console.WriteLine("Введите пароль.");
                string password = Console.ReadLine();

                // Подключение к серверу

                client.Connect(name_server, port, usessl);

                // Аутентификация (проверка логина и пароля)
                client.Authenticate(login, password, AuthenticationMethod.UsernameAndPassword);
                client.Connect("cn.ami.nstu.ru", 995, true);

                // Аутентификация (проверка логина и пароля)
                client.Authenticate("b4@cn.ami.nstu.ru", "Aayu2uon", AuthenticationMethod.UsernameAndPassword);

                if (client.Connected)
                {
                    var flag = true;
                    for (; flag; )
                    {
                        Console.WriteLine("Выберите действие:");
                        Console.WriteLine("1 - выход");
                        Console.WriteLine("2 - проверить текущее состояние почты");
                        Console.WriteLine("3 - вывод списка сообщений");
                        Console.WriteLine("4 - вывод всех сообщений");
                        Console.WriteLine("5 - прочитать сообщение номер");
                        Console.WriteLine("6 - проверка состояния");
                        Console.WriteLine("7 - удалить сообщение номер");
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
                            case 3: // Дичь полная 
                                var var1 = client.GetMessageUids();
                                foreach(var var2 in var1)
                                    Console.WriteLine(var2);
                                break;
                            case 4:
                                get_all_message(client);
                                break;
                            case 5: // Не робит
                                Console.WriteLine("Номер сообщения.");
                                var ch = Convert.ToInt32(Console.ReadLine());
                                var bytes = client.GetMessageAsBytes(ch);
                                Console.WriteLine(Convert.ToString(bytes));
                                break;
                            case 6:
                                client.NoOperation();
                                break;
                            case 7:
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
