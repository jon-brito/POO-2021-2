#pragma once

#include "cliente.hpp"
#include <iostream>
#include <memory>
#include <map>

using namespace std;

class Cinema {
private:
    map<int, shared_ptr<Cliente>> cadeiras;
    const int qtd_cadeiras;
    int sentados;

public:
    Cinema(int qtd_cadeiras) : qtd_cadeiras{qtd_cadeiras}, sentados{0} {}

    void reservar(string nome, string telefone, int index) {
        if (qtd_cadeiras == sentados) {
            cout << "Cinema lotado.\n";
            return;
        }

        if (index < 0 || index >= qtd_cadeiras) {
            cout << "Index invalido.\n";
            return;
        }

        for (auto& [index, cliente] : cadeiras) {
            if (cliente != nullptr && cliente->getNome() == nome) {
                cout << nome << " ja esta no cinema.\n";
                return;
            }
        }

        if (cadeiras[index] != nullptr) {
            cout << "Cadeira ja esta ocupada.\n";
            return;
        }

        auto cliente = make_shared<Cliente>(nome, telefone);
        cadeiras[index] = cliente;

        cout << nome << " entrou no cinema.\n";
        this->sentados++;
    }

    void cancelar(string nome) {
        for (auto& [index, cliente] : cadeiras) {
            if (cliente->getNome() == nome) {
                cadeiras.erase(index);
                cout << nome << " saiu do cinema.\n";
                return;
            }
        }

        cout << nome << " nao esta no cinema.\n";
    }

    friend ostream& operator<<(ostream& os, const Cinema& cinema) {        
        for (int i = 0; i < cinema.qtd_cadeiras; i++) {
            auto it = cinema.cadeiras.find(i);

            if (it != cinema.cadeiras.end()) {
                os << "[" << it->first << ":" << it->second->getNome() << "] ";
            } else {
                os << "[- - - - -] ";
            }
        }

        return os;
    }

};