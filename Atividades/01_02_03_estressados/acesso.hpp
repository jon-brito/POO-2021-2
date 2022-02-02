#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

std::vector<int> inverter_com_copia(std::vector<int> fila)
{
    std::vector<int> invertidos;
    for (int valor : fila)
        invertidos.push_back(valor * -1);

    return invertidos;
}

void inverter_inplace(std::vector<int>& fila)
{
    for (int& valor : fila)
        valor *= -1;
}

int numero_aleatorio(int i) {
    srand(time(NULL));
    return std::rand() % i;
}

void embaralhar_velhor(std::vector<int>& fila)
{
    std::random_shuffle(fila.begin(), fila.end(), numero_aleatorio);
}

int sortear(std::vector<int> fila)
{
    srand(time(NULL));
    int index {std::rand() % fila.size()};
    return fila[index];
}

void ordenar_vetor(std::vector<int>& fila)
{
    sort(fila.begin(), fila.end());
}