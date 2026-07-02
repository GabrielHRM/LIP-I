#ifndef TRAJETO_H
#define TRAJETO_H

#include "Cidade.h"

// Define uma estrada ou rota que liga duas cidades
class Trajeto {
private:
    Cidade* origem;   // Cidade de onde parte
    Cidade* destino;  // Cidade onde chega
    char tipo;        // 'A' para água, 'T' para terra ou 'E' para aéreo
    int distancia;    // Distância em quilômetros

public:
    Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia);
    Cidade* getOrigem() const;
    Cidade* getDestino() const;
    char getTipo() const;
    int getDistancia() const;
};

#endif