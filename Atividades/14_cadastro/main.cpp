#include <iostream>
#include "agencia.hpp"
using namespace std;

int main() {
    Agencia agencia;
    agencia.adicionarCliente("Andre");
    agencia.adicionarCliente("Jorge");
    agencia.adicionarCliente("Mariana");
    cout << agencia << '\n';

    agencia.depositar(1, 100);
    agencia.depositar(2, 200);
    agencia.depositar(3, 50);
    agencia.depositar(4, 300);
    agencia.retirar(4, 50);
    agencia.retirar(1, 70);
    agencia.retirar(2, 300);
    cout << agencia << '\n'; 

    agencia.tranferir(4, 6, 200);
    agencia.tranferir(1, 5, 25);
    agencia.tranferir(10, 2, 30);
    agencia.tranferir(3, 9, 10);
    cout << agencia << '\n';

    agencia.atualizacaoMensal();
    cout << agencia << '\n';

    return 0;
}