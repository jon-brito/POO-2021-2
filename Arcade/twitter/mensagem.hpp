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
    bool deletada;

public:
    Mensagem(int id, string remetente, string msg) : id{id}, remetente{remetente}, msg{msg}, deletada{false} {}

    int getId() const {
        return this->id;
    }

    string getRemetente() const {
        return this->remetente;
    }

    bool getDeletada() const {
        return this->deletada;
    }

    void setDeletada() {
        this->deletada = true;
    }

    void like(string nome) {
        auto it = likes.find(nome);
        if (it == likes.end()) {
            likes.insert(nome);
        }
    }

    friend ostream& operator<<(ostream& os, const Mensagem& mensagem) {
        os << "(" << mensagem.remetente << ") - " << mensagem.msg;
        
        os << " [ ";
        for (auto user : mensagem.likes) {
            os << user << ' ';
        }
        os << "]\n";

        return os;
    }

};