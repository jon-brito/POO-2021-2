#pragma once
#include <iostream>
#include "pessoa.hpp"

class Atleta : public Pessoa {
private:
    std::string time;
    int vitorias;
    int derrotas;

public:
    Atleta(std::string nome = "", int idade = 0, std::string time = "", int vitorias = 0, int derrotas = 0) 
    : Pessoa(nome, idade), time{time}, vitorias{vitorias}, derrotas{derrotas} {}

    std::string getTime() const {
        return this->time;
    }

    int getVitorias() const {
        return this->vitorias;
    }

    int getDerrotas() const {
        return this->derrotas;
    }

    void treinar() {
        std::cout << this->getNome() << " esta treinando\n";
    }

    void vencer() {
        std::cout << this->getNome() << " venceu uma partida\n";
        this->vitorias++;
    }

    void perder() {
        std::cout << this->getNome() << " perdeu uma partida\n";
        this->derrotas++;
    }

    friend std::ostream& operator<<(std::ostream& os, const Atleta a) {
        const Pessoa& p = a;
        os << p << " | Time: " << a.time << " | Vitorias: " << a.vitorias << " | Derrotas: " << a.derrotas;
        return os;
    }

};