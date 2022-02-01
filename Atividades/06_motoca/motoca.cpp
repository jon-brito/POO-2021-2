#include <iostream>
using namespace std;

struct Pessoa {
    string nome {""};
    int idade {0};

    Pessoa(string nome = "", int idade = 0) :
        nome {nome}, idade{idade} {
    }
};

struct Motoca {
    Pessoa *pessoa {nullptr};
    bool tem_pessoa {false};
    int potencia {0};
    int tempo {0};

    Motoca(int potencia) :
        potencia {potencia} {
    }

    void Imprimir() {
        cout << "\nPotencia : " << this->potencia << '\n';
        cout << "Minutos restantes: " << this->tempo << '\n';
        cout << "Tem pessoa? ";
        this->tem_pessoa ? cout << "Sim\n" : cout << "Nao\n";
    }

    void Descer() {
        if (tem_pessoa) {
            this->tem_pessoa = false;
            cout << this->pessoa->nome << " desceu da moto!\n";
            this->pessoa = nullptr;
        }
    }

    void Subir(Pessoa *pessoa) {
        if (tem_pessoa) 
            Descer();
        this->pessoa = pessoa;
        this->tem_pessoa = true;
        cout << this->pessoa->nome << " subiu na moto!\n";
        
    }

    void ComprarTempo(int tempo) {
        this->tempo += tempo;
    }

    void Dirigir(int tempo) {
        if (tem_pessoa) {
            if (this->pessoa->idade <= 10) {
                int dirigidas {0};
                while(this->tempo > 0 && tempo > 0) {
                    dirigidas++;
                    this->tempo--;
                    tempo--;
                }
                cout << "Eu dirigi por " << dirigidas << " minutos";
                if (tempo > this->tempo) cout << " e acabou o tempo!\n";
                else cout << "!\n";

            } else {
                cout << "Sai daqui " << this->pessoa->nome << ", voce é muito grande!\n";
            }
        } else {
            cout << "Necessito de alguém para dirigir\n";
        }
    }

    void Buzinar() {
        if (tem_pessoa) {
            cout << "P";
            for (int i = 1; i <= this->potencia; i++) {
                cout << "e";
            }
            cout << "m!\n";

        } else {
            cout << "Apesar de inteligente, nao consigo buzinar sozinho :)\n";
        }
    }
};

int main() {
    Pessoa p1 {"joao", 6};
    Pessoa p2 {"mateus", 12};

    Motoca m1 {2};
    m1.Subir(&p2);
    m1.Subir(&p1);
    m1.ComprarTempo(15);
    m1.Dirigir(20);
    m1.Buzinar();
    m1.Imprimir();

    return 0;
}