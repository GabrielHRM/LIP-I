#include "Transporte.h"

// Define as regras e características iniciais do veículo
Transporte::Transporte(std::string nome, char tipo, int capacidade, int velocidade,
                       int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual) :
    nome(nome), tipo(tipo), capacidade(capacidade), velocidade(velocidade),
    distancia_entre_descansos(distancia_entre_descansos), tempo_de_descanso(tempo_de_descanso),
    tempo_de_descanso_atual(0), localAtual(localAtual)
{
}

std::string Transporte::getNome() const
{ 
    return nome; 
}

char Transporte::getTipo() const
{ 
    return tipo; 
}

int Transporte::getCapacidade() const
{ 
    return capacidade; 
}

int Transporte::getVelocidade() const
{ 
    return velocidade; 
}

int Transporte::getDistanciaEntreDescansos() const
{ 
    return distancia_entre_descansos; 
}

int Transporte::getTempoDescanso() const
{ 
    return tempo_de_descanso; 
}

int Transporte::getTempoDescansoAtual() const
{ 
    return tempo_de_descanso_atual; 
}

// Atualiza o tempo que o veículo ainda precisa ficar parado descansando
void Transporte::setTempoDescansoAtual(int tempo)
{ 
    tempo_de_descanso_atual = tempo; 
}

Cidade* Transporte::getLocalAtual() const
{ 
    return localAtual; 
}

// Muda a cidade atual do veículo (muda para vazio quando ele começa a andar)
void Transporte::setLocalAtual(Cidade* local)
{ 
    localAtual = local; 
}

// Configura um veículo aquático
TransporteAquatico::TransporteAquatico(std::string nome, int capacidade, int velocidade,
                                       int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual) :
    Transporte(nome, 'A', capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, localAtual)
{
}

// Só aceita trajetos de água ('A')
bool TransporteAquatico::podeViajarEm(char tipoTrajeto) const
{ 
    return tipoTrajeto == 'A';
}

// Configura um veículo terrestre
TransporteTerrestre::TransporteTerrestre(std::string nome, int capacidade, int velocidade,
                                         int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual) :
    Transporte(nome, 'T', capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, localAtual)
{
}

// Só aceita trajetos de terra ('T')
bool TransporteTerrestre::podeViajarEm(char tipoTrajeto) const
{ 
    return tipoTrajeto == 'T';
}

// Configura um veículo aéreo
TransporteAereo::TransporteAereo(std::string nome, int capacidade, int velocidade,
                                 int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual) :
    Transporte(nome, 'E', capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, localAtual)
{
}

// Só aceita trajetos de ar ('E')
bool TransporteAereo::podeViajarEm(char tipoTrajeto) const
{ 
    return tipoTrajeto == 'E';
}