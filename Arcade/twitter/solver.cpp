#include <iostream>
#include <map>
#include <memory>
#include "controlador.hpp"
using namespace std;

int main() {
    Controlador sistema;

    sistema.addUsuario("user1");
    sistema.addUsuario("user2");
    sistema.addUsuario("user3");

    sistema.getUsuario("user1")->seguir(sistema.getUsuario("user2"));
    sistema.getUsuario("user1")->seguir(sistema.getUsuario("user3"));
    sistema.getUsuario("user3")->seguir(sistema.getUsuario("user2"));

    cout << sistema << '\n';

    sistema.enviarTweet("user2", "nossa o tt ta um sacooooo :(((");
    sistema.getUsuario("user1")->like(0);
    cout << sistema.getUsuario("user1")->getInbox() << '\n';

    sistema.removerUsuario("user2");
    cout << sistema.getUsuario("user1")->getInbox() << '\n';
    cout << sistema << '\n';

    return 0;
}