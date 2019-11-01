#pragma comment(lib,"Ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

SOCKET Connect;
SOCKET* Connections;
SOCKET Listen;

int ClientCount = 0;

void SendMessageToClient(int ID)
{
   char* buffer = new char[1024];
   for (;; Sleep(75))
   {
      memset(buffer, 0, sizeof(buffer));
      recv(Connections[ID], buffer, 1024, NULL);
      int key = 0;
      
      for (key; buffer[key] != ';'; key++)
         ;


      if (buffer[0]!= 0)
      {
         for (int i = 0; i < key; i++)
            printf_s("%c", buffer[i]);
         std::cout << std::endl;

         for (int i = 0; i <= ClientCount; i++)
            send(Connections[i], buffer, key, NULL);
      }
   }
   delete(buffer);
}

int main()
{
   setlocale(LC_ALL, "rus");
   WSADATA data;
   WORD version = MAKEWORD(2, 2);
   int res = WSAStartup(version, &data);
   
   if (res != 0)
      return 0;

   struct addrinfo hints;
   struct addrinfo* result;

   Connections = new SOCKET[64];

   ZeroMemory(&hints, sizeof(hints));
   hints.ai_family = AF_INET;
   hints.ai_flags = AI_PASSIVE;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_protocol = IPPROTO_TCP;

   getaddrinfo(NULL, "7111", &hints, &result);

   Listen = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
   bind(Listen, result->ai_addr, result->ai_addrlen);
   listen(Listen, SOMAXCONN);

   freeaddrinfo(result);

   std::cout << "Start server..." << std::endl;
   char m_connect[] = "Connect...";

   for (;; Sleep(75))
   {
      if (ClientCount < SOMAXCONN)
      {
         if (Connect = accept(Listen, NULL, NULL))
         {
            printf("Client connected...\n");
            Connections[ClientCount] = Connect;
            send(Connections[ClientCount], m_connect, strlen(m_connect), NULL);
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SendMessageToClient, (LPVOID)(ClientCount), NULL, NULL);
            ClientCount++;
         }
      }
      else
         closesocket(accept(Listen, NULL, NULL));
   }

   return 1;
}

