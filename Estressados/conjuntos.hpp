#include <vector>
#include <cmath>

using std::vector;

vector<int> exclusivos(vector<int> fila)
{
    vector<int> vetor_exclusivos { };
    for (int valor : fila) {
        bool eh_exclusivo { true };

        for (int exclusos : vetor_exclusivos) {
            if (valor == exclusos) {
                eh_exclusivo = false;
                break;
            }
        }

        if (eh_exclusivo) {
            vetor_exclusivos.push_back(valor);
        }
    }

    return vetor_exclusivos;
}

vector<int> diferentes(vector<int> fila)
{
    vector<int> vetor_diferentes { };
    for (int valor : fila) {
        bool eh_exclusivo { true };

        for (int exclusos : vetor_diferentes) {
            if (abs(valor) == abs(exclusos)) {
                eh_exclusivo = false;
                break;
            }
        }

        if (eh_exclusivo) {
            vetor_diferentes.push_back(abs(valor));
        }
    }

    return vetor_diferentes;
}

vector<int> abandonados(vector<int> fila)
{
    vector<int> lixo { };
    int i = 0;
    
    while (i < fila.size()) {
        bool pro_lixo { true };

        for (int j { }; j < lixo.size(); j++) {
            if (fila[i] == lixo[j]) {
                pro_lixo = false;
                break;
            }
        }

        if (pro_lixo) {
            lixo.push_back(fila[i]);
            fila.erase(fila.begin() + i);
        } else {
            i++;
        }
    }

    return fila;
}