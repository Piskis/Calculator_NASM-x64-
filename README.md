NASM x64 Calculator

I made a calculator for fairly large numbers in NASM x64.
It supports numbers up to 18446744073709551615 and includes division-by-zero checks in the division function.

This project also includes another small utility of mine — NASM_tools.inc, a set of macros to simplify working with NASM.
How to build and run:

nasm -f elf64 TrueCalc.asm
ld TrueCalc.o
./a.out

Make sure you're using a Linux distribution with nasm and ld installed.
You can also run it in a Linux environment via WSL or another emulator.



Калькулятор на NASM x64

Я написал калькулятор на NASM x64, который работает с довольно большими числами — до 18446744073709551615.
В функции деления реализована проверка деления на ноль, чтобы избежать ошибок выполнения.

Проект также включает мой вспомогательный файл — NASM_tools.inc, небольшой набор макросов для упрощения работы с NASM.
Как собрать и запустить:

nasm -f elf64 TrueCalc.asm
ld TrueCalc.o
./a.out

Убедитесь, что вы используете дистрибутив Linux с установленными nasm и ld.
Также можно использовать эмуляторы вроде WSL для запуска под Windows.
