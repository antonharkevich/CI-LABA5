all: build
build: main
  gcc -Wall -O0 -g3 -DDEBUG -std=c89 main.c -o programm

run: programm.exe
  ./programm.exe

clean:  
  rm -rf *.o programm
