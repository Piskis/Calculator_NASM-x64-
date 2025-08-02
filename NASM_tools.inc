;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                                                                             ;;;
;;;  Here are all commands in this file:                                        ;;;
;;;  print (takes two parameters); name_input (takes two parameters);           ;;;
;;;  exit (dont takes parameters); create_file (takes two parameters);          ;;;
;;;  string_to_line (takes parameters in the RAX(number), and RDI(string))      ;;;
;;;                                                                             ;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ; WARNING: You MUST define `fd resq 1` in .bss or this will segfault.          ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; To work with this file you can use nasm command < %include "NASM_tools.inc" >   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



; ======== PRINT ========= ;

%macro print 2             ; msg, len
mov rax, 1
mov rdi, 1
mov rsi, %1
mov rdx, %2
syscall
%endmacro

; ====== NAME INPUT ====== ;

%macro name_input 2        ; input, buffer
mov rax, 0
mov rdi, 0
mov rsi, %1
mov rdx, %2
syscall
%endmacro

; ===== CREATE FILE ====== ;

; ask for Filename and buffers!!!
; like:

; section .bss
; filename resb 256
; msg resb 256
; fd resq 1


%macro create_file 2
  call %%Kill_Newline
  mov rax, 2
  mov rdi, %1
  mov rsi, 0x241
  mov rdx, 0o644
  syscall

  mov [fd], rax

  call %%find_le
  mov rdx, rcx

  mov rax, 1
  mov rdi, [fd]
  mov rsi, %2
  mov rdx, rcx
  syscall

  mov rax, 60
  mov rdi, [fd]
  syscall

; remove \n in filename
%%Kill_Newline:
  mov rdi, %1
%%kloop:
  cmp byte [rdi], 0
  je %%kdone
  cmp byte [rdi], 10
  je %%kreplace
  inc rdi
  jmp %%kloop

%%kreplace:
  mov byte [rdi], 0
%%kdone:
  ret

%%find_le:
  mov rdi, %2
  xor rcx, rcx

%%floop:
  cmp byte [rdi + rcx], 0
  je %%fdone
  cmp byte [rdi + rcx], 10
  je %%fdone
  inc rcx
  jmp %%floop

%%fdone:
  ret
%endmacro

; ======= num_to_string ========= ;

; string to RDI num in RAX (!)

%macro num_to_string 0
    push rbx
    xor rax, rax
    xor rcx, rcx
    xor rbx, rbx

%%skip_spaces:
    mov cl, byte [rdi]
    cmp cl, ' '
    jne %%check_sign
    inc rdi
    jmp %%skip_spaces

%%check_sign:
    mov cl, byte [rdi]
    cmp cl, '-'
    jne %%check_plus
    mov bl, 1
    inc rdi
    jmp %%parse_digits

%%check_plus:
    cmp cl, '+'
    jne %%parse_digits
    inc rdi

%%parse_digits:
    mov cl, byte [rdi]
    cmp cl, 0
    je %%done

    cmp cl, '0'
    jb %%done
    cmp cl, '9'
    ja %%done

    imul rax, rax, 10
    sub cl, '0'
    movzx rcx, cl
    add rax, rcx

    inc rdi
    jmp %%parse_digits

%%done:
    cmp bl, 1
    jne %%positive
    neg rax

%%positive:
    pop rbx
    ret

%endmacro

; num in RAX  string in RSI  RCX = base (!)

%macro itoa 0

%%itoa:
    add rsi, 256          ; конец буфера 256 (может быть изменено на 3)
    mov byte [rsi], 0     ; null terminator

%%itoa_loop:
    dec rsi
    xor rdx, rdx
    div rcx
    add dl, '0'
    mov [rsi], dl
    test rax, rax
    jnz %%itoa_loop
    ret

%endmacro

%macro exit 0
mov rax, 60
xor rdi, rdi
syscall
%endmacro
