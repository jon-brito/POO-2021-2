#include <vector>

using std::vector;

// int times_aux(vector<int>& fila, int sexo_time_atual, int membros)
// {
//     if (fila.size() == 0) {
//         return membros;
//     } 

//     int sexo { fila[0] > 0 };
//     if (sexo != sexo_time_atual) {
//         return membros;
//     } 

//     fila.erase(fila.begin());
//     return times_aux(fila, sexo, ++membros);
// }

// int quantos_times(const vector<int> fila)
// {
//     vector<int> fila_aux {fila};
//     int times { 0 };

//     while(fila_aux.size()) {
//         int sexo { fila_aux[0] > 0 };
//         int membros = times_aux(fila_aux, sexo, 0);
//         if (membros > 1) ++times;
//     }

//     return times;
// }

// int sem_time(vector<int> fila)
// {
//     vector<int> fila_aux {fila};
//     int sem_time { 0 };

//     while(fila_aux.size()) {
//         int sexo { fila_aux[0] > 0 };
//         int membros = times_aux(fila_aux, sexo, 0);
//         if (membros == 1) ++sem_time;
//     }

//     return sem_time;
// }

int homem_mulher(int num)
{
    return num > 0;
}

vector<vector<int>> times(vector<int> fila)
{
    int sexo { homem_mulher(fila[0]) }, times_qtd { 0 };
    vector<vector<int>> matriz_times(fila.size());

    for (int i = 0; i < fila.size(); i++) {
        if (homem_mulher(fila[i]) == sexo) {
            matriz_times[times_qtd].push_back(fila[i]);
        } else {
            times_qtd++;
            matriz_times[times_qtd].push_back(fila[i]);
            sexo = homem_mulher(fila[i]);
        }
    }

    matriz_times.resize(times_qtd + 1);

    return matriz_times;
}

int quantos_times(vector <int> fila)
{
    auto matriz_times { times(fila) };
    int cont { 0 };

    for (auto linha : matriz_times) {
        if (linha.size() >= 2) {
            cont++;
        }
    }

    return cont;
}

vector<int> maior_time(vector <int> fila)
{
    auto matriz_times { times(fila) };
    int maior { 0 };
    vector<int> timao {};

    for (auto time : matriz_times) {
        if (time.size() > maior) {
            maior = time.size();
            timao = time;
        }
    }

    return timao;
}

int sem_time(vector<int> fila)
{
    auto matriz_times { times(fila) };
    int alones { 0 };    

    for (auto time : matriz_times) {
        if (time.size() == 1) {
            alones++;
        }
    }

    return alones;
}