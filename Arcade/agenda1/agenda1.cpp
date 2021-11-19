#include "contato.hpp"

int main() {
    Contato c1("David");
    cout << c1 << '\n';

    c1.adicionar(Telefone("oi", "88"));
    c1.adicionar(Telefone("tim", "99"));
    c1.adicionar(Telefone("tim", "98"));
    c1.adicionar(Telefone("vivo", "83"));
    cout << c1 << '\n';

    c1.remover(2);
    cout << c1 << '\n';

    c1.remover(0);
    cout << c1 << '\n';

    c1.adicionar(Telefone("tim", "9a9"));
    c1.adicionar(Telefone("tim", "(85)99.99"));
    cout << c1 << '\n';

    return 0;
}