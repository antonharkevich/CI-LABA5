all: build run clean
build: main.c
gcc -Wall -O0 -g3 -DDEBUG -pedantic-errors -std=c89 main.c -o programm

run: programm.exe
./programm.exe

clean:
rm -rf *.o programm
