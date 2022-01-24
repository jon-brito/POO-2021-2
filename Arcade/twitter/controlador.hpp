#pragma once

#include <iostream>
#include <map>
#include "usuario.hpp"
using namespace std;

class Controlador {
private:
    map<string, shared_ptr<Usuario>> usuarios;
    map<int, shared_ptr<Mensagem>> tweets;
    int nextTweetId;

    shared_ptr<Mensagem> criarTweet(string nome, string msg) {
        auto tweet = make_shared<Mensagem>(nextTweetId, nome, msg);
        this->tweets[nextTweetId] = tweet;
        nextTweetId++;

        return tweet;
    }
    

public:
    Controlador() : nextTweetId{0} {}

    shared_ptr<Usuario> getUsuario(string nome) const {
        auto it = this->usuarios.find(nome);
        if (it != usuarios.end()) {
            return it->second;
        }

        throw TweetException("erro: usuario nao cadastrado");
    }

    void addUsuario(string nome) {
        auto it = usuarios.find(nome);
        if (it != usuarios.end()) {
            throw TweetException("erro: usuario ja cadastrado");
        }

        cout << nome << " foi cadastrado(a).\n";
        auto user = make_shared<Usuario>(nome);
        this->usuarios[nome] = user;
    }

    void enviarTweet(string nome, string msg) {
        this->getUsuario(nome)->tweetar(criarTweet(nome, msg));
    }

    void enviarRetweet(string nome, int tweetId, string msg) {
        auto usuario = this->getUsuario(nome);
        auto tweet_original = usuario->getInbox().getMensagem(tweetId);

        auto retweet = criarTweet(nome, msg);
        retweet->setRetweet(tweet_original);
        this->getUsuario(nome)->tweetar(retweet);
    }

    void removerUsuario(string nome) {
        auto it = usuarios.find(nome);
        if (it != usuarios.end()) {
            it->second->deletar();
            this->usuarios.erase(nome);
                        
            cout << nome << " foi removido do sistema.\n";
            return;
        }

        throw TweetException("erro: usuario nao cadastrado");
    }

    friend ostream& operator<<(ostream& os, const Controlador& cont) {
        os << "\n---------------------------------\n";
        for (auto user : cont.usuarios) {
            os << *user.second;
        }
        os << "---------------------------------\n";

        return os;
    }
};