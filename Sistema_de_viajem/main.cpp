#include "ControladorDeTransito.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// Imprime as opções do menu na tela
void mostrarMenu()
{
    std::cout << "--- MENU CONTROLADOR DE VIAGENS ---\n";
    std::cout << "1. Cadastrar Cidade\n";
    std::cout << "2. Cadastrar Trajeto\n";
    std::cout << "3. Cadastrar Transporte\n";
    std::cout << "4. Cadastrar Passageiro\n";
    std::cout << "5. Iniciar Viagem\n";
    std::cout << "6. Avançar Horas\n";
    std::cout << "7. Exibir Relatórios do Sistema\n";
    std::cout << "8. Salvar Modificações (Persistência)\n";
    std::cout << "0. Encerrar Sistema\n";
    std::cout << "Entre com a opção desejada: ";
}

// Canal de comunicação direta entre as ações do usuário e o gerenciador do sistema
int main()
{
    ControladorDeTransito ctrl;
    ctrl.carregarDados(); // Carrega os dados salvos antes de abrir o menu

    int escolha = -1;
    while (escolha != 0) {
        mostrarMenu();
        // Evita erros caso o usuário digite texto onde deveria ser um número
        if (!(std::cin >> escolha)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin.ignore(); 

        if (escolha == 1) {
            std::string nome;
            std::cout << "Nome da localidade urbana: ";
            std::getline(std::cin, nome);
            ctrl.cadastrarCidade(nome);
        } else if (escolha == 2) {
            std::string o, d; char t; int dist;
            std::cout << "Origem: "; std::getline(std::cin, o);
            std::cout << "Destino: "; std::getline(std::cin, d);
            // Incluído a opção E no menu de trajetos
            std::cout << "Tipo de ambiente (A - Aquático, T - Terrestre, E - Aéreo): "; std::cin >> t;
            std::cout << "Distância total (em Quilômetros): "; std::cin >> dist;
            ctrl.cadastrarTrajeto(o, d, t, dist);
        } else if (escolha == 3) {
            std::string nome, local; char t; int cap, vel, distD, tempD;
            std::cout << "Nome do Veículo: "; std::getline(std::cin, nome);
            // Incluído a opção E no menu de transportes
            std::cout << "Tipo (A - Aquático, T - Terrestre, E - Aéreo): "; std::cin >> t;
            std::cout << "Capacidade Máxima (Pessoas): "; std::cin >> cap;
            std::cout << "Velocidade Média (Km/h): "; std::cin >> vel;
            std::cout << "Janela máxima antes de parada (Km): "; std::cin >> distD;
            std::cout << "Tempo de descanso regulamentar (Horas): "; std::cin >> tempD;
            std::cin.ignore();
            std::cout << "Cidade Sede (Local Inicial): "; std::getline(std::cin, local);
            ctrl.cadastrarTransporte(nome, t, cap, vel, distD, tempD, local);
        } else if (escolha == 4) {
            std::string nome, local;
            std::cout << "Nome do Passageiro: "; std::getline(std::cin, nome);
            std::cout << "Cidade de Alocação Inicial: "; std::getline(std::cin, local);
            ctrl.cadastrarPassageiro(nome, local);
        } else if (escolha == 5) {
            std::string v, o, d, pLinha, pNome;
            std::vector<std::string> listaPassageiros;
            std::cout << "Nome do Transporte escolhido: "; std::getline(std::cin, v);
            std::cout << "Cidade de Saída: "; std::getline(std::cin, o);
            std::cout << "Cidade Destino Final: "; std::getline(std::cin, d);
            std::cout << "Passageiros (separados por vírgula): "; std::getline(std::cin, pLinha);
            
            // Separa os nomes dos passageiros digitados na mesma linha por vírgula e limpa os espaços vazios
            std::stringstream ss(pLinha);
            while (std::getline(ss, pNome, ',')) {
                size_t start = pNome.find_first_not_of(" ");
                size_t end = pNome.find_last_not_of(" ");
                if (start != std::string::npos && end != std::string::npos) {
                    listaPassageiros.push_back(pNome.substr(start, (end - start + 1)));
                }
            }
            ctrl.iniciarViagem(v, listaPassageiros, o, d);
        } else if (escolha == 6) {
            int h;
            std::cout << "Quantidade de horas para simulação: "; std::cin >> h;
            ctrl.avancarHoras(h);
        } else if (escolha == 7) {
            ctrl.relatarEstado();
        } else if (escolha == 8) {
            ctrl.salvarDados();
        }
    }
    
    // Garante que tudo seja salvo no arquivo quando o usuário escolher fechar o programa
    std::cout << "Encerrando e salvando logs do controlador...\n";
    ctrl.salvarDados();
    return 0;
}