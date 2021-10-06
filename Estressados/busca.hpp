#include <iostream>
#include <vector>

bool existe(std::vector<int> fila, int numero)
{
    for (int x : fila) {
        if (x == numero) return 1;
    }
    return 0;
}

int contar(std::vector<int> fila, int numero)
{
    int quantidade = 0;
    for (int x : fila) {
        if (x == numero) quantidade++;
    }
    return quantidade;
}

int procurar_valor(std::vector<int> fila, int numero)
{
    for (int i = 0; i < fila.size(); i++) {
        if (fila.at(i) == numero) return i;
    }
    return -1;
}

int procurar_valor_a_partir(std::vector<int> fila, int numero, int posicao)
{
    if (posicao > fila.size() - 1) {
        return -1;
    } else {
        for (int i = posicao; i < fila.size(); i++) {
            if (fila.at(i) == numero) return i;
        }

        return -1;
    }    
}