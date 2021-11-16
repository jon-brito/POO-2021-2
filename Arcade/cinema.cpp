#include <iostream>
#include <list>
#include <vector>
#include <memory>
using namespace std;

void clear_terminal()
{
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

class Cliente {
private:
    string nome;
    string telefone;

public:
    Cliente(string nome = "", string telefone = "") : nome{nome}, telefone{telefone} {}

    string getNome() {
        return this->nome;
    }

    string getTelefone() {
        return this->telefone;
    }

    void setNome(string str) {
        this->nome = str;
    }

    void setTelefone(string str) {
        this->telefone = str;
    }

    friend ostream& operator<<(ostream& os, Cliente& cliente) {
        os << "Cliente: " << cliente.getNome() << ", Fone: " << cliente.getTelefone();
        return os;
    }

};

class Cinema {
private:
    vector<shared_ptr<Cliente>> cadeiras;
    const int qtd_cadeiras;
    int sentados;

public:
    Cinema(int qtd_cadeiras) : cadeiras(qtd_cadeiras, nullptr), qtd_cadeiras{qtd_cadeiras}, sentados{0} {}

    void reservar(string nome, string telefone, int cadeira) {
        if (sentados == qtd_cadeiras) {
            cout << "Cinema lotado\n";
            return;
        }

        for (auto cliente : cadeiras) {
            if (cliente == nullptr) {
                continue;
            }
            
            if (nome == cliente->getNome()) {
                cout << "Cliente já cadastrado\n";
                return;
            }
        }

        if (cadeira > cadeiras.size() - 1 || cadeira < 0) {
            cout << "Cadeira inexistente\n";
            return;
        }

        if (cadeiras[cadeira] != nullptr) {
            cout << "Cadeira ocupada\n";
            return;
        }

        this->sentados++;
        cadeiras[cadeira] = make_shared<Cliente>(nome, telefone);
        cout << nome << " sentou na cadeira " << cadeira << '\n';
    }

    void cancelar(string nome) {
        for (int i = 0; i < qtd_cadeiras; i++) {
            if (cadeiras[i] == nullptr) {
                continue;
            }

            if (this->cadeiras[i]->getNome() == nome) {
                this->cadeiras[i] = nullptr;
                sentados--;
                cout << nome << " saiu do cinema\n";
                return;
            }
        }

        cout << nome << " nao esta no cinema\n";
    }

    friend ostream& operator<<(ostream& os, Cinema& cinema) {
        for (int i = 0; i < cinema.qtd_cadeiras; i++) {
            if (cinema.cadeiras[i] == nullptr) {
                os << "----" << ' ';
                continue;
            }

            os << cinema.cadeiras[i]->getNome() << ' ';
        }
        cout << '\n';
    }

};

int main() {

    while (true) {
        clear_terminal();
        cout << "=-=-=-=-=-=CRIANDO SEU CINEMA=-=-=-=-=-=\n";
        cout << "Deseja criar um novo cinema? [sim/nao] ";

        string escolha {""};
        cin >> escolha;

        if (escolha == "sim") {
            clear_terminal();

            int qtd_cadeiras {};
            cout << "\nDigite a quantidade de cadeiras: ";
            cin >> qtd_cadeiras;
            Cinema cine(qtd_cadeiras);

            clear_terminal();
            string opcao {""};

            while (opcao != "0") {
                cout << "\n[1] - Reservar cadeira\n";
                cout << "[2] - Cancelar reserva\n";
                cout << "[3] - Mostrar cadeiras\n";
                cout << "[0] - Destruir  cinema\n";

                cout << "Sua opcao: ";
                cin >> opcao;

                if (opcao == "1") {
                    string nome, telefone;
                    int indice_cadeira;

                    cout << "\nNome do cliente: ";
                    cin >> nome;

                    cout << "Telefone do cliente: ";
                    cin >> telefone;

                    cout << "Cadeira para reservar: ";
                    cin >> indice_cadeira;

                    clear_terminal();
                    cine.reservar(nome, telefone, indice_cadeira);

                } else if (opcao == "2") {
                    clear_terminal();
                    string nome {};
                    cout << "Nome do cliente para cancelar: ";
                    cin >> nome;
                    clear_terminal();
                    cine.cancelar(nome);

                } else if (opcao == "3") {
                    clear_terminal();
                    cout << cine;

                } else if (opcao != "0") {
                    clear_terminal();
                    cout << "Opcao inválida\n";
                }
            }

        } else if (escolha == "nao") {
            cout << "Saindo da criacao do cinema...\n";
            break;
        } else {
            cout << "Opcao invalida\n";
        }

    }

    return 0;
}