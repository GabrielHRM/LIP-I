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
        }else if(comando == "LANCAR_VOO"){
            int code;
            cin >> code;

            Voo* vooEncontrado = nullptr;

            for(auto& v : voos){
                if(code == v.codevoo){
                    vooEncontrado = &v;
                    break;
                }
            }

            if(vooEncontrado == nullptr){
                cout<<"Voo nao cadastrado"<<endl;
            }else  if(vooEncontrado->estado != "planejado"){
                cout<<"Voo nao esta mais planejado"<<endl;
            }else if (vooEncontrado->cpfsPassageiros.empty()) {
                cout << "Erro: Nao e possivel lancar um voo sem astronautas." << endl;
            }else{
                bool lancamento = true;

                for(const string& cpfP : vooEncontrado->cpfsPassageiros){
                    for(auto& a : astronautas){
                        if(a.cpf == cpfP){
                            if(a.estado == 0 || a.disponibilidade == 0){
                                lancamento = false;
                                break;
                            }
                        }
                    }
                }
            }
            if(!lancamento){
                cout<<"Astronauta morto ou nao disponivel"<<endl;
            }else{
                vooEncontrado->estado = "em curso";

                for(const string& cpfP : vooEncontrado->cpfsPassageiros){
                    for(auto& a : astronautas){
                        if(a.cpf == cpfP){
                            a.estado = false; //morto;
                        }
                    }
                }
            }
        }else if(comando == "EXPLODIR_VOO"){
            int code;
            cin >> code;

            Voo* vooEncontrado = nullptr;

            for(auto& v : voos){
                if(code == v.codevoo){
                    vooEncontrado = &v;
                    break;
                }
            }

            if(vooEncontrado == nullptr){
                cout<<"Voo nao cadastrado"<<endl;
            }else  if(vooEncontrado->estado != "em curso"){
                cout<<"Voo nao esta em curso"<<endl;
            }else{
                vooEncontrado->estado = "finalizado com explosão";

                for(const string& cpfP : vooEncontrado->cpfsPassageiros){
                    for(auto& a : astronautas){
                        if(a.cpf == cpfP){
                            a.estado = false; //morto
                            a.disponibilidade = false; //indisponivel
                        }
                    }
                }
            }
        }else if(comando == "FINALIZAR_VOO"){
            int code;
            cin >> code;

            Voo* vooEncontrado = nullptr;

            for(auto& v : voos){
                if(code == v.codevoo){
                    vooEncontrado = &v;
                    break;
                }
            }

            if(vooEncontrado == nullptr){
                cout<<"Voo nao cadastrado"<<endl;
            }else  if(vooEncontrado->estado != "em curso"){
                cout<<"Voo nao esta mais planejado"<<endl;
            }else{
                vooEncontrado->estado = "finalizado com sucesso";

                for(const string& cpfP : vooEncontrado->cpfsPassageiros){
                    for(auto& a : astronautas){
                        if(a.cpf == cpfP){
                            a.disponibilidade = true; //disponivel
                        }
                    }
                }
            }
        }else if(comando == "LISTAR_VOOS"){
            string estados[] = {"planejado", "em curso", "finalizado com sucesso", "finalizado com explosão"};

            for(int i = 0; i < 4; i++){
                cout << "VOOS: " << estados[e] << endl;
                
                for(auto& v : voos){
                    if(v.estado == estados[i]){
                        cout << "Codigo: " << v.codevoo << endl;
                        cout << "Passageiros:" << endl;

                        for(const string& cpfP : v.cpfsPassageiros){
                            for(auto& a : astronautas){
                                if(a.cpf == cpfP){
                                    cout << a.cpf << ": " << a.nome << endl;
                                }
                            }
                        }
                    }
                }
            }
        }else if(comando == "LISTAR_MORTOS"){
            cout << "--- LISTA DE ASTRONAUTAS MORTOS ---" << endl;
            bool encontrouMorto = false;

            for(auto& a : astronautas){
                if(a.estado == false){
                    encontrouMorto = true;
                    cout << "CPF: "<<a.cpf<<endl;
                    cout<<"Nome: " << a.nome << endl;

                    cout<<"Voos que participou: "<<endl;
                    for(auto& v : voos){
                        if(v.estado != "planejado"){
                            for(const string& cpfP : v.cpfsPassageiros){
                                for(auto& a : astronautas){
                                    if(cpfP == a.cpf){
                                        cout << v.codevoo << " ";
                                        participouDeAlgum = true;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if(encontrouMorto == false){
                cout<<"Nenhum astronauta morto no sistema."<<endl;
            }
        }
    }
    return 0;
};