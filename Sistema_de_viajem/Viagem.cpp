#include "Viagem.h"
#include <iostream>

Viagem::Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int distancia) {
    this->transporte = transporte;
    this->passageiros = passageiros;
    this->origem = origem;
    this->destino = destino;
    this->distanciaTotal = distancia;
    this->horasEmTransito = 0;
    this->distanciaPercorrida = 0;
    this->emAndamento = false;
    this->finalizada = false;
    this->proxima = nullptr;
}

void Viagem::iniciarViagem() {
    this->emAndamento = true;
    this->transporte->setLocalAtual(nullptr); 
    for (auto p : passageiros) {
        p->setLocalAtual(nullptr); 
    }
}

void Viagem::avancarHoras(int horas) {
    if (!emAndamento) return;
    
    this->horasEmTransito += horas;
    
    if (transporte->getTempoDescansoAtual() > 0) {
        transporte->setTempoDescansoAtual(transporte->getTempoDescansoAtual() - horas);
        if (transporte->getTempoDescansoAtual() < 0) {
            transporte->setTempoDescansoAtual(0);
        }
    } else {
        distanciaPercorrida += transporte->getVelocidade() * horas;
        if (distanciaPercorrida >= distanciaTotal) {
            distanciaPercorrida = distanciaTotal;
            emAndamento = false;
            finalizada = true;
            transporte->setLocalAtual(destino);
            for (auto p : passageiros) {
                p->setLocalAtual(destino);
            }
        } else {
            if (distanciaPercorrida > 0 && (distanciaPercorrida % transporte->getDistanciaEntreDescansos() == 0)) {
                transporte->setTempoDescansoAtual(transporte->getTempoDescanso());
            }
        }
    }
}

void Viagem::relatarEstado() {
    std::cout << "- Viagem de " << origem->getNome() << " para " << destino->getNome();
    if (emAndamento) std::cout << " [Em Andamento] - Percorrido: " << distanciaPercorrida << "/" << distanciaTotal << "km\n";
    else if (finalizada) std::cout << " [Finalizada]\n";
    else std::cout << " [Aguardando Inicio]\n";
}

bool Viagem::isEmAndamento() { return emAndamento; }
bool Viagem::isFinalizada() { return finalizada; }
void Viagem::setProxima(Viagem* v) { this->proxima = v; }
Viagem* Viagem::getProxima() { return proxima; }
Transporte* Viagem::getTransporte() { return transporte; }
Cidade* Viagem::getDestino() { return destino; }