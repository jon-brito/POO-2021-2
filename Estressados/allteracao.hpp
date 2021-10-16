#include <vector>
#include <iostream>

using std::vector;

void remover(vector<int>& fila)
{
    int estresse { };
    std::cout << "Digite um estresse para remover: ";
    std::cin >> estresse;

    for (auto i = fila.begin(); i != fila.end(); i++) {
        if (*i == estresse) {
            fila.erase(i);
            return;
        }
    }

    std::cout << "Estresse inexistente\n\n";
}

void inserir(vector<int>& fila)
{
    int posicao { }, estresse { };
    std::cout << "Digite um estresse para ser inserido: ";
    std::cin >> estresse;

    std::cout << "Digite o index para inserir o estresse: ";
    std::cin >> posicao;


    if(posicao >= 0 && posicao <= fila.size()) {
        auto i = fila.begin() + posicao;
        fila.insert(i, estresse);
    } else {
        std::cout << "Posicao invalida\n\n";
    }
}

void dancar(vector<int>& fila)
{
    int existe_par {1};

    while (existe_par) {
        existe_par = 0;
        if (fila.size() >= 2) {
            for (int i = 0; i < fila.size() - 1; i++) {
                if (abs(fila[i]) == abs(fila[i + 1])) {
                    fila.erase(fila.begin() + i);
                    fila.erase(fila.begin() + i);
                    existe_par = 1;
                    break;
                }
            }
        }
    }
}