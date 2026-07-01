#include "Passageiro.h"

Passageiro::Passageiro(std::string nome, Cidade* localAtual) {
    this->nome = nome;
    this->localAtual = localAtual;
}

std::string Passageiro::getNome() {
    return this->nome;
}

Cidade* Passageiro::getLocalAtual() {
    return this->localAtual;
}

void Passageiro::setLocalAtual(Cidade* local) {
    this->localAtual = local;
}