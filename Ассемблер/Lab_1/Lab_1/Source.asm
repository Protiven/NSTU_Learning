.486
.model flat, stdcall
option casemap: none
 
include /masm32/include/windows.inc
include /masm32/include/user32.inc
include /masm32/include/kernel32.inc
 
includelib /masm32/lib/user32.lib
includelib /masm32/lib/kernel32.lib
 
include /masm32/macros/macros.asm 
uselib masm32, comctl32, ws2_32 
 
.data
 
.code
start:
 
call GetCommandLine ; результат будет помещен в eax
 
push 0
push chr$("Command Line")
push eax ; текст для вывода берем из eax
push 0
call MessageBox
 
push 0
call ExitProcess
 
end start