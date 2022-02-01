#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <cstdlib>
#include "busca.hpp"
#include "melhorcaso.hpp"
#include "contagem.hpp"
#include "filter.hpp"
#include "acesso.hpp"
#include "conjuntos.hpp"
#include "manipulacao.hpp"
#include "proximidade.hpp"
#include "sequencias.hpp"
#include "grupos.hpp"
#include "allteracao.hpp"

void clear_terminal()
{
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

void mostrar_fila(std::vector<int> fila)
{
    printf("[ ");
    for (int x : fila) std::cout << x << " ";
    printf("]\n\n");
}

void modificar_fila(std::vector<int> &fila)
{
    clear_terminal();
    std::cout << "\n-> MODIFICAR FILA\n";
    
    std::cout << "Fila Anterior: ";
    mostrar_fila(fila);

    int qtd, estresse;
    std::cout << "Digite a quantidade de pessoas na fila: ";
    std::cin >> qtd;

    fila.clear();
    for (int i = 0; i < qtd; i++) {
        std::cout << "Estresse " << i + 1 << ": ";
        std::cin >> estresse;
        fila.push_back(estresse);
    }

    std::cout << '\n';
}

void busca(std::vector<int> fila)
{
    clear_terminal();
    std::cout << "\n-> BUSCA";
    mostrar_fila(fila);

    int num, posicao;
    std::cout << "Digite um valor: ";
    std::cin >> num;

    std::cout << "Digite um index: ";
    std::cin >> posicao;

    std::cout << "\n";
    std::cout << "O valor " << num << " existe: " << existe(fila, num) << '\n';
    std::cout << "O valor " << num << " aparece " << contar(fila, num) << " vez(es)" << '\n';
    std::cout << "O valor " << num << " aparece, pela primeira vez, no index: " << procurar_valor(fila, num) << '\n';
    std::cout << "O valor " << num << " aparece, pela primeira vez a partir do index "
              << posicao << ", no index: " << procurar_valor_a_partir(fila, num, posicao) << "\n\n";
}

void melhor_caso(std::vector<int> fila)
{
    clear_terminal();
    std::cout << "\n-> MELHOR CASO";
    mostrar_fila(fila);
    
    int posicao;
    std::cout << "Digite um index: ";
    std::cin >> posicao;

    std::cout << '\n';
    std::cout << "Menor valor: " << procurar_menor(fila) << '\n';
    std::cout << "Posicao do menor valor: " << procurar_menor_pos(fila) << '\n';
    std::cout << "Posicao do menor valor a partir do index " << posicao << ": " << procurar_menor_pos_a_partir(fila, posicao) << '\n';
    std::cout << "Posicao do homem mais calmo: " << procurar_homem_mais_calmo_pos(fila) << "\n\n";
}

void contagem(std::vector<int> fila)
{
    clear_terminal();
    std::cout << "\n->CONTAGEM";    
    mostrar_fila(fila);

    printf ("Estresse medio da fila: %.2f\n", calcular_estresse_medio(fila));
    std::cout << "Genero que mais aparece na fila: " << mais_homens_ou_mulheres(fila) << '\n';
    std::cout << "Metade mais estressada da fila: " << qual_metade_eh_mais_estressada(fila) << '\n';
    std::cout << "Os homens sao mais estressados que as mulheres? " << homens_sao_mais_estressados_que_mulheres(fila) << "\n\n";
}

void filter(std::vector<int> fila)
{
    clear_terminal();
    std::cout << "Fila clone: ";
    mostrar_fila(clonar(fila));

    std::cout << "Fila apenas com homens: ";
    mostrar_fila(so_homens(fila));

    std::cout << "Fila apenas com calmos: ";
    mostrar_fila(so_calmos(fila));

    std::cout << "Fila apenas com mulheres calmas: ";
    mostrar_fila(so_mulheres_calmas(fila));
}

void acesso(std::vector<int>& fila)
{
    clear_terminal();

    int escolha { };
    std::cout << "Deseja ordenar/embaralhar/inverter fila [1/2/3]? ";
    std::cin >> escolha;

    clear_terminal();

    std::cout << "Fila normal: ";
    mostrar_fila(fila);

    std::cout << "Fila com valores invertidos: ";
    mostrar_fila(inverter_com_copia(fila));

    if (escolha == 1) {
        std::cout << "Sua fila foi ordenada: ";
        ordenar_vetor(fila);
        mostrar_fila(fila);
    } else if (escolha == 2) {
        std::cout << "Sua fila foi embaralhada: ";
        embaralhar_velhor(fila);
        mostrar_fila(fila);
    } else if (escolha == 3) {
        std::cout << "Sua fila teve os valores invertidos: ";
        inverter_inplace(fila);
        mostrar_fila(fila);
    }

    std::cout << "Valor sorteado da fila: " << sortear(fila) << "\n\n";
}

void conjuntos(std::vector<int> fila)
{
    clear_terminal();
    std::cout << "Fila normal: ";
    mostrar_fila(fila);

    std::cout << "Fila exclusiva por valor: ";
    mostrar_fila(exclusivos(fila));

    std::cout << "Fila exclusiva por estresse: ";
    mostrar_fila(diferentes(fila));

    std::cout << "Fila dos abandonados: ";
    mostrar_fila(abandonados(fila));
}

void manipulacao(std::vector<int> fila)
{
    clear_terminal();
    std::cout << "Fila: ";
    mostrar_fila(fila);

    std::cout << "Sozinhos: ";
    mostrar_fila(sozinhos(fila));

    std::cout << "Maior quantidade de ocorrencias: " << mais_ocorrencias(fila) << '\n';

    std::cout << "Numeros mais recorrentes: ";
    mostrar_fila(mais_recorrentes(fila));
}

void proximidade(std::vector<int> fila)
{
    clear_terminal();
    std::cout << "Fila: ";
    mostrar_fila(fila);

    std::cout << "Quantidade de pacificacoes: " << apaziguado(fila) << "\n\n";
    std::cout<< "Quantidade de brigas na fila: " << briga(fila) << "\n\n";
}

void sequencias(std::vector<int> fila)
{
    clear_terminal();
    std::cout << "Fila: ";
    mostrar_fila(fila);

    std::cout << "Quantidade de times: " << quantos_times(fila) << "\n\n";
    std::cout << "Maior time: ";
    mostrar_fila(maior_time(fila));
    std::cout << "Quantidade de pessoas sem time: " << sem_time(fila) << "\n\n";
}

void grupos(std::vector<int> fila)
{
    clear_terminal();
    std::cout << "Fila: ";
    mostrar_fila(fila);

    std::cout << "Numero de possiveis casais: " << casais(fila) << "\n\n";

    std::cout << "Numero de possiveis trios: " << trios(fila) << "\n\n";
}

void alteracao(std::vector<int>& fila)
{
    clear_terminal();
    mostrar_fila(fila);

    int escolha { };
    std::cout << "Remover / Inserir / Dancar [1/2/3]\n" << "Sua escolha: ";
    std::cin >> escolha;

    if (escolha == 1)
        remover(fila);
    else if (escolha == 2)
        inserir(fila);
    else if (escolha == 3)
        dancar(fila);
    else
        std::cout << "Nada modificado!\n\n";

    std::cout << "Nova fila: ";
    mostrar_fila(fila);

   
}

int main()
{
    clear_terminal();
    std::cout.setf(std::ios::boolalpha);
    std::vector<int> fila = {1, 1, 1, 5, -1, 6, 8, 1, 1, -5};

    int escolha = 1;
    while (escolha != 0) {
        std::cout << "-=-=-FILA DOS ESTRESSADOS-=-=- \n";
        std::cout << "[01] - Modificar Fila \n";
        std::cout << "[02] - Busca \n";
        std::cout << "[03] - Melhor Caso \n";
        std::cout << "[04] - Contagem \n";
        std::cout << "[05] - Filter \n";
        std::cout << "[06] - Acesso \n";
        std::cout << "[07] - Conjuntos \n";
        std::cout << "[08] - Manipulacao \n";
        std::cout << "[09] - Proximidade \n";
        std::cout << "[10] - Sequencias \n";
        std::cout << "[11] - Grupos \n";
        std::cout << "[12] - Alteração \n";
        std::cout << "[00] - Sair \n";

        std::cout << "Sua escolha: ";
        std::cin >> escolha;

        switch (escolha) {
            case 1:
                modificar_fila(fila);
                break;
            case 2:
                busca(fila);
                break;
            case 3:
                melhor_caso(fila);
                break;
            case 4:
                contagem(fila);
                break;
            case 5:
                filter(fila);
                break;
            case 6:
                acesso(fila);
                break;
            case 7:
                conjuntos(fila);
                break;
            case 8:
                manipulacao(fila);
                break;
            case 9:
                proximidade(fila);
                break;
            case 10:
                sequencias(fila);
                break;
            case 11:
                grupos(fila);
                break;
            case 12:
                alteracao(fila);
                break;
        }
    }
    std::cout << "\nSaindo . . .\n";

    return 0;
}