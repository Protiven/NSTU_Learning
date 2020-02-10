﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Net.Sockets;
using System.Net;

namespace SMTP_C_SHARP
{
    class Program
    {
        static void Main(string[] args)
        {
            var rec = new byte[512];

            Console.WriteLine("Программа для работы протокола SMTP через сокеты. Чтобы выйти из программы нажмите ESC. \nВведите hostname: ");
            string hostname = Console.ReadLine();
            Console.WriteLine("Введите port: ");
            int port = Convert.ToInt32(Console.ReadLine());
            var client = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                client.Connect(hostname, port);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
                Console.ReadKey();
                Environment.Exit(0);
            }
            client.Receive(rec);

            string str_rec = Encoding.UTF8.GetString(rec);
            Console.WriteLine("Server: " + str_rec);

            string str_req;

            while (true)
            {
                try
                {
                    Console.Write("Client: ");

                    str_req = Console.ReadLine() + " \r\n";
                    client.Send(Encoding.UTF8.GetBytes(str_req));

                    client.Receive(rec);
                    str_rec = Encoding.UTF8.GetString(rec);
                    Console.WriteLine("Server: " + str_rec);
                }
                catch (Exception ex)
                {
                    Environment.Exit(0);
                }
                
            }

        }
    }
}
