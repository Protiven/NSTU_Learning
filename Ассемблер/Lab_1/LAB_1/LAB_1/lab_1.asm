.386
.MODEL FLAT, STDCALL

EXTERN  GetStdHandle@4: PROC
EXTERN  WriteConsoleA@20: PROC
EXTERN  CharToOemA@8: PROC
EXTERN  ExitProcess@4: PROC; ������� ������ �� ���������
EXTERN  lstrlenA@4: PROC; ������� ����������� ����� ������
EXTERN  ReadConsoleA@20: PROC;


.DATA; ������� ������
CONSTa DD ? ; ��������� � ���������� �� (16)
CONSTb DD ? ; ��������� � 10 
STRN DB "������� ������ � ������ ������(�� ����� 3 ��������): ",13,10,0; 
STRN2 DB "������� ������ �� ������ ������(�� ����� 3 ��������): ",13,10,0; 
STRN3 DB "����������� ������� ������: ��������� ������ ����� �� ���� ������",13,10,0; 
STRN4 DB "����������� ������� ������: ��������� ������ ������ �� �����",13,10,0;
FMT DB "����� ���� �����: ", 0; 
FMT2 DB "����� ���� �����: -", 0; 
DIN DD ?; ���������� �����
COUNTER DB ?; �������
DOUT DD ?; ���������� ������
NUMA DD ?; ������ �����
NUMB DD ?; ������ ����� 
NUMC DD ?; ����� ��� ������
LENS DD ?; ���������� ��� ���������� ���������� ��������
FLAG DB ?; 
FLAGM DB ?; 
BUF  DB 200 dup (?); 


.CODE; ������� ���� 
MAIN PROC ; 

; ������� ���������� �����
PUSH -10
CALL GetStdHandle@4
MOV DIN, EAX 

; ������� ���������� ������
PUSH -11
CALL GetStdHandle@4
MOV DOUT, EAX 



;������������� 1 ������
MOV  EAX, OFFSET STRN;	����� ������ ������ -> � ������� ���
PUSH EAX; ��������� ������� ���������� � ���� �������� PUSH
PUSH EAX
CALL CharToOemA@8; ( ���������: ��� ��������������/ ���� ��������� ���������)

;������������� 2 ������
MOV  EAX, OFFSET STRN2;	����� ������ ������ -> � ������� ���
PUSH EAX; 
PUSH EAX
CALL CharToOemA@8; ( ���������: ��� ��������������/ ���� ��������� ���������)

;������������� 3 ������(��� 1 ���� ������ �����)
MOV  EAX, OFFSET STRN3;	����� ������ ������ -> � ������� ���
PUSH EAX; ��������� ������� ���������� � ���� �������� PUSH
PUSH EAX
CALL CharToOemA@8; ( ���������: ��� ��������������/ ���� ��������� ���������)

;������������� 4 ������(��� 1 ���� ������ �����)
MOV  EAX, OFFSET STRN4;	����� ������ ������ -> � ������� ���
PUSH EAX; ��������� ������� ���������� � ���� �������� PUSH
PUSH EAX
CALL CharToOemA@8; ( ���������: ��� ��������������/ ���� ��������� ���������)

LOOP NUM1

ERROR1:
; ��������� ����� ������ STRN3
PUSH OFFSET STRN3; � ���� ���������� ����� ������
CALL lstrlenA@4; ����� � EAX

; ����� ������� WriteConsoleA ��� ������ ������ STRN3
PUSH 0; � ���� ���������� 5-� ��������
PUSH OFFSET LENS; 4-� ��������
PUSH EAX; 3-� ��������
PUSH OFFSET STRN3; 2-� ��������
PUSH DOUT; 1-� ��������
CALL WriteConsoleA@20
CMP FLAG, 1
JB NUM1
JMP NUM2

ERROR2:
; ��������� ����� ������ STRN4
PUSH OFFSET STRN4; � ���� ���������� ����� ������
CALL lstrlenA@4; ����� � EAX

; ����� ������� WriteConsoleA ��� ������ ������ STRN3
PUSH 0; � ���� ���������� 5-� ��������
PUSH OFFSET LENS; 4-� ��������
PUSH EAX; 3-� ��������
PUSH OFFSET STRN4; 2-� ��������
PUSH DOUT; 1-� ��������
CALL WriteConsoleA@20
CMP FLAG, 1
JB NUM1
JMP NUM2

NUM1:
MOV COUNTER, 0
; ��������� ����� ������ STRN
PUSH OFFSET STRN; � ���� ���������� ����� ������
CALL lstrlenA@4; ����� � EAX

; ����� ������� WriteConsoleA ��� ������ ������ STRN
PUSH 0; � ���� ���������� 5-� ��������
PUSH OFFSET LENS; 4-� ��������
PUSH EAX; 3-� ��������
PUSH OFFSET STRN; 2-� ��������
PUSH DOUT; 1-� ��������
CALL WriteConsoleA@20

;���� ������ � ������ ������
PUSH 0;
PUSH OFFSET LENS;
PUSH 200;
PUSH OFFSET BUF;
PUSH DIN;
CALL ReadConsoleA@20 ; 

DEC LENS; �� ��������� ����������, ��� � LENS ����� ����� �� 2 ������, ��� �������� �����
DEC LENS; �������� ������� ������� � ������� �� ����� ������ ???

;�������������� 1 ����� 
XOR EDI, EDI
XOR ESI, ESI
MOV DI, 10; ��������� ������� ���������
XOR ECX, ECX;
MOV ECX, LENS; ������� ����� (������ ����� ����� LENS)
MOV ESI, OFFSET BUF; ������ ������ �������� � ���������� BUF
XOR EBX, EBX; �������� ������� BX �������� XOR, 
; ����������� ������� �������� ������������ ���
XOR EAX, EAX; �������� ������� AX
; 
MOV BL, [ESI]; ��������� ������ �� ��������� ������ � �������
CMP BL, 45
JE MIN1
INC ECX
LOOP CONVERT
MIN1:
ADD FLAGM,1
INC ESI
LOOP CONVERT
CONVERT: 	; ����� ������ ���� �����
	MOV BL, [ESI]; ��������� ������ �� ��������� ������ � ������� 
	; BL, ��������� ��������� ���������
	CMP BL, 48 ; ���������� � ����� ����
	JAE NEXT1 
NEXT1:
	CMP BL, 57
	JA ERROR2	
	SUB BL, '0'; ������� �� ���������� ������� ��� ����
	MUL DI; �������� �������� AX �� 10, ��������� � � AX
	ADD EAX, EBX; �������� � ����������� � AX ����� ����� �����	
	ADD COUNTER, 1
	INC ESI; ������� �� ��������� ������ ������
LOOP CONVERT; ������� �� ��������� �������� �����
MOV NUMA, EAX

CMP COUNTER, 3
JB ERROR1

MOV FLAG, 1



;����� ������ � 1 ������
;������ �� � 2 ������ 






NUM2:
MOV COUNTER, 0
; ��������� ����� ������ STRN2
PUSH OFFSET STRN2; � ���� ���������� ����� ������
CALL lstrlenA@4; ����� � EAX

; ����� ������� WriteConsoleA ��� ������ ������ STRN2
PUSH 0; � ���� ���������� 5-� ��������
PUSH OFFSET LENS; 4-� ��������
PUSH EAX; 3-� ��������
PUSH OFFSET STRN2; 2-� ��������
PUSH DOUT; 1-� ��������
CALL WriteConsoleA@20

;���� ������ � 2 ������
PUSH 0;
PUSH OFFSET LENS;
PUSH 200;
PUSH OFFSET BUF;
PUSH DIN;
CALL ReadConsoleA@20 ; 

DEC LENS; �� ��������� ����������, ��� � LENS ����� ����� �� 2 ������, ��� �������� �����
DEC LENS; �������� ������� ������� � ������� �� ����� ������???

;�������������� 2 ����� 
XOR DI, DI
MOV DI, 10; ��������� ������� ���������
XOR ECX, ECX;
MOV ECX, LENS; ������� ����� (������ ����� ����� LENS)
MOV ESI, OFFSET BUF; ������ ������ �������� � ���������� BUF
XOR EBX, EBX; �������� ������� BX �������� XOR, 
; ����������� ������� �������� ������������ ���
XOR EAX, EAX; �������� ������� AX
MOV BL, [ESI]; ��������� ������ �� ��������� ������ � �������
CMP BL, 45
JE MIN2
INC ECX
LOOP CONVERT2
MIN2:
ADD FLAGM,2
INC ESI
LOOP CONVERT2
CONVERT2: 	; ����� ������ ���� �����
	MOV BL, [ESI]; ��������� ������ �� ��������� ������ � ������� 
	; BL, ��������� ��������� ���������
	CMP BL, 48 ; ���������� � ����� ����
	JAE NEXT2 
NEXT2:
	CMP BL, 57
	JA ERROR2 
	SUB BL, '0'; ������� �� ���������� ������� ��� ����
	MUL DI; �������� �������� AX �� 10, ��������� � � AX
	ADD EAX, EBX; �������� � ����������� � AX ����� ����� �����	
	ADD COUNTER, 1
	INC ESI; ������� �� ��������� ������ ������
LOOP CONVERT2; ������� �� ��������� �������� �����
MOV NUMB, EAX

CMP COUNTER, 3
JB ERROR1



; ����� ������ �� 2 ������

 CMP FLAGM, 1
 JAE SUBab

 SUMM:
;����� ���� �����
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
; ����� FMT2
XOR EAX,EAX
MOV  EAX, OFFSET FMT2;	����� FMT2 ������ -> � ������� ���
PUSH EAX; ��������� ������� ���������� � ���� �������� PUSH
PUSH EAX
CALL CharToOemA@8; ( ���������: ��� ��������������/ ���� ��������� ���������)
 
; ��������� ����� ������ FMT2
PUSH OFFSET FMT2; � ���� ���������� ����� ������
CALL lstrlenA@4; ����� � EAX

; ����� ������� WriteConsoleA ��� ������ ������ FMT
PUSH 0; � ���� ���������� 5-� ��������
PUSH OFFSET LENS; 4-� ��������
PUSH EAX; 3-� ��������
PUSH OFFSET FMT2; 2-� ��������
PUSH DOUT; 1-� ��������
CALL WriteConsoleA@20
LOOP FINALMARK

SUMOUTPUT:
;����� ����������
; ����� FMT
XOR EAX,EAX
MOV  EAX, OFFSET FMT;	����� FMT ������ -> � ������� ���
PUSH EAX; ��������� ������� ���������� � ���� �������� PUSH
PUSH EAX
CALL CharToOemA@8; ( ���������: ��� ��������������/ ���� ��������� ���������)
 
; ��������� ����� ������ FMT
PUSH OFFSET FMT; � ���� ���������� ����� ������
CALL lstrlenA@4; ����� � EAX

; ����� ������� WriteConsoleA ��� ������ ������ FMT
PUSH 0; � ���� ���������� 5-� ��������
PUSH OFFSET LENS; 4-� ��������
PUSH EAX; 3-� ��������
PUSH OFFSET FMT; 2-� ��������
PUSH DOUT; 1-� ��������
CALL WriteConsoleA@20

FINALMARK:
;������� ������� � 16-�
XOR EAX,EAX; ������� �������
XOR EDI, EDI; ������� ������� ( ����� ����� ������� ���-�� ��������)
XOR EBX, EBX; ������� �������
MOV CONSTa, 16; �������� ��������� �� 
MOV CONSTb, 10 ; �������� 10 
MOV EAX, NUMA; � ��� �������� ����� 
CONVERT3:		
	XOR EDX, EDX ; ���������
		CMP EAX, 0; ���� ���� ����� ������ 0
JE RESULT; ���� ��� ������ - �� �� �����
	IDIV CONSTa;  �������� ���(���� �����) �� ��������� ��, �������  - � EDX, ����� ����� - � ���
		CMP	EDX, CONSTb
JB CONVERT4
		ADD EDX, 'A'; �������� ��� A � �������
		SUB EDX, 10 ; ������� 10
		PUSH EDX; ���������� ���������������� ������� � ����	
		ADD EDI, 1; ����������� ������� �� 1
		LOOP CONVERT3;	
CONVERT4:
		ADD EDX, '0' ; �������� ��� ���� � �������
		PUSH EDX; ���������� ���������������� ������� � ����	
		ADD EDI, 1; ����������� ������� �� 1
		LOOP CONVERT3 

RESULT:
; ����� ������
XOR ESI,ESI
CONVERTF:
CMP ESI, EDI ;���� ������ ���-�� �������� �������� �����(������ ���-�� ��������)
JAE	EXITF
	POP NUMC ; ������� �� ����� ��������� ������ � �������� ��� � �����
	push 0 ; � ���� ���������� 5-� ��������
	push offset lens ; 4-� ��������
	push 1; 3-� ��������
	push  OFFSET NUMC ; 2-� ��������
	push dout ; 1-� ��������
	call WriteConsoleA@20
	ADD ESI,1 
JMP CONVERTF

EXITF:
PUSH 0; ��������: ��� ������
CALL ExitProcess@4
MAIN ENDP
END MAIN

