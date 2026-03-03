CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm

# Pega o nome do arquivo que você quer rodar via comando
# Exemplo: mingw32-make run FILE=Questao-1
FILE = main

all:
	$(CC) $(FILE).c -o $(FILE).exe $(CFLAGS) $(LDFLAGS)

run: all
	./$(FILE).exe

clean:
	del /f *.exe