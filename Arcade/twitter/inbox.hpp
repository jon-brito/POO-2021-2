#pragma once

#include <iostream>
#include <map>
#include <memory>
#include "mensagem.hpp"
using namespace std;

class Inbox {
private:
    string nome_usuario;
    map<int, shared_ptr<Mensagem>> time_line;

public:
    Inbox() {}

    void setNome(string nome_usuario) {
        this->nome_usuario = nome_usuario;
    }

    map<int, shared_ptr<Mensagem>>& getTimeLine() {
        return this->time_line;
    }

    void guardarTimeLine(shared_ptr<Mensagem> tweet) {
        this->time_line[tweet->getId()] = tweet;
    }

    void deletarApagadas(const vector<int>& id_deletados) {
        for (auto id : id_deletados) {
            this->time_line.erase(id);
        }
    }

    friend ostream& operator<<(ostream& os, Inbox& inbox) {
        vector<int> id_deletados {};

        os << "\n=========================================\n";
        os << "Ibox do(a) " << inbox.nome_usuario << '\n';
        for (auto [num, msg] : inbox.time_line) {
            if (msg->getDeletada()) {
                id_deletados.push_back(num);
            }
            
            else {
                os << num << ' ' << *msg;
            }
            
        } 
        os << "=========================================\n";

        inbox.deletarApagadas(id_deletados);
        return os;
    }
};