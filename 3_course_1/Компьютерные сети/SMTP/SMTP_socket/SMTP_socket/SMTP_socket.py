import sys
import socket


print("Введите имя сервера: ")
#host = input()
print("Введите порт сервера (465, 25, 587): ")
#port = int(input())

# smtp.ngs.ru      
host = "smtp.ngs.ru"  
port = 25
flag = True
       
client = socket.socket()
client.connect((host, port))

data = client.recv(1024)
print("server: %s" % data.decode())

#print("Server:%s" % data.decode('utf-8'))

str = "EHLO smtp.ngs.ru \r\n"
client.send(str.encode())
response = client.recv(1024)
print("server: %s" % response.decode())




if int(data[:3]) != 220:
    print("Ошибка подключения!")
else:
    print("Успешное подключение!")
    while flag:
        print("Введите команду!")
        str = input() + " \r\n"
        client.send(str.encode())
        response = client.recv(1024)
        print("server: %s" % response.decode())

"""       
message = 'FROM: b4@cn.ami.nstu.ru\r\n' + \
'TO: b10@cn.ami.nstu.ru\r\n' + \
'SUBJECT: Test message\r\n'
client.send(message.encode())
response = client.recv(1024)
client.send('This is a test message!\r\n'.encode())
response = client.recv(1024)
print("server: %s" % response.decode())
        
flag = False



if int(data[:3]) != 220:
print("Ошибка подключения!")
else:
print("Введите логин: ")
#login = input()
print("Введите пароль: ")
#password = input()

login = 'PM-74.nstu2017@mail.ru'
password = 'student2017'

print("CLIENT:EHLO some.host.ru CRLF")

str = "EHLO " + "some.host.ru" + " \r\n"
client.send(str.encode())

data = client.recv(1024)
print("Server:%s" % data.decode('utf-8'))

print("Использовать STARTTLS? 1 - Yes,'another' - No")
choice = int(input())
if choice == 1:
str = "STARTTLS"
str1 = str + "\r\n"
client.send(str1.encode())
rec = client.recv(1024*4).decode()
print("SERVER:%s" % rec)
if str == "STARTTLS":
if int(rec[:3]) == 220:
    a = 0
else:
    sys.exit()
flag = True
while flag:
print("Введите команду:")
choice = input()
if choice == "QUIT":
client.close()
flag = False
elif choice == "MAIL":
print("Укажите почту получателя: ")
receiver = input()
print("Введите заголовок письма: ")
subject = input()
print("Введите текст письма: ")
text = input()

message = "Subject: " + subject + "\n\n" + text       
           
print("CLIENT: MAIL FROM:%s CRLF" % login)

str = "MAIL FROM:" + login + " \r\n"
client.send(str.encode())
data = client.recv(1024)
print("Server: %s" % data.decode('utf-8'))
            
str = 'RCPT TO:' + receiver + ' \r\n'
            
print("CLIENT: RCPT TO:%s CRLF" % receiver)
client.send(str.encode())
data = client.recv(1024)
print("Server: %s" % data.decode('utf-8'))

                 
print("CLIENT: DATA CRLF")
client.send('DATA \r\n'.encode())
data = client.recv(1024)
print("Server: %s" % data.decode('utf-8'))
       
print("CLIENT: %s CRLF" % message)
client.send(message.encode())
       
print("CLIENT: ")
client.send(''.encode())
       
print("CLIENT: This is a test message! CRLF")
client.send('This is a test message!\r\n'.encode())

print("CLIENT: . CRLF")
client.send('.\r\n'.encode())
data = client.recv(1024)
print("Server: %s" % data.decode('utf-8'))

print("connect to %s through %s port" % (host, port))
       
print("CLIENT: EHLO localhost CRLF")
client.send('EHLO localhost \r\n'.encode())
data = client.recv(1024)
print("Server: %s" % data.decode('utf-8'))
       
print("CLIENT: MAIL FROM:b4@cn.ami.nstu.ru CRLF")
client.send('MAIL FROM:b4@cn.ami.nstu.ru \r\n'.encode())
data = client.recv(1024)
print("Server: %s" % data.decode('utf-8'))
       
print("CLIENT: RCPT TO:b10@cn.ami.nstu.ru CRLF")
client.send('RCPT TO:b10@cn.ami.nstu.ru \r\n'.encode())
data = client.recv(1024)
print("Server: %s" % data.decode('utf-8'))
       
print("CLIENT: DATA CRLF")
client.send('DATA \r\n'.encode())
data = client.recv(1024)
print("Server: %s" % data.decode('utf-8'))
       
message = 'FROM: b4@cn.ami.nstu.ru\r\n' + \
       	'TO: b10@cn.ami.nstu.ru\r\n' + \
       	'SUBJECT: Test message\r\n'
       
print("CLIENT: %s CRLF" % message)
client.send(message.encode())
       
print("CLIENT: ")
client.send(''.encode())
       
print("CLIENT: This is a test message! CRLF")
client.send('This is a test message!\r\n'.encode())
       
print("CLIENT: . CRLF")
client.send('.\r\n'.encode())
data = client.recv(1024)
print("Server: %s" % data.decode('utf-8'))
       
print("CLIENT: QUIT CRLF")
client.send('QUIT\r\n'.encode())
data = client.recv(1024)
print("Server: %s" % data.decode('utf-8'))
"""       