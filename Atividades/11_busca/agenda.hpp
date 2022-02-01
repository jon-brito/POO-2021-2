#pragma once
#include "contato.hpp"

class Agenda {
private:
    list<Contato> contatos;

    list<Contato>::iterator existe(string nome) {
        for (auto it = contatos.begin(); it != contatos.end(); ++it) {
            if (nome == (*it).getNome()) {
                return it;
            }
        }

        return contatos.end();
    }

    void adicionarNumeros(list<Contato>::iterator it, Contato cont) {
        for (auto num : cont.getTelefones()) {
            (*it).adicionar(num);
        }
    }

public:
    Agenda() {}

    void adicionarContato(list<Contato>& conts) {
        for (auto cont : conts) {
            adicionarContato(cont);
        }
    }

    void adicionarContato(Contato& cont) {
        auto it = existe(cont.getNome());
        if (it != contatos.end()) {
            cout << "Contato existente.\n";
            adicionarNumeros(it, cont);
            return;
        }

        cout << "Contato adicionado.\n";
        contatos.push_back(cont);
    }

    void remover(string nome) {
        auto it = existe(nome);
        if (it == contatos.end()) {
            cout << "Contato inexistente.\n";
            return;
        }

        cout << nome << " removido(a) da agenda.\n";
        contatos.erase(it);
    }

    void remover(string nome, int indice) {
        auto it = existe(nome);
        if (it == contatos.end()) {
            cout << "Contato inexistente.\n";
            return;
        }

        cout << "Fone " << indice << " removido de " << nome << ".\n";
        (*it).remover(indice);
    }

    void busca(string str) {
        for (auto cont : contatos) {
            size_t found = cont.getNome().find(str);
            if (found != string::npos) {
                cout << cont << '\n';
            }
        }
        cout << '\n';
    }

    void busca(int num) {
        string numero = to_string(num);
        for (auto cont : contatos) {
            for (auto fone : cont.getTelefones()) {
                size_t found = fone.getNumero().find(numero);
                if (found != string::npos) {
                    cout << cont << '\n';
                }
            }
        }
        cout << '\n';
    }

    friend ostream& operator<<(ostream& os, Agenda& agenda) {
        os << '\n';
        for (auto cont : agenda.contatos) {
            os << cont << '\n';
        }

        return os;
    }
};