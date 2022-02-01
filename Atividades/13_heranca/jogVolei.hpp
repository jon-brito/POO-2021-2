#pragma once
#include <iostream>
#include "atleta.hpp"

class jogVolei : public Atleta {
private:
    std::string posicao;
    int aces;
    int bloqueios;
    int ataques;
    int defesas;

public:
    jogVolei(std::string n = "", int i = 0, std::string t = "", int v = 0, int d = 0, std::string p = "", int ac = 0, int bloq = 0, int at = 0, int def = 0)
    : Atleta(n, i, t, v, d), posicao{p}, aces{ac}, bloqueios{bloq}, ataques{at}, defesas{def} {}

    std::string getPosicao() const {
        return this->posicao;
    }

    int getAces() const {
        return this->aces;
    }

    int getBloqueios() const {
        return this->bloqueios;
    }

    int getAtaques() const {
        return this->ataques;
    }

    int getDefesas() const {
        return this->defesas;
    }

    void fazerAce() {
        this->aces++;
    }

    void bloquear() {
        this->bloqueios++;
    }

    void atacar() {
        this->ataques++;
    }

    void defender() {
        this->defesas++;
    }

    friend std::ostream& operator<<(std::ostream& os, const jogVolei& j) {
        const Atleta& a = j;
        os << a << '\n' << "(VOLEI) -> Posicao: " << j.posicao << " | Aces:" << j.aces;
        os << " | Bloqueios: " << j.bloqueios << " | Ataques: "<< j.ataques << " | Defesas: " << j.defesas;
        return os;
    }
};