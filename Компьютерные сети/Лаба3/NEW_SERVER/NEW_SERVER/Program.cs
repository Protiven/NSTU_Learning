using System;
using System.Threading;
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
            string adr1 = "10.241.120.25";
            IPAddress localhost = IPAddress.Parse(adr1);
            IPEndPoint address = new IPEndPoint(localhost, port);


            server.Bind(address);

            Byte[] bytes = new Byte[buff_s];
            String data;

            while (true)
            {
                Console.Write("Waiting for a connection... ");
                server.Listen(5);
                Socket new_s = server.Accept();
                Console.WriteLine("Connected!");

                new_s.Receive(bytes);

                int i = 3;
                if (i > 0)
                {
                    data = System.Text.Encoding.ASCII.GetString(bytes, 0, i);
                    Console.WriteLine("Received: {0}", data);

                    string answer_message = "";
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

public class thread_client
{
    TcpClient clientSocket;
    string clNo;
 
    public void startClient(TcpClient inClientSocket, string clineNo)
    {
        this.clientSocket = inClientSocket;
        this.clNo = clineNo;
        Thread ctThread = new Thread(doChat);
        ctThread.Start();
    }

    private void doChat()
    {
        int requestCount = 0;
        byte[] bytesFrom = new byte[10025];
        string dataFromClient = null;
        Byte[] sendBytes = null;
        string serverResponse = null;
        string rCount = null;
        requestCount = 0;

        while ((true))
        {
            try
            {
                requestCount = requestCount + 1;
                NetworkStream networkStream = clientSocket.GetStream();
                networkStream.Read(bytesFrom, 0, (int)clientSocket.ReceiveBufferSize);
                dataFromClient = System.Text.Encoding.ASCII.GetString(bytesFrom);
                dataFromClient = dataFromClient.Substring(0, dataFromClient.IndexOf("$"));
                Console.WriteLine("From client - " + clNo + " : " + dataFromClient);
                rCount = Convert.ToString(requestCount);

            //    Program.broadcast(dataFromClient, clNo, true);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }
    }
}  


