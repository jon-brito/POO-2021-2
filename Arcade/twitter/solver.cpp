#include <iostream>
#include <map>
#include <memory>
#include "controlador.hpp"
using namespace std;

int main() {
    Controlador sistema; 

    while(true) {
        try {
            string cmd {};
            cin >> cmd;

            if (cmd == "end") {
                break;
            } 
            
            else if (cmd == "add") {
                string nome {};
                cin >> nome;
                sistema.addUsuario(nome);
            } 
            
            else if (cmd == "rm") {
                string nome {};
                cin >> nome;
                sistema.removerUsuario(nome);
            }  
            
            else if (cmd == "show") {
                std::cout << sistema << '\n';
            } 
            
            else if (cmd == "follow") {
                string autor {}, receptor {};
                cin >> autor >> receptor;
                sistema.getUsuario(autor)->seguir(sistema.getUsuario(receptor));
            } 
            
            else if (cmd == "unfollow") {
                string autor {}, receptor {};
                cin >> autor >> receptor;
                sistema.getUsuario(autor)->unfollow(sistema.getUsuario(receptor));
            } 
            
            else if (cmd == "tt") {
                string nome {}, mensagem {};
                cin >> nome;
                getline(cin, mensagem);
                sistema.enviarTweet(nome, mensagem);
            } 
            
            else if (cmd == "like") {
                string nome {};
                int id;
                cin >> nome >> id;
                sistema.getUsuario(nome)->like(id);
            }
            
            else if (cmd == "timeline") {
                string nome {};
                cin >> nome;
                cout << sistema.getUsuario(nome)->getInbox();
            } 
            
            else if (cmd == "rt") {
                string nome {}, mensagem {};
                int id {};
                cin >> nome >> id;
                getline(cin, mensagem);
                sistema.enviarRetweet(nome, id, mensagem);            
            }

            else if (cmd == "clear") {
                #if defined(_WIN32) || defined(_WIN64)
                    system("cls");
                #else
                    system("clear");
                #endif
            }

            else {
                std::cout << "fail: comando invalido" << '\n';
            }

        } catch(TweetException& te) {
            cout << te.what() << endl;
        }

        cout << '\n';
    }

    return 0;
}