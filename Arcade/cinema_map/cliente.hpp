#pragma once

#include <iostream>
using namespace std;

class Cliente {
private:
    string nome;
    string telefone;

public:
    Cliente(string nome = "", string telefone = "") : nome{nome}, telefone{telefone} {}

    string getNome() const {
        return this->nome;
    }

    string getTelefone() const {
        return this->telefone;
    }

    void setNome(string str) {
        this->nome = str;
    }

    void setTelefone(string str) {
        this->telefone = str;
    }

    friend ostream& operator<<(ostream& os, const Cliente& cliente) {
        os << "Cliente: " << cliente.getNome() << ", Fone: " << cliente.getTelefone();
        return os;
    }

};