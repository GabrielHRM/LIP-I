#include "Viagem.h"
#include <iostream>
#include <algorithm>

// Configura os dados da viagem antes de dar a partida
Viagem::Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int distanciaTotal) :
    transporte(transporte), passageiros(passageiros), origem(origem), destino(destino),
    proxima(nullptr), horasEmTransito(0), emAndamento(false),
    distanciaTotal(distanciaTotal), distanciaPercorrida(0), kmDesdeUltimoDescanso(0), destinoFinalCadeia(destino)
{
}

// Apaga as viagens seguintes quando esta for destruída
Viagem::~Viagem()
{
    if (proxima) {
        delete proxima;
    }
}

// Dá a partida: tira o veículo e as pessoas das cidades e coloca-os em movimento
void Viagem::iniciarViagem()
{
    emAndamento = true;
    transporte->setLocalAtual(nullptr); // Fica vazio significando "em trânsito"
    for (auto* p : passageiros) {
        p->setLocalAtual(nullptr);
    }
}

void Viagem::setProxima(Viagem* prox)
{ 
    proxima = prox; 
}

Viagem* Viagem::getProxima() const
{ 
    return proxima; 
}

Transporte* Viagem::getTransporte() const
{ 
    return transporte; 
}

std::vector<Passageiro*> Viagem::getPassageiros() const
{ 
    return passageiros; 
}

Cidade* Viagem::getOrigem() const
{ 
    return origem; 
}

Cidade* Viagem::getDestino() const
{ 
    return destino; 
}

bool Viagem::isEmAndamento() const
{ 
    return emAndamento; 
}

int Viagem::getDistanciaPercorrida() const
{ 
    return distanciaPercorrida; 
}

int Viagem::getDistanciaTotal() const
{ 
    return distanciaTotal; 
}

void Viagem::setDestinoFinalCadeia(Cidade* destFinal)
{ 
    destinoFinalCadeia = destFinal; 
}

// Faz o tempo passar e move o veículo hora por hora
void Viagem::avancarHoras(int horas)
{
    if (!emAndamento) {
        return;
    }

    for (int h = 0; h < horas; ++h) {
        if (!emAndamento) {
            break;
        }
        horasEmTransito++;

        // Se o veículo estiver descansando, ele apenas espera o tempo passar
        if (transporte->getTempoDescansoAtual() > 0) {
            transporte->setTempoDescansoAtual(transporte->getTempoDescansoAtual() - 1);
            continue; 
        }

        int vel = transporte->getVelocidade();
        int descEntre = transporte->getDistanciaEntreDescansos();
        int andadoNestaHora = 0;

        // Anda os quilômetros permitidos dentro desta 1 hora
        while (andadoNestaHora < vel && distanciaPercorrida < distanciaTotal) {
            distanciaPercorrida++;
            andadoNestaHora++;
            kmDesdeUltimoDescanso++;

            // Se atingir o limite do motorista, ativa o descanso obrigatório e para de andar
            if (kmDesdeUltimoDescanso >= descEntre && distanciaPercorrida < distanciaTotal) {
                transporte->setTempoDescansoAtual(transporte->getTempoDescanso());
                kmDesdeUltimoDescanso = 0;
                break; 
            }
        }

        // Se chegou ao fim do trecho atual
        if (distanciaPercorrida >= distanciaTotal) {
            emAndamento = false;
            
            // Se tiver uma escala a seguir, começa ela na mesma hora
            if (proxima != nullptr) {
                proxima->iniciarViagem();
            } else {
                // Se era a última parada, coloca o veículo e as pessoas na cidade de destino final
                transporte->setLocalAtual(destinoFinalCadeia);
                for (auto* p : passageiros) {
                    p->setLocalAtual(destinoFinalCadeia);
                }
            }
        }
    }
}

// Mostra na tela a situação atual deste trecho da viagem
void Viagem::relatarEstado() const
{
    std::cout << "  Trecho: " << origem->getNome() << " -> " << destino->getNome() 
              << " | Progresso: " << distanciaPercorrida << "/" << distanciaTotal << " km"
              << " | Tempo neste trecho: " << horasEmTransito << "h";
    if (transporte->getTempoDescansoAtual() > 0) {
        std::cout << " [Parada para descanso: " << transporte->getTempoDescansoAtual() << "h restantes]";
    }
    std::cout << "\n";
}