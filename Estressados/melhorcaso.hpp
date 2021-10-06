#include <iostream>
#include <vector>

int procurar_menor(std::vector<int> fila)
{
    int menor = fila.at(0);
    for (int i = 1; i < fila.size(); i++) {
        if (fila.at(i) < menor) menor = fila.at(i);
    }

    return menor;
}

int procurar_menor_pos(std::vector<int> fila)
{
    int menor = procurar_menor(fila);
    for (int i = 0; i < fila.size(); i++) {
        if (fila.at(i) == menor) return i;
    }
}

int procurar_menor_pos_a_partir(std::vector<int> fila, int posicao)
{
    if (posicao > fila.size() - 1) {
        return -1;
    } else {
        int menor = fila.at(posicao);
        int m_pos = posicao;

        for (int i = posicao + 1; i < fila.size(); i++) {
            if (fila.at(i) < menor) {
                menor = fila.at(i); 
                m_pos = i;
            }
        }

        return m_pos;
    }
}

int procurar_homem_mais_calmo_pos(std::vector<int> fila)
{
    int calmo = 99;
    for (int x : fila) {
        if (x > 0 && x < calmo) calmo = x;
    }

    for (int i = 0; i < fila.size(); i++) {
        if (fila.at(i) == calmo) return i;
    }
    return -1;
}