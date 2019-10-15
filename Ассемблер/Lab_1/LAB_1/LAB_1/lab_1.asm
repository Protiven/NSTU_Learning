.386
.MODEL FLAT, STDCALL

EXTERN  GetStdHandle@4: PROC
EXTERN  WriteConsoleA@20: PROC
EXTERN  CharToOemA@8: PROC
EXTERN  ExitProcess@4: PROC; функция выхода из программы
EXTERN  lstrlenA@4: PROC; функция определения длины строки
EXTERN  ReadConsoleA@20: PROC;


.DATA; сегмент данных
CONSTa DD ? ; константа с основанием СС (16)
CONSTb DD ? ; константа с 10 
STRN DB "Введите строку с первым числом(не менее 3 символов): ",13,10,0; 
STRN2 DB "Введите строку со вторым числом(не менее 3 символов): ",13,10,0; 
STRN3 DB "Некорректно введены данные: требуется ввести число от трех знаков",13,10,0; 
STRN4 DB "Некорректно введены данные: требуется ввести строку из чисел",13,10,0;
FMT DB "Сумма двух чисел: ", 0; 
FMT2 DB "Сумма двух чисел: -", 0; 
DIN DD ?; дескриптор ввода
COUNTER DB ?; СЧЕТЧИК
DOUT DD ?; дескриптор вывода
NUMA DD ?; первое число
NUMB DD ?; второе число 
NUMC DD ?; буфер для вывода
LENS DD ?; переменная для количества выведенных символов
FLAG DB ?; 
FLAGM DB ?; 
BUF  DB 200 dup (?); 


.CODE; сегмент кода 
MAIN PROC ; 

; получим дескриптор ввода
PUSH -10
CALL GetStdHandle@4
MOV DIN, EAX 

; получим дескриптор вывода
PUSH -11
CALL GetStdHandle@4
MOV DOUT, EAX 



;ПЕРЕКОДИРОВКА 1 СТРОКИ
MOV  EAX, OFFSET STRN;	адрес первой строки -> в регистр ЕАХ
PUSH EAX; параметры функции помещаются в стек командой PUSH
PUSH EAX
CALL CharToOemA@8; ( параметры: что перекодировать/ куда поместить результат)

;ПЕРЕКОДИРОВКА 2 СТРОКИ
MOV  EAX, OFFSET STRN2;	адрес второй строки -> в регистр ЕАХ
PUSH EAX; 
PUSH EAX
CALL CharToOemA@8; ( параметры: что перекодировать/ куда поместить результат)

;ПЕРЕКОДИРОВКА 3 СТРОКИ(ДЛЯ 1 ТИПА ОШИБКИ ВВОДА)
MOV  EAX, OFFSET STRN3;	адрес первой строки -> в регистр ЕАХ
PUSH EAX; параметры функции помещаются в стек командой PUSH
PUSH EAX
CALL CharToOemA@8; ( параметры: что перекодировать/ куда поместить результат)

;ПЕРЕКОДИРОВКА 4 СТРОКИ(ДЛЯ 1 ТИПА ОШИБКИ ВВОДА)
MOV  EAX, OFFSET STRN4;	адрес первой строки -> в регистр ЕАХ
PUSH EAX; параметры функции помещаются в стек командой PUSH
PUSH EAX
CALL CharToOemA@8; ( параметры: что перекодировать/ куда поместить результат)

LOOP NUM1

ERROR1:
; определим длину строки STRN3
PUSH OFFSET STRN3; в стек помещается адрес строки
CALL lstrlenA@4; длина в EAX

; вызов функции WriteConsoleA для вывода строки STRN3
PUSH 0; в стек помещается 5-й параметр
PUSH OFFSET LENS; 4-й параметр
PUSH EAX; 3-й параметр
PUSH OFFSET STRN3; 2-й параметр
PUSH DOUT; 1-й параметр
CALL WriteConsoleA@20
CMP FLAG, 1
JB NUM1
JMP NUM2

ERROR2:
; определим длину строки STRN4
PUSH OFFSET STRN4; в стек помещается адрес строки
CALL lstrlenA@4; длина в EAX

; вызов функции WriteConsoleA для вывода строки STRN3
PUSH 0; в стек помещается 5-й параметр
PUSH OFFSET LENS; 4-й параметр
PUSH EAX; 3-й параметр
PUSH OFFSET STRN4; 2-й параметр
PUSH DOUT; 1-й параметр
CALL WriteConsoleA@20
CMP FLAG, 1
JB NUM1
JMP NUM2

NUM1:
MOV COUNTER, 0
; определим длину строки STRN
PUSH OFFSET STRN; в стек помещается адрес строки
CALL lstrlenA@4; длина в EAX

; вызов функции WriteConsoleA для вывода строки STRN
PUSH 0; в стек помещается 5-й параметр
PUSH OFFSET LENS; 4-й параметр
PUSH EAX; 3-й параметр
PUSH OFFSET STRN; 2-й параметр
PUSH DOUT; 1-й параметр
CALL WriteConsoleA@20

;ввод строки с первым числом
PUSH 0;
PUSH OFFSET LENS;
PUSH 200;
PUSH OFFSET BUF;
PUSH DIN;
CALL ReadConsoleA@20 ; 

DEC LENS; ПО ОТЛАДЧИКУ ПОУЛЧАЕТСЯ, ЧТО В LENS ЛЕЖИТ ЧИСЛО НА 2 БОЛЬШЕ, ЧЕМ РЕАЛЬНАЯ ДЛИНА
DEC LENS; ВОЗМОЖНО ВОЗВРАТ КОРЕТКИ И ПЕРЕХОД НА НОВУЮ СТРОКУ ???

;преобразование 1 числа 
XOR EDI, EDI
XOR ESI, ESI
MOV DI, 10; основание системы счисления
XOR ECX, ECX;
MOV ECX, LENS; счетчик цикла (строка имеет длину LENS)
MOV ESI, OFFSET BUF; начало строки хранится в переменной BUF
XOR EBX, EBX; обнулить регистр BX командой XOR, 
; выполняющей побитно операцию «исключающее или»
XOR EAX, EAX; обнулить регистр AX
; 
MOV BL, [ESI]; поместить символ из введенной строки в регистр
CMP BL, 45
JE MIN1
INC ECX
LOOP CONVERT
MIN1:
ADD FLAGM,1
INC ESI
LOOP CONVERT
CONVERT: 	; метка начала тела цикла
	MOV BL, [ESI]; поместить символ из введенной строки в регистр 
	; BL, используя косвенную адресацию
	CMP BL, 48 ; СРАВНИВАЕМ С КОДОМ НУЛЯ
	JAE NEXT1 
NEXT1:
	CMP BL, 57
	JA ERROR2	
	SUB BL, '0'; вычесть из введенного символа код нуля
	MUL DI; умножить значение AX на 10, результат – в AX
	ADD EAX, EBX; добавить к полученному в AX числу новую цифру	
	ADD COUNTER, 1
	INC ESI; перейти на следующий символ строки
LOOP CONVERT; перейти на следующую итерацию цикла
MOV NUMA, EAX

CMP COUNTER, 3
JB ERROR1

MOV FLAG, 1



;КОНЕЦ РАБОТЫ С 1 ЧИСЛОМ
;РАБОТА СО В 2 ЧИСЛОМ 






NUM2:
MOV COUNTER, 0
; определим длину строки STRN2
PUSH OFFSET STRN2; в стек помещается адрес строки
CALL lstrlenA@4; длина в EAX

; вызов функции WriteConsoleA для вывода строки STRN2
PUSH 0; в стек помещается 5-й параметр
PUSH OFFSET LENS; 4-й параметр
PUSH EAX; 3-й параметр
PUSH OFFSET STRN2; 2-й параметр
PUSH DOUT; 1-й параметр
CALL WriteConsoleA@20

;ввод строки с 2 числом
PUSH 0;
PUSH OFFSET LENS;
PUSH 200;
PUSH OFFSET BUF;
PUSH DIN;
CALL ReadConsoleA@20 ; 

DEC LENS; ПО ОТЛАДЧИКУ ПОУЛЧАЕТСЯ, ЧТО В LENS ЛЕЖИТ ЧИСЛО НА 2 БОЛЬШЕ, ЧЕМ РЕАЛЬНАЯ ДЛИНА
DEC LENS; ВОЗМОЖНО ВОЗВРАТ КОРЕТКИ И ПЕРЕХОД НА НОВУЮ СТРОКУ???

;преобразование 2 числа 
XOR DI, DI
MOV DI, 10; основание системы счисления
XOR ECX, ECX;
MOV ECX, LENS; счетчик цикла (строка имеет длину LENS)
MOV ESI, OFFSET BUF; начало строки хранится в переменной BUF
XOR EBX, EBX; обнулить регистр BX командой XOR, 
; выполняющей побитно операцию «исключающее или»
XOR EAX, EAX; обнулить регистр AX
MOV BL, [ESI]; поместить символ из введенной строки в регистр
CMP BL, 45
JE MIN2
INC ECX
LOOP CONVERT2
MIN2:
ADD FLAGM,2
INC ESI
LOOP CONVERT2
CONVERT2: 	; метка начала тела цикла
	MOV BL, [ESI]; поместить символ из введенной строки в регистр 
	; BL, используя косвенную адресацию
	CMP BL, 48 ; СРАВНИВАЕМ С КОДОМ НУЛЯ
	JAE NEXT2 
NEXT2:
	CMP BL, 57
	JA ERROR2 
	SUB BL, '0'; вычесть из введенного символа код нуля
	MUL DI; умножить значение AX на 10, результат – в AX
	ADD EAX, EBX; добавить к полученному в AX числу новую цифру	
	ADD COUNTER, 1
	INC ESI; перейти на следующий символ строки
LOOP CONVERT2; перейти на следующую итерацию цикла
MOV NUMB, EAX

CMP COUNTER, 3
JB ERROR1



; КОНЕЦ РАБОТЫ СО 2 ЧИСЛОМ

 CMP FLAGM, 1
 JAE SUBab

 SUMM:
;СУММА ДВУХ ЧИСЕЛ
XOR EAX, EAX
XOR EBX, EBX
MOV EAX, NUMA
MOV EBX, NUMB
ADD EAX, EBX
MOV NUMA, EAX
CMP FLAGM, 3
JE SUMOUTPUTM
LOOP SUMOUTPUT

SUBab:
CMP FLAGM, 3
JE SUMM
XOR EAX, EAX
XOR EBX, EBX
MOV EAX, NUMA
MOV EBX, NUMB
CMP EBX,EAX
JAE SUBab2
SUB EAX, EBX
MOV NUMA, EAX
CMP FLAGM, 2
JE SUMOUTPUT
LOOP SUMOUTPUTM


SUBab2:
SUB EBX,EAX  
MOV NUMA, EBX
CMP FLAGM, 2
JE SUMOUTPUTM
LOOP SUMOUTPUT

SUMOUTPUTM:
; ВЫВОД FMT2
XOR EAX,EAX
MOV  EAX, OFFSET FMT2;	адрес FMT2 строки -> в регистр ЕАХ
PUSH EAX; параметры функции помещаются в стек командой PUSH
PUSH EAX
CALL CharToOemA@8; ( параметры: что перекодировать/ куда поместить результат)
 
; определим длину строки FMT2
PUSH OFFSET FMT2; в стек помещается адрес строки
CALL lstrlenA@4; длина в EAX

; вызов функции WriteConsoleA для вывода строки FMT
PUSH 0; в стек помещается 5-й параметр
PUSH OFFSET LENS; 4-й параметр
PUSH EAX; 3-й параметр
PUSH OFFSET FMT2; 2-й параметр
PUSH DOUT; 1-й параметр
CALL WriteConsoleA@20
LOOP FINALMARK

SUMOUTPUT:
;ВЫВОД РЕЗУЛЬТАТА
; ВЫВОД FMT
XOR EAX,EAX
MOV  EAX, OFFSET FMT;	адрес FMT строки -> в регистр ЕАХ
PUSH EAX; параметры функции помещаются в стек командой PUSH
PUSH EAX
CALL CharToOemA@8; ( параметры: что перекодировать/ куда поместить результат)
 
; определим длину строки FMT
PUSH OFFSET FMT; в стек помещается адрес строки
CALL lstrlenA@4; длина в EAX

; вызов функции WriteConsoleA для вывода строки FMT
PUSH 0; в стек помещается 5-й параметр
PUSH OFFSET LENS; 4-й параметр
PUSH EAX; 3-й параметр
PUSH OFFSET FMT; 2-й параметр
PUSH DOUT; 1-й параметр
CALL WriteConsoleA@20

FINALMARK:
;пробный перевод в 16-ю
XOR EAX,EAX; обнуляю регистр
XOR EDI, EDI; обнуляю регистр ( далее будет считать кол-во итераций)
XOR EBX, EBX; обнуляю регистр
MOV CONSTa, 16; загрузка основания СС 
MOV CONSTb, 10 ; загрузка 10 
MOV EAX, NUMA; в ЕАХ положили сумму 
CONVERT3:		
	XOR EDX, EDX ; обнуление
		CMP EAX, 0; ПОКА НАШЕ ЧИСЛО БОЛЬШЕ 0
JE RESULT; если оно меньше - то на выход
	IDIV CONSTa;  поделили ЕАХ(наше число) на основание СС, остаток  - в EDX, целая часть - в ЕАХ
		CMP	EDX, CONSTb
JB CONVERT4
		ADD EDX, 'A'; добавить код A к остатку
		SUB EDX, 10 ; ВЫЧЕСТЬ 10
		PUSH EDX; складываем перекодированный остаток в стек	
		ADD EDI, 1; увеличиваем счётчик на 1
		LOOP CONVERT3;	
CONVERT4:
		ADD EDX, '0' ; добавить код нуля к остатку
		PUSH EDX; складываем перекодированный остаток в стек	
		ADD EDI, 1; увеличиваем счётчик на 1
		LOOP CONVERT3 

RESULT:
; вывод строки
XOR ESI,ESI
CONVERTF:
CMP ESI, EDI ;пока меньше кол-ва итераций прошлого цикла(меньше кол-ва символов)
JAE	EXITF
	POP NUMC ; достать из стека последний символ и положить его в буфер
	push 0 ; в стек помещается 5-й параметр
	push offset lens ; 4-й параметр
	push 1; 3-й параметр
	push  OFFSET NUMC ; 2-й параметр
	push dout ; 1-й параметр
	call WriteConsoleA@20
	ADD ESI,1 
JMP CONVERTF

EXITF:
PUSH 0; параметр: код выхода
CALL ExitProcess@4
MAIN ENDP
END MAIN

