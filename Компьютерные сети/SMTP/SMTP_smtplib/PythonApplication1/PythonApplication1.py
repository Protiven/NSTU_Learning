import smtplib
       
# Ввод данных о сервере
print("Введите имя сервера: ")
host = input()
print("Введите порт сервера (465, 25, 587): ")
port = int(input())


if port==465: 
    SMTP = smtplib.SMTP_SSL(host, port)
elif port == 25:
    SMTP = smtplib.SMTP(host, port)
elif port == 587:
    SMTP = smtplib.SMTP(host, port)
    SMTP.starttls()

print("Введите логин: ")
login = input()
print("Введите пароль: ")
password = input()

SMTP.login(login, password)

flag = True
while flag:
    print("1 - Выход, 2 - Отправить сообщение")
    choice = int(input())
    if choice == 1:
        SMTP.close()
        flag = False
    elif choice == 2:
        print("Укажите  почту получателя: ")
        reciver = input()
        print("Введите заголовок письма: ")
        subject = input()
        print("Введите текст письма: ")
        text = input()

        message = "Subject: " + subject + "\n\n" + text       
        SMTP.sendmail(login, reciver, message)
    else:
        flag = True
