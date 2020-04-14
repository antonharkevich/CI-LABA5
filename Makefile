all: build run clean
build: main.c
-t gcc -Wall -O0 -g3 -DDEBUG -errors -std=c89 main.c -o programm

run: programm.exe
-t ./programm.exe

clean:
-t rm -rf *.o programm
