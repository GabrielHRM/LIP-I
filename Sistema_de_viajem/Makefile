# Compilador a ser utilizado
CXX = g++

# Flags de compilação (mostra avisos e usa o padrão C++11)
CXXFLAGS = -Wall -std=c++11

# Nome do executável final
TARGET = controlador_viagens

# Lista de todos os arquivos fonte (.cpp)
SRCS = main.cpp Cidade.cpp Passageiro.cpp Trajeto.cpp Transporte.cpp Viagem.cpp ControladorDeTransito.cpp

# Transforma a lista de .cpp em uma lista de objetos .o
OBJS = $(SRCS:.cpp=.o)

# Regra principal
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar cada .cpp em um .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados (útil para recompilar do zero)
clean:
	rm -f $(OBJS) $(TARGET)