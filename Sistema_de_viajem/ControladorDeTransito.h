#ifndef CONTROLADORDETRANSITO_H
#define CONTROLADORDETRANSITO_H

#include <vector>
#include <string>
#include "Cidade.h"
#include "Trajeto.h"
#include "Transporte.h"
#include "Passageiro.h"
#include "Viagem.h"

// Gerenciador central do programa (guarda dados, procura caminhos e salva arquivos)
class ControladorDeTransito {
private:
    std::vector<Cidade*> cidades;
    std::vector<Trajeto*> trajetos;
    std::vector<Transporte*> transportes;
    std::vector<Passageiro*> passageiros;
    std::vector<Viagem*> viagens;

    // Funções auxiliares para achar cadastros originais usando apenas o nome
    Cidade* buscarCidade(const std::string& nome) const;
    Transporte* buscarTransporte(const std::string& nome) const;
    Passageiro* buscarPassageiro(const std::string& nome) const;
    
    // Procura o caminho conectando os trajetos válidos para o veículo escolhido
    bool encontrarCaminho(Cidade* atual, Cidade* destino, Transporte* t, 
                          std::vector<Cidade*>& visitados, std::vector<Trajeto*>& caminhoAtual, 
                          std::vector<Trajeto*>& melhorCaminho) const;

public:
    ControladorDeTransito() = default;
    ~ControladorDeTransito();

    // Funções para cadastrar novos elementos no sistema
    void cadastrarCidade(std::string nome);
    void cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo, int distancia);
    void cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade,
                             int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual);
    void cadastrarPassageiro(std::string nome, std::string localAtual);
    
    // Funções para fazer o sistema rodar
    void iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros,
                       std::string nomeOrigem, std::string nomeDestino);
    void avancarHoras(int horas);
    void relatarEstado() const;

    // Funções para salvar e carregar dados em arquivos de texto
    void salvarDados() const;
    void carregarDados();
};

#endif