all: build
build: main
<tab>gcc -Wall -O0 -g3 -DDEBUG -std=c89 main.c -o programm

run: programm.exe
<tab>./programm.exe

clean:
<tab>rm -rf *.o programm
