#include <iostream>
#include <map>
#include <memory>
#include "controlador.hpp"
using namespace std;

int main() {
    Controlador sistema;

    sistema.addUsuario("Hugo");
    sistema.addUsuario("Henok");
    sistema.addUsuario("Freitag");
    cout << "\n";

    sistema.getUsuario("Hugo")->seguir(sistema.getUsuario("Henok"));
    sistema.getUsuario("Hugo")->seguir(sistema.getUsuario("Freitag"));
    sistema.getUsuario("Freitag")->seguir(sistema.getUsuario("Henok"));
    sistema.getUsuario("Freitag")->seguir(sistema.getUsuario("Hugo"));
    sistema.getUsuario("Henok")->seguir(sistema.getUsuario("Freitag"));
    cout << sistema << "\n";

    sistema.enviarTweet("Henok", "Bom dia, gosto de java");
    sistema.enviarTweet("Freitag", "Meu Deus, tem gente que gosta de java...");
    sistema.getUsuario("Freitag")->unfollow(sistema.getUsuario("Henok"));

    sistema.enviarTweet("Freitag", "Parei de seguir :eyes:");
    sistema.enviarTweet("Henok", "Deixaram de me seguir :sob:");
    sistema.enviarTweet("Hugo", "Meu Deus... Henok cancelado por usar java!");

    cout << sistema.getUsuario("Henok")->getInbox() << "\n";
    cout << sistema.getUsuario("Freitag")->getInbox() << "\n";
    cout << sistema.getUsuario("Hugo")->getInbox() << "\n";

    cout << sistema << '\n';

    return 0;
}