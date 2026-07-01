#ifndef VIAGEM_H
#define VIAGEM_H

#include <vector>
#include "Transporte.h"
#include "Passageiro.h"
#include "Cidade.h"

class Viagem {
private:
    Transporte* transporte;
    std::vector<Passageiro*> passageiros;
    Cidade* origem;
    Cidade* destino;
    Viagem* proxima;
    int horasEmTransito;
    int distanciaPercorrida;
    int distanciaTotal;
    bool emAndamento;
    bool finalizada;
public:
    Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int distancia);
    
    void iniciarViagem();
    void avancarHoras(int horas);
    void relatarEstado();
    bool isEmAndamento();
    bool isFinalizada();
    void setProxima(Viagem* v);
    Viagem* getProxima();
    Transporte* getTransporte();
    Cidade* getDestino();
};

#endif