#include <iostream>
#include <string>
#include <vector>
#include "ControladorDeTransito.h"

void limparBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

int main() {
    ControladorDeTransito controlador;
    controlador.carregarDados();

    int opcao = -1;
    while (opcao != 0) {
        std::cout << "\n=========================================\n";
        std::cout << "      SISTEMA CONTROLADOR DE VIAGENS     \n";
        std::cout << "=========================================\n";
        std::cout << "1. Cadastrar Cidade\n";
        std::cout << "2. Cadastrar Trajeto\n";
        std::cout << "3. Cadastrar Passageiro\n";
        std::cout << "4. Cadastrar Transporte\n";
        std::cout << "5. Iniciar Viagem Direta\n";
        std::cout << "6. Avancar Tempo (Horas)\n";
        std::cout << "7. Relatorio de Estado\n";
        std::cout << "0. Salvar e Sair\n";
        std::cout << "Escolha uma opcao: ";
        
        std::cin >> opcao;
        limparBuffer();

        if (opcao == 1) {
            std::string nome;
            std::cout << "Nome da Cidade: ";
            std::getline(std::cin, nome);
            controlador.cadastrarCidade(nome);
            std::cout << "Cidade cadastrada com sucesso!\n";
        } 
        else if (opcao == 2) {
            std::string origem, destino;
            char tipo;
            int dist;
            std::cout << "Origem: "; std::getline(std::cin, origem);
            std::cout << "Destino: "; std::getline(std::cin, destino);
            std::cout << "Tipo (A - Aquatico / T - Terrestre / V - Aereo): "; std::cin >> tipo;
            std::cout << "Distancia (km): "; std::cin >> dist;
            controlador.cadastrarTrajeto(origem, destino, tipo, dist);
            std::cout << "Trajeto cadastrado!\n";
        }
        else if (opcao == 3) {
            std::string nome, local;
            std::cout << "Nome do Passageiro: "; std::getline(std::cin, nome);
            std::cout << "Cidade Atual: "; std::getline(std::cin, local);
            controlador.cadastrarPassageiro(nome, local);
            std::cout << "Passageiro cadastrado!\n";
        }
        else if (opcao == 4) {
            std::string nome, local;
            char tipo;
            int cap, vel, distDesc, tempoDesc;
            std::cout << "Nome do Transporte: "; std::getline(std::cin, nome);
            std::cout << "Tipo (A - Aquatico / T - Terrestre / V - Aereo): "; std::cin >> tipo;
            std::cout << "Capacidade: "; std::cin >> cap;
            std::cout << "Velocidade (km/h): "; std::cin >> vel;
            std::cout << "Distancia entre descansos (km) (Digite um valor alto para voos diretos): "; std::cin >> distDesc;
            std::cout << "Tempo de descanso (horas): "; std::cin >> tempoDesc;
            limparBuffer();
            std::cout << "Cidade Atual: "; std::getline(std::cin, local);
            controlador.cadastrarTransporte(nome, tipo, cap, vel, distDesc, tempoDesc, local);
            std::cout << "Transporte cadastrado!\n";
        }
        else if (opcao == 5) {
            std::string transporte, origem, destino, passageiro;
            std::cout << "Nome do Transporte: "; std::getline(std::cin, transporte);
            std::cout << "Origem: "; std::getline(std::cin, origem);
            std::cout << "Destino: "; std::getline(std::cin, destino);
            std::cout << "Nome do Passageiro: "; std::getline(std::cin, passageiro);
            
            std::vector<std::string> pass = {passageiro};
            controlador.iniciarViagem(transporte, pass, origem, destino);
        }
        else if (opcao == 6) {
            int horas;
            std::cout << "Quantas horas deseja avancar? "; std::cin >> horas;
            controlador.avancarHoras(horas);
        }
        else if (opcao == 7) {
            controlador.relatarEstado();
        }
        else if (opcao == 0) {
            std::cout << "Salvando dados...\n";
            controlador.salvarDados();
            std::cout << "Programa encerrado.\n";
        } else {
            std::cout << "Opcao invalida.\n";
        }
    }

    return 0;
}