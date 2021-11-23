#pragma once
#include "telefone.hpp"
#include <list>


class Contato {
private:
    string nome;
    list<Telefone> telefones;

    bool ehRepetido(Telefone fone) {
        for (auto telefone : telefones) {
            if (fone.getNumero() == telefone.getNumero() && fone.getTipo() == telefone.getTipo()) {
                return true;
            }
        }

        return false;
    }

public:
    Contato(string nome, list<Telefone> telefones) : nome{nome}, telefones{telefones} {}
    Contato(string nome) : nome{nome}, telefones{} {}

    string getNome() {
        return this->nome;
    }

    list<Telefone> getTelefones() {
        return this->telefones;
    }

    void adicionar(list<Telefone> fones) {
        for (auto fone : fones) {
            adicionar(fone);
        }
    }

    void adicionar(Telefone fone) {
        if (fone.getNumero() != "" && !ehRepetido(fone)) {
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