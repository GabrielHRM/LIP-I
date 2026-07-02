#include "Passageiro.h"

// Cria o passageiro e define onde ele começa
Passageiro::Passageiro(std::string nome, Cidade* localAtual) :
    nome(nome), localAtual(localAtual)
{
}

std::string Passageiro::getNome() const
{ 
    return nome; 
}

Cidade* Passageiro::getLocalAtual() const
{ 
    return localAtual; 
}

// Atualiza onde a pessoa está no momento
void Passageiro::setLocalAtual(Cidade* local)
{ 
    localAtual = local; 
}