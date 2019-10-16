using System;
using System.Threading;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Collections;
using System.Collections.Generic;


namespace ConsoleApplication1
{
    class Program
    {
        public static Hashtable clientsList = new Hashtable();

        static void Main(string[] args)
        {
            Socket server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp); // поиграться с AddressFamily
            Int32 port = 7111; // порт сервера
            string adr1 = "192.168.0.100";
            IPAddress localhost = IPAddress.Parse(adr1);
            IPEndPoint address = new IPEndPoint(localhost, port);
            server.Bind(address);
            int counter = 0;

            counter = 0;
            while ((true))
            {
                server.Listen(7);
                thr_client new_s = new thr_client(server.Accept(), clientsList);

            }

            server.Close();
            Console.WriteLine("exit");
            Console.ReadLine();
        }

    }



    public class thr_client
    {
        public int id;
        public static int counts = 0;
        Socket cl;
        public Hashtable table;
        public thr_client(Socket s, Hashtable table)
        {
            this.id = counts;
            this.cl = s;
            counts++;
            this.table = table;
            table.Add(this.id, cl);
           
            
            
            // вывод в консоль
            Console.WriteLine("Connected {0}.", s.RemoteEndPoint.ToString());
            broadcast(id, table, "Connected " + s.RemoteEndPoint.ToString() + ".\n");
            // хотим вывести всем

            
            
            Thread th1 = new Thread(start);
            th1.Start();
        }

        public void broadcast(int id, Hashtable tabl, string mess)
        {
            byte[] mess_1 = Encoding.ASCII.GetBytes(mess);


            Thread.Sleep(4000);

            foreach (DictionaryEntry Item in tabl)
            {
                if (!Item.Key.Equals(id))
                {
                    Socket s = (Socket)Item.Value;
                    s.Send(mess_1, SocketFlags.None);
                }
                else 
                {
                    Socket s = (Socket)Item.Value;
                    s.Send(Encoding.ASCII.GetBytes("YOU are " + s.RemoteEndPoint.ToString()+"\n"), SocketFlags.None);
                }
            }
        }

        private void start()
        {
            int mess_Count = 0;
            byte[] bytesFrom = new byte[10025];
            string dataFromClient = null;
/*            Byte[] sendBytes = null;
            string serverResponse = null;
            string rCount = null;
*/           
            mess_Count = 0;

            while ((true))
            {
                try
                {
                    cl.Receive(bytesFrom);
                    if (bytesFrom[0] != 0)
                    {
                        while (bytesFrom[mess_Count] != 0)
                            mess_Count++;
                        dataFromClient = System.Text.Encoding.ASCII.GetString(bytesFrom, 0, mess_Count);
                        dataFromClient += '\n';
                        // Вывели в консоль
                        Console.WriteLine("Recieved from {0}: {1}", cl.RemoteEndPoint.ToString(), dataFromClient);
                        broadcast(id, table, cl.RemoteEndPoint.ToString() + ": "+ dataFromClient);
                        // Хотим вывод на других клиентов
                        bytesFrom[0] = 0;
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine("SRABOTALO ISKLYCHENIE");
                    break;
                }
            }//end while
        }
    }

}