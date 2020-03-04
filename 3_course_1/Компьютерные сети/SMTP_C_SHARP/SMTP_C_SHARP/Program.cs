using System;
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
        static string Trim_bytes(byte[] rec)
        {
            int k = 0;
            for (int i = rec.Length - 1; rec[i] == 0 && i >= 0; i--)
                k = i;

            string str_rec = Encoding.UTF8.GetString(rec, 0, k);
            return str_rec;
        }

        static void Main(string[] args)
        {
            var rec = new byte[512];

            Console.WriteLine("Программа для работы протокола SMTP через сокеты. QUIT для выхода.\nВведите hostname: ");
            string hostname = Console.ReadLine();
            if (hostname == "QUIT" || hostname == "quit")
                Environment.Exit(0);
           
            Console.WriteLine("Введите port: ");
            var h = Console.ReadLine();
            if (h == "QUIT" || h == "quit")
                Environment.Exit(0);
            int port = Convert.ToInt32(h);
            

            var client = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                client.Connect(hostname, port);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
                Thread.Sleep(5000);
                Environment.Exit(0);
            }
            client.Receive(rec);

            string str_rec = Trim_bytes(rec);
            Console.WriteLine("Server: " + str_rec);

            string str_req;

            while (true)
            {
                try
                {
                    string help1;
                    Console.Write("Client: ");
                    var help = Console.ReadLine();
                    if (help == "QUIT" || help == "quit")
                        Environment.Exit(0);

                    str_req = help + " \r\n";
                    client.Send(Encoding.UTF8.GetBytes(str_req));
                    client.Receive(rec);
                    str_rec = Trim_bytes(rec);
                    Console.WriteLine("Server: " + str_rec);

                    if (help == "DATA" || help == "data")
                    {
                        do
                        {
                            Console.Write("Client: ");
                            help1 = Console.ReadLine();
                            if (help1 != ".")
                                str_req = help1 + " \r\n";
                            else
                                str_req = help1 + "\r\n";
                            client.Send(Encoding.UTF8.GetBytes(str_req));
                        } while (help1 != ".");
                        client.Receive(rec);
                        str_rec = Trim_bytes(rec);
                        Console.WriteLine("Server: " + str_rec);
                    }

                }
                catch (Exception ex)
                {
                    Environment.Exit(0);
                }
                
            }

        }
    }
}
