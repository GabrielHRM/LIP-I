#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Astronauta{
    public:
        string cpf;
        string nome;
        int idade;
        bool estado; //vivo(1) ou morto(0)
        bool disponibilidade; //Disponivel(1) ou indisponivel(0)

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
                // Ordem correta: CPF, Nome, Idade
                Astronauta novoAstro(cpf, nome, idade);
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

            if(jaExiste){
                cout << "Erro: Voo já cadastrado" << endl;
            }else{
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
            }else if(vooEncontrado->estado != "planejado"){
                cout<<"Voo nao esta mais planejado"<<endl;
            }else if(astroEncontrado->estado != true){
                cout<<"O astronauta está morto"<<endl;
            }else{
                bool jaEsta = false;
                for(string c : vooEncontrado->cpfsPassageiros){
                    if(c == cpf){
                        jaEsta = true;
                        break;
                    }
                }
                if(jaEsta){
                    cout<<"Astronauta ja esta no voo"<<endl;
                }else{
                    vooEncontrado->cpfsPassageiros.push_back(cpf);
                }
            }
        }else if(comando == "REMOVER_ASTRONAUTA"){
            string cpf;
            int code;
            cin >> cpf >> code;

            Voo* vooEncontrado = nullptr;
            for(auto& v : voos){
                if(code == v.codevoo){
                    vooEncontrado = &v;
                    break;
                }
            }

            if(vooEncontrado == nullptr){
                cout<<"Voo nao cadastrado"<<endl;
            }else if(vooEncontrado->estado != "planejado"){
                cout<<"Voo nao planejado"<<endl;
            }else{
                int indice = -1;
                for(int i = 0; i < (int)vooEncontrado->cpfsPassageiros.size(); i++){
                    if(vooEncontrado->cpfsPassageiros[i] == cpf){
                        indice = i;
                        break;
                    }
                }
                if(indice == -1){
                    cout<<"Astronauta não esta no voo"<<endl;
                }else{
                    vooEncontrado->cpfsPassageiros.erase(vooEncontrado->cpfsPassageiros.begin() + indice);
                    cout<<"Astronauta removido"<<endl;
                }
            }
        }else if(comando == "LANCAR_VOO"){
            int code;
            cin >> code;
            Voo* v = nullptr;
            for(auto& item : voos){
                if(item.codevoo == code) v = &item;
            }

            if(v && v->estado == "planejado" && !v->cpfsPassageiros.empty()){
                bool possivel = true;
                for(string c : v->cpfsPassageiros){
                    for(auto& a : astronautas){
                        if(a.cpf == c && (a.estado == false || a.disponibilidade == false)) possivel = false;
                    }
                }
                if(possivel){
                    v->estado = "em curso";
                    for(string c : v->cpfsPassageiros){
                        for(auto& a : astronautas){
                            if(a.cpf == c) a.disponibilidade = false;
                        }
                    }
                }else{
                    cout << "Erro: Astronautas mortos ou ocupados" << endl;
                }
            }else{
                cout << "Erro no lancamento" << endl;
            }
        }else if(comando == "EXPLODIR_VOO"){
            int code;
            cin >> code;
            for(auto& v : voos){
                if(v.codevoo == code && v.estado == "em curso"){
                    v.estado = "finalizado com explosão";
                    for(string c : v.cpfsPassageiros){
                        for(auto& a : astronautas){
                            if(a.cpf == c){
                                a.estado = false;
                                a.disponibilidade = false;
                            }
                        }
                    }
                }
            }
        }else if(comando == "FINALIZAR_VOO"){
            int code;
            cin >> code;
            for(auto& v : voos){
                if(v.codevoo == code && v.estado == "em curso"){
                    v.estado = "finalizado com sucesso";
                    for(string c : v.cpfsPassageiros){
                        for(auto& a : astronautas){
                            if(a.cpf == c) a.disponibilidade = true;
                        }
                    }
                }
            }
        }else if(comando == "LISTAR_VOOS"){
            string est[] = {"planejado", "em curso", "finalizado com sucesso", "finalizado com explosão"};
            for(int i = 0; i < 4; i++){
                cout << "--- VOOS " << est[i] << " ---" << endl;
                for(auto& v : voos){
                    if(v.estado == est[i]){
                        cout << "Codigo: " << v.codevoo << endl;
                        for(string c : v.cpfsPassageiros){
                            for(auto& a : astronautas){
                                if(a.cpf == c) cout << " - " << a.cpf << ": " << a.nome << endl;
                            }
                        }
                    }
                }
            }
        }else if(comando == "LISTAR_MORTOS"){
            for(auto& a : astronautas){
                if(a.estado == false){
                    cout << "CPF: " << a.cpf << " Nome: " << a.nome << " Voos: ";
                    for(auto& v : voos){
                        if(v.estado != "planejado"){
                            for(string c : v.cpfsPassageiros){
                                if(c == a.cpf) cout << v.codevoo << " ";
                            }
                        }
                    }
                    cout << endl;
                }
            }
        }
    }
    return 0;
}