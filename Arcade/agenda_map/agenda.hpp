#pragma once

#include "contato.hpp"
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Agenda {
private:
    map<string, Contato> contatos;

public:
    Agenda() {}

    void adicionarContato(const Contato& cont) {
        auto it = contatos.find(cont.getNome());

        if (it == contatos.end()) {
            this->contatos[cont.getNome()] = cont;
        } else {
            it->second.adicionar(cont.getTelefones());
        }
    }

    void adicionarContato(const vector<Contato>& conts) {
        for (auto contato : conts) {
            adicionarContato(contato);
        }
    }

    void remover(string nome) {
        auto it = contatos.find(nome);

        if (it != contatos.end()) {
            contatos.erase(it);
        } else {
            std::cout << "Contato nao existe.\n";
        }
    }

    void remover(string nome, int indice) {
        auto it = contatos.find(nome);

        if (it != contatos.end()) {
            it->second.remover(indice);
        } else {
            std::cout << "Contato nao existe.\n";
        }
    }

    void buscar(string str) {
        for (auto cont : contatos) {
            size_t found = cont.second.getNome().find(str);
            if (found != string::npos) {
                cout << cont.second << '\n';
            }
        }
        cout << '\n';
    }

    void buscar(int num) {
        string numero = to_string(num);
        for (auto cont : contatos) {
            for (auto fone : cont.second.getTelefones()) {
                size_t found = fone.getNumero().find(numero);
                
                if (found != string::npos) {
                    cout << cont.second << '\n';
                }
            }
        }

        cout << '\n';
    }

    friend ostream& operator<<(ostream& os, Agenda& agenda) {
        os << '\n';

        for (auto cont : agenda.contatos) {
            os << cont.second << '\n';
        }

        return os;
    }
};