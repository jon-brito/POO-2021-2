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

    map<string, shared_ptr<Usuario>>& getSeguidores() {
        return this->seguidores;
    }

    map<string, shared_ptr<Usuario>>& getSeguindo() {
        return this->seguindo;
    }

    Inbox& getInbox() {
        return this->inbox;
    }

    void seguir(shared_ptr<Usuario> other) {
        if (other == nullptr) {
            throw TweetException("erro: usuario nao cadastrado");
        }
        
        if (other->getNome() == this->nome) {
            throw TweetException("erro: nao pode dar follow em voce mesmo");
        }

        auto it = this->seguindo.find(other->getNome());
        if (it != this->seguindo.end()) {
            throw TweetException("erro: usuarios ja se seguem");
        }

        cout << this->nome << " esta seguindo " << other->getNome() << '\n';
        this->seguindo[other->getNome()] = other;
        other->seguidores[this->nome] = shared_from_this();
    }

    void unfollow(shared_ptr<Usuario> other) {
        if (other == nullptr) {
            throw TweetException("erro: usuario nao cadastrado");
        }
        
        if (other->getNome() == this->nome) {
            throw TweetException("erro: nao pode dar unfollow em voce mesmo");
        }

        auto it = this->seguindo.find(other->getNome());
        if (it == this->seguindo.end()) {
            throw TweetException("erro: usuarios nao se seguem");
        }

        cout << this->nome << " parou de seguir " << other->getNome() << '\n';
        for (auto [id, Mensagem] : this->inbox.getTimeLine()) {
            if (Mensagem->getRemetente() == other->getNome()) {
                this->inbox.getTimeLine().erase(id);
            }
        }

        this->seguindo.erase(other->getNome());
        other->seguidores.erase(this->nome);
    }

    void tweetar(shared_ptr<Mensagem> tweet) {
        this->inbox.guardarTimeLine(tweet);
        
        for (auto seguidor : this->seguidores) {
            seguidor.second->inbox.guardarTimeLine(tweet);
        }
    }

    void like(int tweetId) {
        auto time_line = inbox.getTimeLine();
        auto it = time_line.find(tweetId);

        if (it != time_line.end()) {
            it->second->like(this->nome);
            return;
        }

        throw TweetException("erro: tweet nao encontrado");
    }

    void deletar() {
        auto time_line = this->inbox.getTimeLine();
        for (auto [id, msg] : time_line) {
            if (msg->getRemetente() == this->nome) {
                msg->setDeletada();
            }
        }

        for (auto& seguidor : seguidores) {
            auto& seguindo_do_seguidor = seguidor.second->getSeguindo();
            seguindo_do_seguidor.erase(this->nome);            

            auto& seguindores_do_seguidor = seguidor.second->getSeguidores();
            seguindores_do_seguidor.erase(this->nome);    
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