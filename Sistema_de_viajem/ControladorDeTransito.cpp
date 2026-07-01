#include "ControladorDeTransito.h"
#include <iostream>
#include <fstream>
#include <sstream>

ControladorDeTransito::~ControladorDeTransito() {
    for (auto c : cidades) delete c;
    for (auto t : trajetos) delete t;
    for (auto tr : transportes) delete tr;
    for (auto p : passageiros) delete p;
    for (auto v : viagens) delete v;
}

Cidade* ControladorDeTransito::buscarCidade(std::string nome) {
    for (auto c : cidades) if (c->getNome() == nome) return c;
    return nullptr;
}

Transporte* ControladorDeTransito::buscarTransporte(std::string nome) {
    for (auto t : transportes) if (t->getNome() == nome) return t;
    return nullptr;
}

Passageiro* ControladorDeTransito::buscarPassageiro(std::string nome) {
    for (auto p : passageiros) if (p->getNome() == nome) return p;
    return nullptr;
}

Trajeto* ControladorDeTransito::buscarTrajetoDireto(Cidade* origem, Cidade* destino) {
    for (auto t : trajetos) {
        if (t->getOrigem() == origem && t->getDestino() == destino) return t;
    }
    return nullptr;
}

void ControladorDeTransito::cadastrarCidade(std::string nome) {
    if (!buscarCidade(nome)) cidades.push_back(new Cidade(nome));
}

void ControladorDeTransito::cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo, int distancia) {
    Cidade* origem = buscarCidade(nomeOrigem);
    Cidade* destino = buscarCidade(nomeDestino);
    if (origem && destino) trajetos.push_back(new Trajeto(origem, destino, tipo, distancia));
}

void ControladorDeTransito::cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade, 
                                                int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual) {
    Cidade* local = buscarCidade(localAtual);
    if (local) transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, local));
}

void ControladorDeTransito::cadastrarPassageiro(std::string nome, std::string localAtual) {
    Cidade* local = buscarCidade(localAtual);
    if (local) passageiros.push_back(new Passageiro(nome, local));
}

void ControladorDeTransito::iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros, 
                                          std::string nomeOrigem, std::string nomeDestino) {
    Transporte* transporte = buscarTransporte(nomeTransporte);
    Cidade* origem = buscarCidade(nomeOrigem);
    Cidade* destino = buscarCidade(nomeDestino);
    Trajeto* trajeto = buscarTrajetoDireto(origem, destino);

    if (!transporte || !origem || !destino || !trajeto) {
        std::cout << "Erro: Conexao ou dados invalidos. Verifique se o trajeto existe.\n";
        return;
    }
    
    if (transporte->getLocalAtual() != origem) {
        std::cout << "Erro: Transporte nao esta na cidade de origem.\n";
        return;
    }
    
    // Verifica compatibilidade entre Transporte e Trajeto 
    if (transporte->getTipo() != trajeto->getTipo()) {
        std::cout << "Erro: O tipo do transporte e incompativel com o tipo do trajeto.\n";
        return;
    }

    std::vector<Passageiro*> passLista;
    for (const auto& np : nomesPassageiros) {
        Passageiro* p = buscarPassageiro(np);
        if (p && p->getLocalAtual() == origem) passLista.push_back(p);
    }

    Viagem* novaViagem = new Viagem(transporte, passLista, origem, destino, trajeto->getDistancia());
    novaViagem->iniciarViagem();
    viagens.push_back(novaViagem);
    std::cout << "Viagem registrada e iniciada com sucesso.\n";
}

void ControladorDeTransito::avancarHoras(int horas) {
    for (auto v : viagens) {
        if (v->isEmAndamento()) v->avancarHoras(horas);
    }
    std::cout << "O tempo avancou " << horas << " horas.\n";
}

void ControladorDeTransito::relatarEstado() {
    std::cout << "\n=== STATUS DO SISTEMA ===\n";
    std::cout << "Passageiros:\n";
    for(auto p : passageiros) {
        std::cout << "- " << p->getNome() << " | Local: " << (p->getLocalAtual() ? p->getLocalAtual()->getNome() : "Em transito") << "\n";
    }
    std::cout << "\nTransportes:\n";
    for(auto t : transportes) {
        std::cout << "- " << t->getNome() << " | Tipo: " << t->getTipo() << " | Local: " << (t->getLocalAtual() ? t->getLocalAtual()->getNome() : "Em transito") << "\n";
    }
    std::cout << "\nViagens:\n";
    if (viagens.empty()) std::cout << "Nenhuma viagem registrada.\n";
    for (auto v : viagens) v->relatarEstado();
    std::cout << "=========================\n";
}

void ControladorDeTransito::salvarDados() {
    std::ofstream arquivo("dados_viagens.txt");
    if (!arquivo.is_open()) return;

    arquivo << "CIDADES\n";
    for (auto c : cidades) arquivo << c->getNome() << "\n";
    
    arquivo << "TRAJETOS\n";
    for (auto t : trajetos) {
        arquivo << t->getOrigem()->getNome() << ";" << t->getDestino()->getNome() << ";" 
                << t->getTipo() << ";" << t->getDistancia() << "\n";
    }

    arquivo << "PASSAGEIROS\n";
    for (auto p : passageiros) {
        if(p->getLocalAtual()) arquivo << p->getNome() << ";" << p->getLocalAtual()->getNome() << "\n";
    }

    arquivo.close();
}

void ControladorDeTransito::carregarDados() {
    std::ifstream arquivo("dados_viagens.txt");
    if (!arquivo.is_open()) return;

    std::string linha, secao;
    while (std::getline(arquivo, linha)) {
        if (linha == "CIDADES" || linha == "TRAJETOS" || linha == "PASSAGEIROS") {
            secao = linha;
            continue;
        }

        if (linha.empty()) continue;

        if (secao == "CIDADES") {
            cadastrarCidade(linha);
        } 
        else if (secao == "TRAJETOS") {
            std::stringstream ss(linha);
            std::string origem, destino, tipoStr, distStr;
            std::getline(ss, origem, ';');
            std::getline(ss, destino, ';');
            std::getline(ss, tipoStr, ';');
            std::getline(ss, distStr, ';');
            cadastrarTrajeto(origem, destino, tipoStr[0], std::stoi(distStr));
        }
        else if (secao == "PASSAGEIROS") {
            std::stringstream ss(linha);
            std::string nome, local;
            std::getline(ss, nome, ';');
            std::getline(ss, local, ';');
            cadastrarPassageiro(nome, local);
        }
    }
    arquivo.close();
}