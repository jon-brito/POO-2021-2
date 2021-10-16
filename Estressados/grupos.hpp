#include <vector>
#include <cmath>
using std::vector;

int posicao_par(vector<int> fila, int num, int index)
{
    for (int i = index; i < fila.size(); i++) {
        if (fila[i] == -1 * num) return i;
    }
    return 0;
}

int casais(vector<int> fila)
{
    int casais { 0 };
    for (int i = 0; i < fila.size(); i++) {
        int par { posicao_par(fila, fila[i], i) };
        if (par) {
            fila.erase(fila.begin() + par);
            fila.erase(fila.begin() + i);
            casais++;
            i--;
        }
    }

    return casais;
}

int posicao_abs(vector<int> fila, int num, int index)
{
    for (int i = index; i < fila.size(); i++) {
        if (abs(fila[i]) == abs(num)) return i;
    }
    return 0;
}

int trios(vector<int> fila)
{
    int trios { 0 };

    if (fila.size() > 2) {
        for (int i = 0; i < fila.size(); i ++) {
            int primeiro_par { posicao_abs(fila, fila[i], i + 1) };
            if (primeiro_par) {
                int segundo_par { posicao_abs(fila, fila[i], primeiro_par + 1) };
                if (segundo_par) {
                    fila.erase(fila.begin() + segundo_par);
                    fila.erase(fila.begin() + primeiro_par);
                    i--;
                    trios++;
                }
            }
        }
    }

    return trios;
}