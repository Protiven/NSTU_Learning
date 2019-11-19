.386
.MODEL FLAT

.DATA
BUF DD ?; буфер под ввод
RES DD ?; буфер под вывод
POS DD ?; номер, начиная с которого выводим
LEN DD ?; длина отрезка
DOUT DD ?
.code
_FUNC PROC
PUSH EBP; необходимо сохранить в стеке первоначальное значение регистра EBP 
MOV EBP, ESP


; разложили все параметры процедуры по буферам
MOV EAX, [EBP+8]
MOV BUF, EAX
MOV EAX, [EBP+12]
MOV RES, EAX
MOV EAX, [EBP + 16]
MOV LEN,EAX 
MOV EAX, [EBP + 20]
MOV POS, EAX 
DEC POS



; Сдвиг на позицию pos
MOV esi, BUF
ADD esi, POS; В esi ПО ИДЕЕ ЛЕЖИТ СТРОКА, СДВИНУТАЯ НА POS



cld 
mov edi, res
mov ecx, len
rep movsb
xor eax, eax
mov [edi], eax

POP EBP
RET
_FUNC ENDP
END
