#include <vector>
#include <cmath>

using std::vector;

int apaziguado(vector<int> fila)
{
    int pacificacoes {0};
    
    if(fila.size() > 1){
        for (int i = 0; i < fila.size(); i++) {
            if (abs(fila[i]) > 80) {
                if (i == 0) {
                    if (abs(fila[i + 1] < 10)) {
                        pacificacoes++;
                    }
                } else if (i == (fila.size() - 1)) {
                    if (abs(fila[i - 1]) < 10) {
                        pacificacoes++;
                    }
                } else if (abs(fila[i + 1] < 10) || abs(fila[i - 1]) < 10) {
                    pacificacoes++;
                }
            }
        }
    }

    return pacificacoes;
}

int briga(vector<int> fila)
{
    int brigas { 0 };
    for (int i = 0; i < fila.size(); i++) {
        if (i > 0 && i < fila.size() - 1) {
            int atual { abs(fila[i]) };
            int anterior { abs(fila[i - 1]) };
            int posterior { abs(fila[i + 1]) };

            if (atual > 50 && anterior > 30 && posterior > 30) {
                brigas++;
            }
        }
    }

    return brigas;
}