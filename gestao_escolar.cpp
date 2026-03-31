#include <iostream>
#include <string>
#define MAX_ALUNOS 50
using namespace std;

class Data{
    public:
        int dia;
        int mes;
        int ano;

        void ImprimirData(){
            cout << dia << "/" << mes << "/" << ano;
        }
};

class Aluno{
    public:
        int matricula;
        string nome;
        Data nascimento;

        void ImprimirAluno(){
            cout << matricula << " | " << nome << " | "; 
            nascimento.ImprimirData();
            cout<<"\n";

        }
};

int main(){
    Aluno turma[MAX_ALUNOS];
    int totalAlunos = 0;
    int opcao = -1;

    while(opcao != 0){
        cout<<"\nMenu\n";
        cout<<"1. Adicionar Aluno\n";
        cout<<"2. Listar Alunos\n";
        cout<<"0. Sair\n";

        cin >> opcao;

        switch (opcao){
            case 1:
                if(totalAlunos < MAX_ALUNOS){
                    cout << "Digite a matricula do aluno: ";
                    cin >> turma[totalAlunos].matricula;
                    cout<<"\n";

                    cout << "Digite o primeiro nome do aluno: ";
                    cin >> turma[totalAlunos].nome;
                    cout<<"\n";

                    cout << "Digite a data de nascimento do aluno: ";
                    cin >> turma[totalAlunos].nascimento.dia 
                        >> turma[totalAlunos].nascimento.mes 
                        >> turma[totalAlunos].nascimento.ano;
                    cout<<"\n";

                    totalAlunos++;
                    cout<<"Aluno Matriculado com sucesso!";
                }else{
                    cout<<"Número maxim ode alunos atingido!";
                }
                break;
            case 2:
                for(int i = 0; i < totalAlunos; i++){
                    turma[i].ImprimirAluno();
                }
                break;
            case 0:
                break;

            default:
                cout << "Opcao invalida!";
                break;
        }
    }

    return 0;
}