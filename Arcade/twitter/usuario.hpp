#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include "inbox.hpp"
using namespace std;

class Usuario : public enable_shared_from_this<Usuario> {
private:
    string nome;
    map<string, shared_ptr<Usuario>> seguidores;
    map<string, shared_ptr<Usuario>> seguindo;
    Inbox inbox;

public:
    Usuario(string nome) : nome{nome} {
        this->inbox.setNome(nome);
    }

    string getNome() const {
        return this->nome;
    }

    map<string, shared_ptr<Usuario>> getSeguidores() {
        return this->seguidores;
    }

    Inbox getInbox() {
        return this->inbox;
    }

    void seguir(shared_ptr<Usuario> other) {
        if (other == nullptr) {
            cout << "Usuario nao cadastrado.\n";
            return;
        }
        
        if (other->getNome() == this->nome) {
            cout << "Nao tem como se auto-seguir... ou tem?\n";
            return;
        }

        auto it = this->seguindo.find(other->getNome());
        if (it != this->seguindo.end()) {
            cout << this->nome << " ja segue " << other->getNome() << '\n';
            return;
        }

        cout << this->nome << " esta seguindo " << other->getNome() << '\n';
        this->seguindo[other->getNome()] = other;
        other->seguidores[this->nome] = shared_from_this();
    }

    void unfollow(shared_ptr<Usuario> other) {
        if (other == nullptr) {
            cout << "Usuario nao cadastrado.\n";
            return;
        }
        
        if (other->getNome() == this->nome) {
            cout << "Nao tem como se auto-deseguir... ou tem?\n";
            return;
        }

        cout << this->nome << " parou de seguir " << other->getNome() << '\n';
        this->seguindo.erase(other->getNome());
        other->seguidores.erase(this->nome);
    }

    void tweetar(shared_ptr<Mensagem> tweet) {
        this->inbox.guardarTimeLine(tweet);
        
        for (auto seguidor : this->seguidores) {
            seguidor.second->inbox.guardarTimeLine(tweet);
        }
    }

    friend ostream& operator<<(ostream& os, const Usuario& user) {
        os << "* " << user.getNome() << '\n';
        
        os << "       seguidores: [ ";
        for (auto [nome, usuario] : user.seguidores) {
            os << nome << ' ';
        }

        os << "]\n       seguindo  : [ ";
        for (auto [nome, usuario] : user.seguindo) {
            os << nome << ' ';
        }        
        os << "]\n";

        return os;
    }
};