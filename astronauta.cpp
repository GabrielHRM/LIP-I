#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Astronauta{
    public:
        string cpf;
        string nome;
        int idade;
        int estado; //vivo(1) ou morto(0)
        int disponibilidade; //Disponivel(1) ou indisponivel(0)

    Astronauta(string c, string n, int i){
        cpf = c;
        nome = n;
        idade = i;
        estado = true;
        disponibilidade = true;
    }
};

class Voo{
    public:
        int codevoo;
        vector<string> cpfsPassageiros;
        string estado;

    Voo(int c){
        estado = "planejado";
        codevoo = c;
    }
};



int main(){
    string comando;
    vector<Astronauta> astronautas;
    vector<Voo> voos;

    while(cin >> comando && comando != "FIM"){
        if(comando == "CADASTRAR_ASTRONAUTA"){
            string cpf, nome;
            int idade;
            cin >> cpf >> idade;
            getline(cin >> ws, nome);

            bool jaExiste = 0;
            for(const auto& a : astronautas){
                if(a.cpf== cpf){
                    jaExiste = 1;
                    break;
                }
            }
            if(jaExiste){
                cout << "Erro: CPF já cadastrado" << endl;
            }else{
                Astronauta novoAstro(cpf, idade, nome);
                astronautas.push_back(novoAstro);
            }
        }else if(comando == "CADASTRAR_VOO"){
            int code;
            cin >> code;

            bool jaExiste = 0;
            for(const auto& v : voos){
                if(v.codevoo == code){
                    jaExiste = 1;
                    break;
                }
            }

            if(jaExiste)[
                cout << "Erro: Voo já cadastrado" << endl;
            ]else{
                Voo novoV(code);
                voos.push_back(novoV);
            }
        }else if(comando == "ADICIONAR_ASTRONAUTA"){
            string cpf;
            int code;

            cin >> cpf >> code;

            Astronauta *astroEncontrado = nullptr;
            Voo* vooEncontrado = nullptr;

            for(auto& a : astronautas){
                if(cpf == a.cpf){
                    astroEncontrado = &a;
                    break;
                }
            }

            for(auto& v : voos){
                if(code == v.codevoo){
                    vooEncontrado = &v;
                    break;
                }
            }

            if(astroEncontrado == nullptr){
                cout<<"Astronauta nao cadastrado"<<endl;
            }else if(vooEncontrado == nullptr){
                cout<<"Voo nao cadastrado"<<endl;
            }else  if(vooEncontrado->estado != "planejado"){
                cout<<"Voo nao esta mais planejado"<<endl;
            }else if(astroEncontrado->estado != true){
                cout<<"O astronauta está morto"<<endl;
            }else{
                int valida = 0;
                for(string c : vooEncontrado->cpfsPassageiros){
                    if(c == cpf){
                        valida = 1;
                        break;
                    }
                }
            }
            if(valida){
                cout<<"Astronauta ja esta no voo"<<endl;
            }else{
                vooEncontrado->cpfsPassageiros.push_back(cpf);
            }
        }else if(comando == "REMOVER_ASTRONAUTA"){
            string cpf;
            int code;
            int indice = -1;

            cin >> cpf >> code;

            Astronauta *astroEncontrado = nullptr;
            Voo* vooEncontrado = nullptr;

            for(auto& a : astronautas){
                if(cpf == a.cpf){
                    astroEncontrado = &a;
                    break;
                }
            }

            for(auto& v : voos){
                if(code == v.codevoo){
                    vooEncontrado = &v;
                    break;
                }
            }

            for (int i = 0; i < voos.size(); i++) {
                if(vooEncontrado->cpfsPassageiros[i] == cpf){
                    indice = i;
                    break;
                }
            }

            if(astroEncontrado == nullptr){
                cout<<"Astronauta nao cadastrado"<<endl;
            }else if(vooEncontrado == nullptr){
                cout<<"Voo nao cadastrado"<<endl;
            }else  if(vooEncontrado->estado != "planejado"){
                cout<<"Voo nao esta mais planejado"<<endl;
            }else{
                if(indice == -1){
                    cout<<"Astronauta não esta no voo"<<endl;
                }else{
                    vooEncontrado->cpfsPassageiros.erase(cpfsPassageiros.begin() + indice);
                    cout<<"Astronauta removido da lista de passageiros"<<endl;
                }
            }
        }
    }

    return 0;
};