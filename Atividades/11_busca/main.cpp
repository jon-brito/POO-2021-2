#include "agenda.hpp"

int main() {    
    Agenda agenda;

    Contato c1("Ana"), c2("Paula"), c3("Gilda"), c4("Suzi"), c5 ("Virginia"), c6("Paula");
    c1.adicionar(Telefone("tim", "111"));         //Contatos Novos
    c1.adicionar(Telefone("claro", "(88).999"));
    c2.adicionar(Telefone("oi", "52222"));
    c3.adicionar(Telefone("vivo", "996"));
    c3.adicionar(Telefone("oi","55432"));
    c4.adicionar(Telefone("oi", "1557"));
    c5.adicionar(Telefone("vivo", "13141422"));
    c5.adicionar(Telefone("oi", "88164"));
    c5.adicionar(Telefone("tim", "525425"));
    c6.adicionar(Telefone("vivo", "8888"));       //Contato Repetido

    list<Contato> contatos {c1,c2,c3,c4,c5,c6};   //Adicionando lista de contatos
    agenda.adicionarContato(contatos);
    cout << agenda << '\n';

    agenda.remover("Virginia", 1);                //Removendo um telefone
    agenda.remover("Suzi");                       //Removendo um contato
    cout << agenda << '\n';

    agenda.busca(88);                             //Contato com numeros 88
    agenda.busca("i");                            //Contatos com "i"

    return 0;
}