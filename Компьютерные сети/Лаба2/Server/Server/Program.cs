using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Collections.Generic;


class Server
{
    static void Main()
    {
        const int buff_s = 1000;
        // Создание сокета
        Socket server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp); // поиграться с AddressFamily

        try
        {
            Int32 port = 7111; // порт сервера
            string adr1 = "192.168.0.10";
            IPAddress localhost = IPAddress.Parse(adr1);
            IPEndPoint address = new IPEndPoint(localhost, port);


            server.Bind(address);

            Byte[] bytes = new Byte[buff_s];
            String data;

            while (true)
            {
                Console.Write("Waiting for a connection... ");
                server.Listen(1);
                Socket new_s = server.Accept();
                Console.WriteLine("Connected!");

                new_s.Receive(bytes);

                int i = 0;
                for (; bytes[i] != 0; )
                    i++;


                if (i > 0)
                {

                    Queue<char> q = new Queue<char>();

                    data = System.Text.Encoding.ASCII.GetString(bytes, 0, i);
                    Console.WriteLine("Received: {0}", data);

                    int supp = 0;
                    i = 0;

                    for (; i < data.Length; i++)
                        if (data[i].Equals('.') || data[i].Equals('!') || data[i].Equals('?'))
                        {
                            supp++;
                            q.Enqueue(data[i]);
                        }

                    string[] support = data.Split(new char[] { '.', '!', '?' });

                    string answer_message = "";


                    i = 0;
                    do
                    {
                        answer_message = answer_message + support[i] + " (" + adr1 + ':' + port + ')' + q.Dequeue();
                        i++;
                    } while (i != supp);

                    Console.WriteLine("Sent: {0}", answer_message);
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(answer_message);

                    new_s.Send(msg, msg.Length, SocketFlags.None);
                }
                new_s.Close();

            }
        }
        catch (SocketException expt)
        {
            Console.WriteLine("SocketException: {0}", expt);
        }
        finally
        {
            server.Dispose();
        }

        Console.WriteLine("\nHit enter to continue...");
        Console.Read();

    }
}

