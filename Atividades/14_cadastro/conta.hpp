#pragma once

#include <iostream>
using namespace std;

class Conta {
protected:
    int id;
    float saldo;
    string tipo_conta;
    string nome_cliente;

public:
    Conta();

    Conta(int id, string nome_cliente) : id{id}, nome_cliente{nome_cliente} {}

    void depositar(float value) {
        this->saldo += value;
    }

    void transferir(shared_ptr<Conta> other, float value) {
        if (this->saldo - value >= 0) {
            this->saldo -= value;
            other->saldo += value;

            cout << "Transferido R$" << value << " de " << this->nome_cliente
            << " para " << other->nome_cliente << "\n";
            return;
        }

        cout << "Valor excede o seu saldo\n";
    }

    void retirar(float value) {
        if (this->saldo - value >= 0) {
            this->saldo -= value;
            cout << "Retirados R$" << value << " de " << this->nome_cliente << "\n";
            return;
        }

        cout << "Valor excede seu saldo.\n";
    }

    virtual void atualizacaoMensal() = 0;

    float getSaldo() const {
        return this->saldo;
    }

    string getNomeCliente() const {
        return this->nome_cliente;
    }

    int getId() const {
        return this->id;
    }

    string getTipoConta() const {
        return this->tipo_conta;
    }

    friend ostream& operator<<(ostream& os, const Conta& c) {
        os << c.id << ":" << c.nome_cliente << ":" << c.saldo << ":" << c.tipo_conta;
        return os;
    }
};