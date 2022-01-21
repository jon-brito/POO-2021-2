#include <iostream>
#include <map>
#include <memory>
#include "controlador.hpp"
using namespace std;

int main() {
    Controlador sistema;

    sistema.addUsuario("goku");
    sistema.addUsuario("sara");
    sistema.addUsuario("tina");

    cout << sistema << endl;

    sistema.getUsuario("goku")->seguir(sistema.getUsuario("sara"));
    sistema.getUsuario("goku")->seguir(sistema.getUsuario("tina"));
    sistema.getUsuario("sara")->seguir(sistema.getUsuario("tina"));

    cout << sistema << endl;

    sistema.enviarTweet("sara", "hoje estou triste");
    sistema.enviarTweet("tina", "ganhei chocolate");
    sistema.enviarTweet("sara", "partiu ru");
    sistema.enviarTweet("tina", "chocolate ruim");
    sistema.enviarTweet("goku", "internet maldita");

    cout << sistema.getUsuario("goku")->getInbox() << endl;
    cout << sistema.getUsuario("tina")->getInbox() << endl;
    cout << sistema.getUsuario("sara")->getInbox() << endl;

    sistema.getUsuario("sara")->like(1);
    sistema.getUsuario("goku")->like(1);
    sistema.getUsuario("sara")->like(3);

    cout << sistema.getUsuario("sara")->getInbox() << endl;
    cout << sistema.getUsuario("goku")->getInbox() << endl;

    sistema.getUsuario("goku")->unfollow(sistema.getUsuario("tina"));
    cout << sistema << endl;
    cout << sistema.getUsuario("goku")->getInbox() << endl;

    sistema.enviarRetweet("sara", 3, "olha goku, ela nao gostou do seu chocolate");
    cout << sistema.getUsuario("sara")->getInbox() << endl;
    cout << sistema.getUsuario("goku")->getInbox() << endl;

    sistema.getUsuario("tina")->seguir(sistema.getUsuario("sara"));
    cout << sistema << endl;

    sistema.removerUsuario("tina");
    cout << sistema << endl;

    cout << sistema.getUsuario("goku")->getInbox() << endl;
    cout << sistema.getUsuario("sara")->getInbox() << endl;

    return 0;
}