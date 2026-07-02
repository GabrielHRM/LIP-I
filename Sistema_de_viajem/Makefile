# Nome do programa final que será criado
TARGET = programa

# Compilador de C++
CC = g++

# Opções de compilação (ativa alertas de erros comuns)
CFLAGS = -Wall -std=c++17

# Lista com todos os arquivos de código do projeto
SRCS = main.cpp Cidade.cpp Trajeto.cpp Transporte.cpp Passageiro.cpp Viagem.cpp ControladorDeTransito.cpp

# Cria automaticamente a lista de arquivos temporários (.o)
OBJS = $(SRCS:.cpp=.o)

# Comando principal: junta tudo e cria o programa
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Comando para compilar cada arquivo de texto em código binário
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Apaga o programa e os arquivos temporários para limpar a pasta
clean:
	rm -f $(OBJS) $(TARGET)