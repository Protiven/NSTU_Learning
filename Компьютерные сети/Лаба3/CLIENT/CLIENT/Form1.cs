using System;
using System.Threading;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CLIENT
{
    public partial class Form1 : Form
    {
        static private Socket Client;
        private string ip = null;
        private int port = 0;
        private string login = "";
        private Thread th_add;
        public Form1()
        {
            InitializeComponent();

            richTextBox1.Enabled = false;
            richTextBox2.Enabled = false;
            textBox1.Enabled = false;
            button1.Enabled = false;
            button2.Enabled = false;
        }

 

        private void button2_Click(object sender, EventArgs e) // Отправка сообщения
        {
            string message = richTextBox2.Text;
            if (message != "")
                sendMessage(message);
        }

        private void button1_Click(object sender, EventArgs e)  // Вставка логина
        {
            login = textBox1.Text;
            if (login != "" && login!= " ")
            {
                richTextBox2.Enabled = true;
                button2.Enabled = true;
                textBox1.Enabled = false;
                button1.Enabled = false;
            }
        }

        private void sendMessage(string message)
        {
            if (message != " " && message != "")
            {
                byte[] buffer = new byte[1024];
                buffer = Encoding.UTF8.GetBytes(message);
                Client.Send(buffer);
            }
        }

        private void recvMessage()
        {
            byte[] buffer = new byte[1024];
            for (int i = 0; i < buffer.Length; i++)
                buffer[i] = 0;

            for (; ; )
            {
                try
                {
                    Client.Receive(buffer);
                    string message = Encoding.UTF8.GetString(buffer);
                    int count = message.IndexOf(";;;5");
                    if (count == -1)
                        continue;

                    string clear_message = "";

                    for (int i = 0; i < count; i++)
                        clear_message += message[i];

                    this.Invoke((MethodInvoker)delegate ()
                    {
                        richTextBox1.AppendText(clear_message);
                    });
                }
                catch (Exception ex) { }
            }
        }

        private void button3_Click(object sender, EventArgs e)  // Кнопка на ввод IP - address и port
        {
            // T_b2 - ip, T_b3 - port
            if (textBox2.Text != "" && textBox3.Text != "")
            {
                ip = textBox2.Text;
                port = Convert.ToInt32(textBox3.Text);

                Client = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

                if (ip != null)
                {
                    Client.Connect(ip, port);
                    th_add = new Thread(delegate () { recvMessage(); });

                    textBox2.Enabled = false;
                    textBox3.Enabled = false;
                    button3.Enabled = false;

                    textBox1.Enabled = true;
                    button1.Enabled = true;
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            if(th_add != null)
                th_add.Abort();
            if (Client != null)
                Client.Close();
            Application.Exit();
        }
    }
}
