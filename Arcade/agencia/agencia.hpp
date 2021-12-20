#pragma once;

#include <iostream>
#include <memory>
#include <list>
#include <map>
#include "cliente.hpp"
#include "conta.hpp"
#include "poupanca.hpp"
#include "corrente.hpp"
using namespace std;

class Agencia {
private:
    int id_prox_conta;
    map<int, shared_ptr<Conta>> contas {};
    map<string, shared_ptr<Cliente>> clientes {};

public:
    Agencia() : id_prox_conta{0} {}

    void adicionarCliente(string nome) {
        auto it = clientes.find(nome);
        if (it != clientes.end()) {
            cout << "Cliente " << nome << " ja esta cadastrado(a).\n";
            return;
        }

        clientes[nome] = make_shared<Cliente>(nome);
        contas[id_prox_conta] = make_shared<Corrente>(++id_prox_conta, nome);
        contas[id_prox_conta] = make_shared<Poupanca>(++id_prox_conta, nome);
        cout << "Cliente " << nome << " foi cadastrado(a).\n";        
    }

    void depositar(int id_conta, float value) {
        auto it = contas.find(id_conta);
        if (it == contas.end()) {
            cout << "ID da conta invalido.\n";
            return;
        }

        it->second->depositar(value);
        cout << "Depositados R$" << value << " para " << it->second->getNomeCliente() << '\n';
    }

    void retirar(int id_conta, float value) {
        auto it = contas.find(id_conta);
        if (it == contas.end()) {
            std::cout << "ID da conta invalido.\n";
            return;
        }

        it->second->retirar(value);
    }

    void tranferir(int id_conta_de, int id_conta_para, float value) {
        auto it = contas.find(id_conta_de);
        auto it2 = contas.find(id_conta_para);
        if (it == contas.end() || it2 == contas.end()) {
            std::cout << "ID da conta de/para invalido(s).\n";
            return;
        }

        it->second->transferir(it2->second, value);
    }

    void atualizacaoMensal() {
        for (auto [id, conta] : contas) {
            conta->atualizacaoMensal();
        }
    }

    friend ostream& operator<<(ostream& os, const Agencia& ag) {        
        os << "\nContas: \n";
        for (auto [id, conta] : ag.contas) {
            os << *conta << '\n';
        }

        return os;
    }
};