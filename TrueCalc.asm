%include "NASM_tools.inc"

section .bss
  hi resb 1
  num1 resq 16
  num2 resq 16
  answer resq 32

  question resb 64 ; line

section .data
  Hello1 db "Hello and welcome to calculator "
         db "written in assembly NASM language "
         db "by Piskis", 10, 0
  Hello1_Len equ $ - Hello1

  Hello2 db "Please, enter two numbers ", 0, 10
         db "Note: Input numbers must be "
         db "unsigned integers ", 0
         db "≤ 18446744073709551615 ", 0
         db   "(19 digits max). ", 0, 10
         db "Press Enter to start ", 10, 0
  Hello2_Len equ $ - Hello2

  First_num db "First number please:", 0, 10
  First_num_len equ $ - First_num

  Second_num db "Second number please:", 0, 10
  Second_num_len equ $ - Second_num
  Question db "Select an option", 10
           db "1 Sum, 2 Multiply, 3 Divide, 4 Substract", 10, 0

  Substract db "Substract selected", 0, 10
  Substractlen equ $ - Substract

  LenQ equ $ - Question

  newline db " ", 10, 0
  lennewline equ $ - newline

  sum db "Sum selected", 0, 10
  lensum equ $ - sum

  mult db "Multiply selected", 0, 10
  multlen equ $ - mult

  divi db "Divide selected", 0, 10
  divilen equ $ - divi

  zerodivision db "Error, zero division!", 0, 10
  zerodivisionlen equ $ - zerodivision

  minus db "-", 0
  minuslen equ $ - minus

section .text
global _start
_start:
  print Hello1, Hello1_Len
  print Hello2, Hello2_Len
  name_input hi, 1

  print First_num, First_num_len
  name_input num1, 256
  print Second_num, Second_num_len
  name_input num2, 256


  print Question, LenQ
  name_input question, 64


  mov rsi, question

.clean_loop:
  mov al, [rsi]
  cmp al, 0
  je .done_clean
  cmp al, 10
  je .replace
  inc rsi
  jmp .clean_loop

.replace:
  mov byte [rsi], 0

.done_clean:
  mov al, [question]
  cmp al, '1'
  je _sum
  cmp al, '2'
  je _second_option
  cmp al, '3'
  je _Division
  cmp al, '4'
  je _Substract

  jmp _exit

_sum:
  print sum, lensum

  lea rdi, [num1]
  call _Nnum_to_string
  mov r8, rax

  lea rdi, [num2]
  call _Nnum_to_string
  add rax, r8

  mov rbx, rax

  mov rsi, answer
  mov rax, rbx

  mov rcx, 10

  call _Nitoa

  mov rax, 1
  mov rdi, 1
  mov rdx, 256
  syscall

  jmp _print_newline

  jmp _exit

_Nnum_to_string:

  num_to_string


_Nitoa:

  itoa


_second_option:
  print mult, multlen
  lea rdi, [num1]
  call _Nnum_to_string
  mov r8, rax

  lea rdi, [num2]
  call _Nnum_to_string
  mov rdi, r8
  mul rdi
  mov rsi, answer
  mov rcx, 10

  call _Nitoa

  mov rax, 1
  mov rdi, 1
  mov rdx, 256
  syscall

  jmp _print_newline

  jmp _exit

_Division:
  print divi, divilen

  lea rdi, [num2]
  call _Nnum_to_string
  mov r8, rax
  cmp r8, 0
  je _zero_division_error

  lea rdi, [num1]
  call _Nnum_to_string
  xor rdx, rdx
  div r8                ; Результат = RAX ;

  mov rsi, answer
  mov rcx, 10

  call _Nitoa

  mov rax, 1
  mov rdi, 1
  mov rdx, 256
  syscall

  jmp _print_newline

  jmp exit

_zero_division_error:
  print zerodivision, zerodivisionlen
  jmp _exit

_Substract:
  print Substract, Substractlen

  lea rdi, [num1]
  call _Nnum_to_string
  mov r8, rax

  lea rdi, [num2]
  call _Nnum_to_string

  sub r8, rax

  cmp r8, 0
  jns _positive_result

  print minus, minuslen

  neg r8



  mov rax, r8

  mov rsi, answer
  mov rcx, 10

  call _Nitoa
  mov rax, 1
  mov rdi, 1
  mov rdx, 256
  syscall


  jmp _print_newline

  jmp _exit

_positive_result:
  mov rax, r8
  mov rcx, 10
  call _Nitoa



  mov rax, r8

  mov rsi, answer
  mov rcx, 10

  call _Nitoa
  mov rax, 1
  mov rdi, 1
  mov rdx, 256
  syscall


  jmp _print_newline

  jmp _exit

_print_newline:
  mov rax, 1
  mov rdi, 1
  mov rsi, newline
  mov rdx, lennewline
  syscall

_exit:
  exit
