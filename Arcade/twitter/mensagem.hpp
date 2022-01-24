#pragma once

#include <iostream>
#include <set>
#include <memory>
using namespace std;

class TweetException : public exception {
    string message;
public:
    TweetException(const string& message) : 
        message(message) {
    }
    const char* what() const noexcept override {
        return message.c_str(); 
    }
};

class Mensagem {
private:
    string msg;
    string remetente;
    int id;
    set<string> likes;
    bool deletada;
    shared_ptr<Mensagem> retweet;

public:
    Mensagem(int id, string remetente, string msg) : id{id}, remetente{remetente}, msg{msg}, deletada{false}, retweet{nullptr} {}

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

    void setRetweet(shared_ptr<Mensagem> retweet) {
        this->retweet = retweet;
    }

    void like(string nome) {
        auto it = likes.find(nome);
        if (it == likes.end()) {
            likes.insert(nome);
        }
    }

    friend ostream& operator<<(ostream& os, const Mensagem& mensagem) {
        auto* proximo_retweet = &mensagem;
        int tab = 0;

        do {
            if (proximo_retweet->getDeletada()) {
                os << string(tab * 2, ' ') << " Esse tweet foi deletado.\n";
            }
            
            else {
                os << string(tab * 2, ' ') << proximo_retweet->id << " (" << proximo_retweet->remetente << ") - " << proximo_retweet->msg << " [ ";           
                for (auto& user : proximo_retweet->likes) {
                    os << user << ' ';
                }            
                os << "]\n";
            }

            proximo_retweet = proximo_retweet->retweet.get();
            tab++;

        } while (proximo_retweet != nullptr);

        return os;
    }
};