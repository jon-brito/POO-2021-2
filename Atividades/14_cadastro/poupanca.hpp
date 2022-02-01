#pragma once

#include <iostream>
#include "conta.hpp"
using namespace std;

class Poupanca : public Conta {
public:
    Poupanca();

    Poupanca(int id, string nome_cliente) : Conta(id, nome_cliente) {
        this->tipo_conta = "CP";
        this->saldo = 0.0;
    }

    void atualizacaoMensal() override {
        this->saldo = this->saldo + this->saldo * (1.0/100);
    }
};