using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;

namespace Client
{
    class TCP_Client
    {
        static void Main(string[] args)
        {
            try
            {
                Int32 port = 7111;//порт сервера
                string message = "CALC * 10 6\n";//строка, которую пошлем серверу


                string localhost = "192.168.0.100"; 

                TcpClient client = new TcpClient(localhost, port);

                //преобразуем строчку в массив байт
                Byte[] data = System.Text.Encoding.ASCII.GetBytes(message);

                // вводим поток stream для чтения и записи через установленное соединение                
                NetworkStream stream = client.GetStream();

                // посылаем сообщение серверу 
                stream.Write(data, 0, data.Length);

                Console.WriteLine("Sent: {0}", message);//печатаем то, что отправили

                // буффер для приема сообщений
                data = new Byte[1000];

                // строка для приема сообщений сервера
                String responseData;

                // получаем сообщение от сервера
                Int32 bytes = stream.Read(data, 0, data.Length);
                responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
                //печатаем то, что получили
                Console.WriteLine("Received: {0}", responseData);

                // закрываем соединение
                stream.Close();
                client.Close();
            }
            catch (ArgumentNullException expt)
            {
                Console.WriteLine("ArgumentNullException: {0}", expt);
            }
            catch (SocketException expt)
            {
                Console.WriteLine("SocketException: {0}", expt);
            }

            Console.WriteLine("\n Press Enter to continue...");
            Console.Read();
        }
    }
}

