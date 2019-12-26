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

        static private void function_pop3()
        {
            // Используем using чтобы соединение автоматически закрывалось
            using (OpenPop.Pop3.Pop3Client client = new Pop3Client())
            {
                // Подключение к серверу
                client.Connect("cn.ami.nstu.ru", 995, true);

                // Аутентификация (проверка логина и пароля)
                client.Authenticate("b4@cn.ami.nstu.ru", "Aayu2uon", AuthenticationMethod.UsernameAndPassword);

                if (client.Connected)
                {
                    // Получение количества сообщений в почтовом ящике
                    int messageCount = client.GetMessageCount();

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

                        string subject = message.Headers.Subject + '\n' ; //заголовок

                        var help_val = message.FindFirstPlainTextVersion();
                        string text_mes = "";
                        if (help_val!=null)
                            text_mes = help_val.GetBodyAsText() + '\n';
                        string date = message.Headers.Date.ToString() + '\n'; //Дата/Время
                        string from = message.Headers.From.ToString() + '\n'; //от кого

                        string str = "---------------------------------------------------------------------------------------------";
                        string text = "Сообщение №: " + add_val + '\n' + subject + text_mes + date + from + str;
                        add_val++;

                        Console.WriteLine(text);
                    }
                }
            }
        }

        static void Main(string[] args)
        {
            function_pop3();
            Console.WriteLine("Программа выполнена успешно!");
            Console.ReadKey();
        }
    }
}
