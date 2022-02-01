#include "agenda.hpp"

int main() {    
    Agenda agenda;

    vector<Telefone> t1{{"oi","123"}, {"tim", "333"}};
    Contato c1("Jorge", t1);

    vector<Telefone> t2{{"oi","123"}, {"tim", "333"}, {"oi", "444"}};
    Contato c2("Jorge", t2);

    vector<Telefone> t3{{"oi","123"}, {"tim", "333"}, {"oi", "444"}};
    Contato c3("Ana", t2);

    Contato c4("Hugo");
    c4.adicionar(vector<Telefone>{{"oi","123"}, {"tim", "444"}});
    agenda.adicionarContato(vector<Contato>({c1, c2, c3, c4}));

    cout << agenda << "\n";

    agenda.remover("Hugo");
    cout << agenda << "\n";

    agenda.buscar("a");
    agenda.buscar(4);

    return 0;
}