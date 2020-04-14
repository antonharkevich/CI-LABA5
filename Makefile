all: build
build : main\tgcc -Wall -O0 -g3 -DDEBUG -std=c89 main.c -o programm

run: programm.exe\t./programm.exe

clean : \trm -rf *.o programm
