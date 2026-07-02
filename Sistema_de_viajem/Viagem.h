#ifndef VIAGEM_H
#define VIAGEM_H

#include <vector>
#include "Transporte.h"
#include "Passageiro.h"
#include "Cidade.h"

// Controla o movimento do veículo e das pessoas entre duas cidades vizinhas
class Viagem {
private:
    Transporte* transporte;              // Veículo usado
    std::vector<Passageiro*> passageiros; // Lista de passageiros a bordo
    Cidade* origem;                      // Cidade de partida deste trecho
    Cidade* destino;                     // Cidade de chegada deste trecho
    Viagem* proxima;                     // Próxima parada da viagem (se houver escalas)
    int horasEmTransito;                 // Quantas horas já se passaram neste trecho
    bool emAndamento;                    // Indica se o veículo está na estrada agora

    int distanciaTotal;                  // Tamanho do trecho em km
    int distanciaPercorrida;             // Quantos km já foram andados
    int kmDesdeUltimoDescanso;           // Contador para saber quando o motorista precisa parar
    Cidade* destinoFinalCadeia;          // O destino final de toda a viagem (mesmo com escalas)

public:
    Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int distanciaTotal);
    ~Viagem();

    void iniciarViagem();
    void avancarHoras(int horas);
    void relatarEstado() const;
    bool isEmAndamento() const;

    void setProxima(Viagem* prox);
    Viagem* getProxima() const;
    Transporte* getTransporte() const;
    std::vector<Passageiro*> getPassageiros() const;
    Cidade* getOrigem() const;
    Cidade* getDestino() const;
    int getDistanciaPercorrida() const;
    int getDistanciaTotal() const;
    void setDestinoFinalCadeia(Cidade* destFinal);
};

#endif