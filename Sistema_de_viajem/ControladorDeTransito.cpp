#include "ControladorDeTransito.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

// Destrutor que limpa a memória de tudo que foi criado no sistema
ControladorDeTransito::~ControladorDeTransito()
{
    for (auto* c : cidades) delete c;
    for (auto* t : trajetos) delete t;
    for (auto* tr : transportes) delete tr;
    for (auto* p : passageiros) delete p;
    for (auto* v : viagens) delete v;
}

/* ------------------ BUSCAS INTERNAS ------------------ */

Cidade* ControladorDeTransito::buscarCidade(const std::string& nome) const
{
    for (auto* c : cidades) {
        if (c->getNome() == nome) return c;
    }
    return nullptr;
}

Transporte* ControladorDeTransito::buscarTransporte(const std::string& nome) const
{
    for (auto* t : transportes) {
        if (t->getNome() == nome) return t;
    }
    return nullptr;
}

Passageiro* ControladorDeTransito::buscarPassageiro(const std::string& nome) const
{
    for (auto* p : passageiros) {
        if (p->getNome() == nome) return p;
    }
    return nullptr;
}

/* ------------------ CADASTROS ------------------ */

void ControladorDeTransito::cadastrarCidade(std::string nome)
{
    if (buscarCidade(nome)) {
        return; // Não deixa cadastrar duas cidades iguais
    }
    cidades.push_back(new Cidade(nome));
}

void ControladorDeTransito::cadastrarTrajeto(std::string nomeOrigem, std::string nomeDestino, char tipo, int distancia)
{
    Cidade* o = buscarCidade(nomeOrigem);
    Cidade* d = buscarCidade(nomeDestino);
    if (o && d) {
        trajetos.push_back(new Trajeto(o, d, tipo, distancia));
    }
}

void ControladorDeTransito::cadastrarTransporte(std::string nome, char tipo, int capacidade, int velocidade,
                                                 int distancia_entre_descansos, int tempo_de_descanso, std::string localAtual)
{
    if (buscarTransporte(nome)) {
        return;
    }
    Cidade* local = buscarCidade(localAtual);
    if (!local) {
        return;
    }
    
    Transporte* t = nullptr;
    if (tipo == 'A') {
        t = new TransporteAquatico(nome, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, local);
    } else if (tipo == 'T') {
        t = new TransporteTerrestre(nome, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, local);
    } else if (tipo == 'E') {
        // Agora aceita a criação de transportes aéreos
        t = new TransporteAereo(nome, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, local);
    }
    
    if (t) {
        transportes.push_back(t);
    }
}

void ControladorDeTransito::cadastrarPassageiro(std::string nome, std::string localAtual)
{
    if (buscarPassageiro(nome)) {
        return;
    }
    Cidade* local = buscarCidade(localAtual);
    if (local) {
        passageiros.push_back(new Passageiro(nome, local));
    }
}

// Testa caminhos válidos ligando as cidades até achar o que tem menos paradas/escalas
bool ControladorDeTransito::encontrarCaminho(Cidade* Schuyler, Cidade* destino, Transporte* t, 
                                              std::vector<Cidade*>& visitados, std::vector<Trajeto*>& caminhoAtual, 
                                              std::vector<Trajeto*>& melhorCaminho) const
{
    if (Schuyler == destino) {
        if (melhorCaminho.empty() || caminhoAtual.size() < melhorCaminho.size()) {
            melhorCaminho = caminhoAtual;
        }
        return true;
    }

    visitados.push_back(Schuyler);
    bool encontrou = false;

    for (auto* trajeto : trajetos) {
        // Só entra no caminho se o tipo do veículo bater com o tipo da pista (água, terra ou ar)
        if (trajeto->getOrigem() == Schuyler && t->podeViajarEm(trajeto->getTipo())) {
            if (std::find(visitados.begin(), visitados.end(), trajeto->getDestino()) == visitados.end()) {
                caminhoAtual.push_back(trajeto);
                if (encontrarCaminho(trajeto->getDestino(), destino, t, visitados, caminhoAtual, melhorCaminho)) {
                    encontrou = true;
                }
                caminhoAtual.pop_back(); 
            }
        }
    }
    visitados.pop_back();
    return encontrou;
}

// Prepara e inicia uma nova viagem ligando a partida ao destino final
void ControladorDeTransito::iniciarViagem(std::string nomeTransporte, std::vector<std::string> nomesPassageiros,
                                           std::string nomeOrigem, std::string nomeDestino)
{
    Transporte* t = buscarTransporte(nomeTransporte);
    Cidade* o = buscarCidade(nomeOrigem);
    Cidade* d = buscarCidade(nomeDestino);

    if (!t || !o || !d || t->getLocalAtual() != o) {
        std::cout << "Erro: Iniciacao abortada. Transporte indisponivel ou local incorreto.\n";
        return;
    }

    if (nomesPassageiros.size() > static_cast<size_t>(t->getCapacidade())) {
        std::cout << "Erro: Lotaçao maxima excedida.\n";
        return;
    }

    std::vector<Passageiro*> passEscolhidos;
    for (const auto& nome : nomesPassageiros) {
        Passageiro* p = buscarPassageiro(nome);
        if (p && p->getLocalAtual() == o) {
            passEscolhidos.push_back(p);
        }
    }

    std::vector<Cidade*> visitados;
    std::vector<Trajeto*> caminhoAtual;
    std::vector<Trajeto*> melhorCaminho;

    if (!encontrarCaminho(o, d, t, visitados, caminhoAtual, melhorCaminho)) {
        std::cout << "Erro: Nao foi localizado nenhum trajeto viavel para esta categoria de veiculo.\n";
        return;
    }

    Viagem* primeiraViagem = nullptr;
    Viagem* ultimaViagem = nullptr;

    // Liga as etapas/escalas da viagem umas nas outras como uma corrente
    for (size_t i = 0; i < melhorCaminho.size(); ++i) {
        Trajeto* traj = melhorCaminho[i];
        Viagem* novaViagem = new Viagem(t, passEscolhidos, traj->getOrigem(), traj->getDestino(), traj->getDistancia());
        novaViagem->setDestinoFinalCadeia(d);

        if (i == 0) {
            primeiraViagem = novaViagem;
        } else {
            ultimaViagem->setProxima(novaViagem);
        }
        
        ultimaViagem = novaViagem;
        viagens.push_back(novaViagem);
    }

    if (primeiraViagem) {
        primeiraViagem->iniciarViagem(); // Dá a partida no primeiro trecho
        std::cout << "Sucesso: Viagem agendada e em andamento via " << melhorCaminho.size() << " trecho(s)!\n";
    }
}

// Faz o tempo andar apenas nas viagens que estão rodando na estrada no momento
void ControladorDeTransito::avancarHoras(int horas)
{
    for (auto* v : viagens) {
        if (v->isEmAndamento()) {
            v->avancarHoras(horas);
        }
    }
}

// Imprime o relatório geral de onde estão os veículos, as pessoas e as viagens ativas
void ControladorDeTransito::relatarEstado() const
{
    std::cout << "\n==================================================\n";
    std::cout << "            STATUS CONTROLADOR DE TRANSITO          \n";
    std::cout << "==================================================\n";

    std::cout << "\n--- Localizaçao de Passageiros ---\n";
    for (auto* p : passageiros) {
        if (p->getLocalAtual()) {
            std::cout << " * Pessoas: " << p->getNome() << " esta em [Cidade: " << p->getLocalAtual()->getNome() << "]\n";
        } else {
            for (auto* v : viagens) {
                if (v->isEmAndamento()) {
                    auto pList = v->getPassageiros();
                    if (std::find(pList.begin(), pList.end(), p) != pList.end()) {
                        std::cout << " * Pessoas: " << p->getNome() << " [EM TRÂNSITO] na rota " 
                                  << v->getOrigem()->getNome() << " -> " << v->getDestino()->getNome() 
                                  << " atraves do veiculo: " << v->getTransporte()->getNome() << "\n";
                        break;
                    }
                }
            }
        }
    }

    std::cout << "\n--- Localizaçao de Veiculos ---\n";
    for (auto* t : transportes) {
        if (t->getLocalAtual()) {
            std::cout << " * Transporte: " << t->getNome() << " estacionado em -> " << t->getLocalAtual()->getNome() << "\n";
        } else {
            std::cout << " * Transporte: " << t->getNome() << " operando [EM TRANSITO]\n";
        }
    }

    std::cout << "\n--- Viagens Ativas (Em Andamento) ---\n";
    bool possuiAtivas = false;
    for (auto* v : viagens) {
        if (v->isEmAndamento()) {
            v->relatarEstado();
            possuiAtivas = true;
        }
    }
    if (!possuiAtivas) {
        std::cout << " Nenhuma viagem ativa registrada no momento.\n";
    }

    // Calcula quais cidades receberam mais visitas até agora e monta o ranking
    std::cout << "\n--- Cidades Mais Visitadas (Ranking) ---\n";
    std::map<std::string, int> ranking;
    for (auto* c : cidades) {
        ranking[c->getNome()] = 0;
    }
    for (auto* v : viagens) {
        if (v->getDistanciaPercorrida() > 0) {
            ranking[v->getDestino()->getNome()]++;
        }
    }
    std::vector<std::pair<std::string, int>> ordenado(ranking.begin(), ranking.end());
    std::sort(ordenado.begin(), ordenado.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    for (const auto& par : ordenado) {
        std::cout << " -> Cidade: " << par.first << " recebeu " << par.second << " visitas.\n";
    }
    std::cout << "==================================================\n\n";
}

/* ------------------ GRAVAÇÃO E LEITURA DE ARQUIVOS ------------------ */

void ControladorDeTransito::salvarDados() const
{
    std::ofstream fCidades("db_cidades.txt");
    for (auto* c : cidades) {
        fCidades << c->getNome() << "\n";
    }

    std::ofstream fTrajetos("db_trajetos.txt");
    for (auto* t : trajetos) {
        fTrajetos << t->getOrigem()->getNome() << ";" << t->getDestino()->getNome() << ";" 
                  << t->getTipo() << ";" << t->getDistancia() << "\n";
    }

    std::ofstream fTransportes("db_transportes.txt");
    for (auto* t : transportes) {
        fTransportes << t->getNome() << ";" << t->getTipo() << ";" << t->getCapacidade() << ";"
                     << t->getVelocidade() << ";" << t->getDistanciaEntreDescansos() << ";"
                     << t->getTempoDescanso() << ";" 
                     << (t->getLocalAtual() ? t->getLocalAtual()->getNome() : "EM_TRANSITO") << "\n";
    }

    std::ofstream fPassageiros("db_passageiros.txt");
    for (auto* p : passageiros) {
        fPassageiros << p->getNome() << ";" 
                     << (p->getLocalAtual() ? p->getLocalAtual()->getNome() : "EM_TRANSITO") << "\n";
    }
    std::cout << "Dados persistidos com sucesso.\n";
}

void ControladorDeTransito::carregarDados()
{
    std::string linha;
    
    std::ifstream fCidades("db_cidades.txt");
    if (fCidades.is_open()) {
        while (std::getline(fCidades, linha)) {
            if (!linha.empty()) {
                cadastrarCidade(linha);
            }
        }
    }

    std::ifstream fTrajetos("db_trajetos.txt");
    if (fTrajetos.is_open()) {
        while (std::getline(fTrajetos, linha)) {
            if (linha.empty()) {
                continue;
            }
            std::stringstream ss(linha);
            std::string orig, dest; char tipo; int dist;
            if (std::getline(ss, orig, ';') && std::getline(ss, dest, ';') && (ss >> tipo) && (ss.ignore() >> dist)) {
                cadastrarTrajeto(orig, dest, tipo, dist);
            }
        }
    }

    std::ifstream fTransportes("db_transportes.txt");
    if (fTransportes.is_open()) {
        while (std::getline(fTransportes, linha)) {
            if (linha.empty()) {
                continue;
            }
            std::stringstream ss(linha);
            std::string nome, local; char tipo; int cap, vel, distD, tempD;
            if (std::getline(ss, nome, ';') && (ss >> tipo) && ss.ignore() && (ss >> cap) && ss.ignore() 
                && (ss >> vel) && ss.ignore() && (ss >> distD) && ss.ignore() && (ss >> tempD) 
                && ss.ignore() && std::getline(ss, local)) {
                if (local == "EM_TRANSITO" && !cidades.empty()) {
                    local = cidades[0]->getNome();
                }
                cadastrarTransporte(nome, tipo, cap, vel, distD, tempD, local);
            }
        }
    }

    std::ifstream fPassageiros("db_passageiros.txt");
    if (fPassageiros.is_open()) {
        while (std::getline(fPassageiros, linha)) {
            if (linha.empty()) {
                continue;
            }
            std::stringstream ss(linha);
            std::string nome, local;
            if (std::getline(ss, nome, ';') && std::getline(ss, local)) {
                if (local == "EM_TRANSITO" && !cidades.empty()) {
                    local = cidades[0]->getNome();
                }
                cadastrarPassageiro(nome, local);
            }
        }
    }
}