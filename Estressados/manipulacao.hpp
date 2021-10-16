#include <vector>
#include <cmath>

using std::vector;

bool uma_vez(vector<int> fila, int num)
{
    int contador {0};
    for (int valor : fila) {
        if (abs(valor) == abs(num)) {
            contador++;
        }
        if (contador > 1) {
            return false;
        }
    }
    return true;
}

vector<int> sozinhos(vector<int> fila)
{
    vector<int> sozin {};
    for (int estress : fila) {
        if (uma_vez(fila, estress)) {
            sozin.push_back(abs(estress));
        }
    }
    return sozin;
}

int contar_abs(vector<int> fila, int num)
{
    int contador {0};
    for (int estress : fila) {
        if (abs(estress) == abs(num)){
            contador++;
        }
    }
    return contador;
}

int mais_ocorrencias(vector<int> fila)
{
    int maior_ocorrencia {0};
    for (int estress : fila) {
        if (contar_abs(fila, estress) > maior_ocorrencia) {
            maior_ocorrencia = contar_abs(fila, estress);
        }
    }

    return maior_ocorrencia;
}

vector<int> mais_recorrentes (vector<int> fila)
{
    int maior_ocorrencia { mais_ocorrencias(fila) };
    vector<int> recorrentes { };

    for (auto i = fila.begin(); i != fila.end(); i++) {
        if (contar_abs(fila, *i) == maior_ocorrencia) {
            recorrentes.push_back(abs(*i));
        }
    }

    return exclusivos(recorrentes);
}