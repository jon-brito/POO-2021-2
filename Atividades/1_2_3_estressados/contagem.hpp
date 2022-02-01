#include <iostream>
#include <vector>
#include <string>
#include <cmath>

int tot_homens(std::vector<int> fila)
{
    int homens = 0;
    for (int x : fila) {
        if (x > 0) homens += 1;
    }

    return homens;
}

int tot_mulheres(std::vector<int> fila)
{
    int mulheres = 0;
    for (int x : fila) {
        if (x < 0) mulheres += 1;
    }
    
    return mulheres;
}

float calcular_estresse_medio(std::vector<int> fila)
{
    float somatorio = 0;
    for (int x : fila) {
        somatorio += abs(x);
    }

    return somatorio / fila.size();
}

std::string mais_homens_ou_mulheres(std::vector<int> fila)
{
    if (tot_homens(fila) < tot_mulheres(fila)) return "Feminino";
    else if (tot_homens(fila) > tot_mulheres(fila)) return "Masculino";
    else return "Empate";
}

std::string qual_metade_eh_mais_estressada(std::vector<int> fila)
{
    int metade1 = 0, metade2 = 0;
    for(int i = 0; i < fila.size() / 2; i++) {
        metade1 += abs(fila.at(i));
    }

    for (int i = fila.size() / 2; i < fila.size(); i++) {
        metade2 += abs(fila.at(i));
    }

    if (metade1 > metade2) return "primeira";
    else if (metade2 > metade1) return "segunda";
    else return "empate";
}

bool homens_sao_mais_estressados_que_mulheres(std::vector<int> fila)
{
    float estresse_h = 0, estresse_m = 0;
    for (int x : fila) {
        if (x > 0) estresse_h += x;
        else if (x < 0) estresse_m += abs(x);
    }

    estresse_h  = estresse_h / tot_homens(fila);
    estresse_m = estresse_m / tot_mulheres(fila);

    if (estresse_h > estresse_m) return true;
    else return false;
}