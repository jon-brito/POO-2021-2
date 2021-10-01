#include <iostream>
#include <cmath>
#include <vector>
#include <string>

//Funcoes Busca
bool existe(std::vector<int> fila, int numero)
{
    for (int x : fila) {
        if (x == numero) return 1;
    }
    return 0;
}

int contar(std::vector<int> fila, int numero)
{
    int quantidade = 0;
    for (int x : fila) {
        if (x == numero) quantidade++;
    }
    return quantidade;
}

int procurar_valor(std::vector<int> fila, int numero)
{
    for (int i = 0; i < fila.size(); i++) {
        if (fila.at(i) == numero) return i;
    }
    return -1;
}

int procurar_valor_a_partir(std::vector<int> fila, int numero, int posicao)
{
    if (posicao > fila.size() - 1) {
        return -1;
    } else {
        for (int i = posicao; i < fila.size(); i++) {
            if (fila.at(i) == numero) return i;
        }

        return -1;
    }    
}

//Funcoes Melhor Caso
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

//Funcoes Contagem
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
    int total_h = 0, total_m = 0;
    for (int x : fila) {
        if (x > 0) total_h++;
        else if (x < 0) total_m++;
    }

    if (total_m > total_h) return "mulheres";
    else if (total_h > total_m) return "homens";
    else return "empate";
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
    int estresse_h = 0, estresse_m = 0;
    for (int x : fila) {
        if (x > 0) estresse_h += x;
        else if (x < 0) estresse_m += abs(x);
    }

    if (estresse_h > estresse_m) return true;
    else return false;
}


//Funcoes de Menu
void mostrar_fila(std::vector<int> fila)
{
    printf("\n[ ");
    for (int x : fila) std::cout << x << " ";
    printf("]\n\n");
}

void busca(std::vector<int> fila)
{
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
    std::cout << "O valor " << num << " aparece, pela primeira vez apos o index "
              << posicao << ", no index: " << procurar_valor_a_partir(fila, num, posicao) << "\n\n";
}

void melhor_caso(std::vector<int> fila)
{
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
    std::cout << "\n->CONTAGEM";    
    mostrar_fila(fila);
    
    printf ("Estresse medio da fila: %.2f\n", calcular_estresse_medio(fila));
    std::cout << "Genero que mais aparece na fila: " << mais_homens_ou_mulheres(fila) << '\n';
    std::cout << "Metade mais estressada da fila: " << qual_metade_eh_mais_estressada(fila) << '\n';
    std::cout << "Os homens sao mais estressados que as mulheres? " << homens_sao_mais_estressados_que_mulheres(fila) << "\n\n";
}

int main()
{
    std::cout.setf(std::ios::boolalpha);
    std::vector<int> fila = {-51, 99, 1, -50, -1, -99};

    int escolha = 1;
    while (escolha != 0) {
        std::cout << "-=-=-FILA DOS ESTRESSADOS-=-=- \n";
        std::cout << "[1] - Busca \n";
        std::cout << "[2] - Melhor Caso \n";
        std::cout << "[3] - Contagem \n";
        std::cout << "[0] - Sair :( \n";

        std::cout << "Sua escolha: ";
        std::cin >> escolha;

        switch (escolha) {
        case 1:
            busca(fila);
            break;
        case 2:
            melhor_caso(fila);
            break;
        case 3:
            contagem(fila);
            break;
        }
    }
    std::cout << "Saindo . . . \n";
}