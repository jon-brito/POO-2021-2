#pragma once

#include <iostream>
#include <list>
#include <memory>
#include "conta.hpp"
using namespace std;

class Cliente {
private:
    list<shared_ptr<Conta>> contas;
    string nome;

public:
    Cliente();

    Cliente(string nome) : nome{nome} {}

    void adicionarConta(shared_ptr<Conta> c) {
        contas.push_back(c);
    }

    list<shared_ptr<Conta>> getContas() const {
        return this->contas;
    }

    string getNome() const {
        return this->nome;
    }

    void setContas(list<shared_ptr<Conta>> novas) {
        this->contas = novas;
    }

    void setNome(string nome) {
        this->nome = nome;
    }

    friend ostream& operator<<(ostream& os, const Cliente& c) {
        os << c.nome;
        return os;
    }
};