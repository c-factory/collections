if exist a.exe erase a.exe
gcc test\test.c src\*.c -I.\include -g -Werror
if exist a.exe a.exe
