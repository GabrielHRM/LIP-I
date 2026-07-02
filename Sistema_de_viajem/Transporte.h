#ifndef TRANSPORTE_H
#define TRANSPORTE_H

#include <string>
#include "Cidade.h"

// Modelo geral para criar qualquer tipo de veículo
class Transporte {
protected:
    std::string nome;               // Nome do veículo
    char tipo;                      // 'A' (aquático), 'T' (terrestre) ou 'E' (aéreo)
    int capacidade;                 // Quantas pessoas cabem
    int velocidade;                 // Velocidade em km/h
    int distancia_entre_descansos;  // Quantos km pode andar antes de parar
    int tempo_de_descanso;          // Quantas horas fica parado descansando
    int tempo_de_descanso_atual;    // Horas que ainda faltam para terminar o descanso
    int kmRodadosSemDescanso;       // Variável de fadiga do veículo
    Cidade* localAtual;             // Cidade onde está parado (fica vazio se estiver viajando)

public:
    Transporte(std::string nome, char tipo, int capacidade, int velocidade,
               int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual);
    virtual ~Transporte() = default;

    std::string getNome() const;
    char getTipo() const;
    int getCapacidade() const;
    int getVelocidade() const;
    int getDistanciaEntreDescansos() const;
    int getTempoDescanso() const;
    int getTempoDescansoAtual() const;
    void setTempoDescansoAtual(int tempo);
    Cidade* getLocalAtual() const;
    void setLocalAtual(Cidade* local);

    // <- ADICIONADO: Funções para gerenciar o cansaço global do veículo
    void registrarKmRodado(int km) { kmRodadosSemDescanso += km; }
    void zerarCansaco() { kmRodadosSemDescanso = 0; }
    int getKmSemDescanso() const { return kmRodadosSemDescanso; }

    // Diz se o veículo consegue andar naquele tipo de caminho
    virtual bool podeViajarEm(char tipoTrajeto) const = 0; 
};

// Veículo que só anda na água
class TransporteAquatico : public Transporte {
public:
    TransporteAquatico(std::string nome, int capacidade, int velocidade,
                       int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual);
    bool podeViajarEm(char tipoTrajeto) const override;
};

// Veículo que só anda na terra
class TransporteTerrestre : public Transporte {
public:
    TransporteTerrestre(std::string nome, int capacidade, int velocidade,
                        int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual);
    bool podeViajarEm(char tipoTrajeto) const override;
};

// Veículo que só anda no ar (Aviões / Helicópteros)
class TransporteAereo : public Transporte {
public:
    TransporteAereo(std::string nome, int capacidade, int velocidade,
                    int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual);
    bool podeViajarEm(char tipoTrajeto) const override;
};

#endif