all: build
build: main.c
gcc -Wall -O0 -g3 -DDEBUG -std=c89 main.c -o programm.exe

run: programm.exe
./programm.exe

clean:
rm -rf *.o programm
