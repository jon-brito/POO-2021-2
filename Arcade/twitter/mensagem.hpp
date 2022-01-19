#pragma once

#include <iostream>
#include <set>
using namespace std;

class Mensagem {
private:
    string msg;
    string remetente;
    int id;
    set<string> likes;

public:
    Mensagem(int id, string remetente, string msg) : id{id}, remetente{remetente}, msg{msg} {}

    int getId() const {
        return this->id;
    }

    void like(string nome) {
        auto it = likes.find(nome);
        if (it == likes.end()) {
            likes.insert(nome);
        }
    }

    friend ostream& operator<<(ostream& os, const Mensagem& mensagem) {
        os << "(" << mensagem.remetente << ") - " << mensagem.msg << '\n';
        return os;
    }

};