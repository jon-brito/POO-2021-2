#pragma once
#include "telefone.hpp"
#include <vector>

class Contato {
private:
    string nome;
    vector<Telefone> telefones;

    bool ehRepetido(Telefone fone) {
        for (auto telefone : telefones) {
            if (fone.getNumero() == telefone.getNumero() && fone.getTipo() == telefone.getTipo()) {
                return true;
            }
        }

        return false;
    }

public:
    Contato(string nome, vector<Telefone> telefones) : nome{nome} {
        adicionar(telefones);
    }

    Contato(string nome) : nome{nome} {}

    Contato() : nome{""} {}

    string getNome() const {
        return this->nome;
    }

    vector<Telefone> getTelefones() const {
        return this->telefones;
    }

    void adicionar(vector<Telefone> fones) {
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
        auto vec = contato.getTelefones();

        for (int i = 0; i < vec.size(); i++) {
            os << "[" << i << ":" << vec[i] << "] ";
        }

        return os;
    }
};