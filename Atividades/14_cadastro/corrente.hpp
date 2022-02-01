#pragma once

#include <iostream>
#include "conta.hpp"
using namespace std;

class Corrente : public Conta {
public:
    Corrente();

    Corrente(int id, string nome_cliente) : Conta(id, nome_cliente) {
        this->tipo_conta = "CC";
        this->saldo = 0.0;
    }

    void atualizacaoMensal() override {
        this->saldo -= 20;
    }
};