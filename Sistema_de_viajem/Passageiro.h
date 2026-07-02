#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

#include <string>
#include "Cidade.h"

// Representa uma pessoa que vai viajar
class Passageiro {
private:
    std::string nome;    // Nome da pessoa
    Cidade* localAtual;  // Onde a pessoa está (fica vazio se estiver dentro de um veículo andando)

public:
    Passageiro(std::string nome, Cidade* localAtual);
    std::string getNome() const;
    Cidade* getLocalAtual() const;
    void setLocalAtual(Cidade* local);
};

#endif