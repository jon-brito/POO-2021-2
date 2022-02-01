#include <iostream>
#include <vector>

std::vector<int> clonar(std::vector<int> fila)
{
    std::vector<int> clone(fila);
    return clone;
}

std::vector<int> so_homens(const std::vector<int> fila)
{
    std::vector<int> homens { };
    for (int valor : fila)
        if (valor > 0)
            homens.push_back(valor);

    return homens;
}

std::vector<int> so_calmos(const std::vector<int> fila)
{
    std::vector<int> calmos { };
    for (int valor : fila)
        if (abs(valor) < 10)
            calmos.push_back(valor);

    return calmos;
}

std::vector<int> so_mulheres_calmas(const std::vector<int> fila)
{
    std::vector<int> mulheres_calmas { };
    for (int valor : fila)
        if (valor < 0 && valor > -10)
            mulheres_calmas.push_back(valor);

    return mulheres_calmas;
}