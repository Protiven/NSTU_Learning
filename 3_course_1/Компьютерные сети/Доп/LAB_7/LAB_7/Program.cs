using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using OpenPop.Mime;
using OpenPop.Pop3;
using OpenPop.Common;

using Message = OpenPop.Mime.Message;

namespace LAB_7
{
    class Program
    {
        static void Main(string[] args)
        {
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // Используем using чтобы соединение автоматически закрывалось
            using (OpenPop.Pop3.Pop3Client client = new Pop3Client())
            {
                // Подключение к серверу
                client.Connect("pop.mail.ru", 995, true);

                // Аутентификация (проверка логина и пароля)
                client.Authenticate("ящик@mail.ru", "password", AuthenticationMethod.UsernameAndPassword);

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
                    for (int i = messageCount; i > 0; i--)
                    {
                        allMessages.Add(client.GetMessage(i));

                        Message message = client.GetMessage(i);

                        string subject = message.Headers.Subject; //заголовок
                        string date = message.Headers.Date.ToString(); //Дата/Время
                        string from = message.Headers.From.ToString(); //от кого
                        string body = "";

                        // ищем первую плейнтекст версию в сообщении
                        MessagePart mpPlain = message.FindFirstPlainTextVersion();

                        if (mpPlain != null)
                        {
                            Encoding enc = mpPlain.BodyEncoding;
                            body = enc.GetString(mpPlain.Body); //получаем текст сообщения
                        }

                        //ListViewItem mes = new ListViewItem(new string[] { subject, date, from, body });
                        //listView.Items.Add(mes);
                    }

                    //Ищем во всех письмах все вложения
                    for (int i = 0; i < messageCount; i++)
                    {
                        Message msg = allMessages[i];
                        var att = msg.FindAllAttachments();
                        foreach (var ado in att)
                        {
                            //сохраняем все найденные в письмах вложения
                            ado.Save(new System.IO.FileInfo(System.IO.Path.Combine("c:\\folder", ado.FileName)));
                        }

                        //если в письме были вложения, удаляем данное письмо
                        if (att.Count > 0) client.DeleteMessage(messageCount - i);
                    }
                }
            }
        }
    }
}


/*
 * using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using OpenPop.Mime;
using OpenPop.Pop3;
using OpenPop.Common;

using Message = OpenPop.Mime.Message;

namespace ReadMail
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // Используем using чтобы соединение автоматически закрывалось
            using (OpenPop.Pop3.Pop3Client client = new Pop3Client())
            {
                // Подключение к серверу
                client.Connect("pop.mail.ru", 995, true);

                // Аутентификация (проверка логина и пароля)
                client.Authenticate("ящик@mail.ru", "password", AuthenticationMethod.UsernameAndPassword);

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
                    for (int i = messageCount; i > 0; i--)
                    {
                        allMessages.Add(client.GetMessage(i));

                        Message message = client.GetMessage(i);

                        string subject = message.Headers.Subject; //заголовок
                        string date = message.Headers.Date.ToString(); //Дата/Время
                        string from = message.Headers.From.ToString(); //от кого
                        string body = "";

                        // ищем первую плейнтекст версию в сообщении
                        MessagePart mpPlain = message.FindFirstPlainTextVersion();

                        if (mpPlain != null)
                        {
                            Encoding enc = mpPlain.BodyEncoding;
                            body = enc.GetString(mpPlain.Body); //получаем текст сообщения
                        }

                        ListViewItem mes = new ListViewItem(new string[] { subject, date, from, body });
                        //listView.Items.Add(mes);
                    }

                    //Ищем во всех письмах все вложения
                    for (int i = 0; i < messageCount; i++)
                    {
                        Message msg = allMessages[i];
                        var att = msg.FindAllAttachments();
                        foreach (var ado in att)
                        {
                            //сохраняем все найденные в письмах вложения
                            ado.Save(new System.IO.FileInfo(System.IO.Path.Combine("c:\\folder", ado.FileName)));
                        }

                        //если в письме были вложения, удаляем данное письмо
                        if (att.Count > 0) client.DeleteMessage(messageCount - i);
                    }
                }
            }

        }
    }
}
 */
