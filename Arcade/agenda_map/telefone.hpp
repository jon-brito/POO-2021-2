#pragma once

#include <iostream>
using namespace std;

class Telefone {
private:
    string tipo;
    string numero;

public:
    Telefone(string tipo = "", string numero = "") {
        if (validarNumero(numero)) {
            this->tipo = tipo;
            this->numero = numero;
        }
    }

    string getTipo() const {
        return this->tipo;
    }

    string getNumero() const {
        return this->numero;
    }

    void setTipo(string str) {
        this->tipo = str;
    }

    void setNumero(string str) {
        if (validarNumero(str)) {
            this->numero = str;
        }
    }

    bool validarNumero(string numero) {
        for (auto c : numero) {
            if (!((c == 40 || c == 41) || (c == 46) || (c >= 48 && c <= 57))) {
                return false;
            }
        }

        return true;
    }

    friend ostream& operator<<(ostream& os, Telefone telefone) {
        os << telefone.getTipo() << ":" << telefone.getNumero();
        return os;
    }

};