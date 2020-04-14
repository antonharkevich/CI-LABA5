all: build
build: main\t
  gcc -Wall -O0 -g3 -DDEBUG -std=c89 main.c -o programm

run: programm.exe\t
  ./programm.exe

clean:  
  rm -rf *.o programm
