.386
.MODEL FLAT

.DATA
BUF DD ?; ����� ��� ����
RES DD ?; ����� ��� �����
POS DD ?; �����, ������� � �������� �������
LEN DD ?; ����� �������
DOUT DD ?
.code
_FUNC PROC
PUSH EBP; ���������� ��������� � ����� �������������� �������� �������� EBP 
MOV EBP, ESP


; ��������� ��� ��������� ��������� �� �������
MOV EAX, [EBP+8]
MOV BUF, EAX
MOV EAX, [EBP+12]
MOV RES, EAX
MOV EAX, [EBP + 16]
MOV LEN,EAX 
MOV EAX, [EBP + 20]
MOV POS, EAX 
DEC POS



; ����� �� ������� pos
MOV esi, BUF
ADD esi, POS; � esi �� ���� ����� ������, ��������� �� POS



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
