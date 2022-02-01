#pragma once
#include "telefone.hpp"
#include <list>


class Contato {
private:
    string nome;
    list<Telefone> telefones;

public:
    Contato(string nome, list<Telefone> telefones) : nome{nome}, telefones{telefones} {}
    Contato(string nome) : nome{nome}, telefones{} {}

    void adicionar(Telefone fone) {
        if (fone.getNumero() != "") {
            telefones.push_back(fone);
        }
    }

    void remover(int indice) {
        if (indice < 0 || indice > telefones.size() - 1) {
            std::cout << "Indice invalido.\n";
            return;
        }

        int contador {0};
        for (auto it = telefones.begin(); it != telefones.end(); it++) {
            if (contador == indice) {
                telefones.erase(it);
                return;
            } else {
                contador++;
            }
        }
    }

    friend ostream& operator<<(ostream& os, Contato& contato) {
        os << "- " << contato.nome << ' ';
        
        int contador {0};
        for (auto fone : contato.telefones) {
            os << '[' << contador << ":" << fone << "] ";
            contador++;
        }

        return os;
    }
};