#pragma once
#include <iostream>

class Pessoa {
private:
    std::string nome;
    int idade;

public:
    Pessoa(std::string nome = "", int idade = 0) : nome{nome}, idade{idade} {}

    std::string getNome() const {
        return this->nome;
    }

    int getIdade() const {
        return this->idade;
    }

    void descansar() const {
        std::cout << this->nome << " esta descansando\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Pessoa p) {
        os << "Nome: " << p.nome << " | Idade: " << p.idade;
        return os;
    }
};