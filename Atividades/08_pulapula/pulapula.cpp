#include <iostream>
#include <vector>
#include <list>
#include <memory>

void clear_terminal()
{
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

class Crianca {
private:
    std::string nome;
    int idade;

public:
    Crianca(std::string nome = "", int idade = 0) : nome{nome}, idade{idade} {}

    std::string getNome() {
        return this->nome;
    }

    int getIdade() {
        return this->idade;
    }

    friend std::ostream& operator<<(std::ostream& os, const Crianca& crianca) {
        os << "Crianca: " << crianca.nome;
        return os;
    }
};

class Pulapula {
private:
    std::list<std::shared_ptr<Crianca>> espera;
    std::list<std::shared_ptr<Crianca>> pulando;
    
    const int idade_max;
    const int max_crianca;
    int num_criancas;

    void chamar() {      
        if (espera.front()->getIdade() > idade_max) {
            std::cout << espera.front()->getNome() << " nao eh uma crianca, sai daqui!\n";
            espera.erase(espera.begin());
            return;
        }

        std::cout << espera.front()->getNome() << " foi pular!\n";
        pulando.push_front(espera.front());
        espera.erase(espera.begin());
        this->num_criancas++;
    }

public:
    Pulapula(int max_crianca = 5, int idade_max = 10) : idade_max {idade_max}, espera {}, pulando {}, max_crianca {max_crianca}, num_criancas {0} {}

    void entrar(const std::shared_ptr<Crianca>& crianca) {
        this->espera.push_back(crianca);
    }

    void colocarPraBrincar() {
        if (num_criancas == max_crianca) {
            std::cout << "Pula pula lotado.\n";
            return;
        }

        if (espera.size() == 0) {
            std::cout << "Sem ninguem na fila de espera.\n";
        }
        
        while (num_criancas < max_crianca && espera.size() != 0) {
            chamar();
        }
    }

    void retirarCrianca() {
        if (num_criancas > 0) {
            std::cout << pulando.back()->getNome() << " saiu do pula-pula.\n";
            espera.push_back(pulando.back());
            pulando.pop_back();
            this->num_criancas--;
        } else {
            std::cout << "Sem criancas para retirar.\n";
        }
    }
    
    void retirarPorNome(std::string nome) {
        for (auto it = pulando.begin(); it != pulando.end(); ++it) {
            if ((*it)->getNome() == nome) {
                pulando.erase(it);
                num_criancas--;
                std::cout << nome << " foi pra casa.\n";
                return;
            }
        }

        for (auto it = espera.begin(); it != espera.end(); ++it) {
            if ((*it)->getNome() == nome) {
                espera.erase(it);
                num_criancas--;
                std::cout << nome << " foi pra casa.\n";
                return;
            }
        }

        std::cout << nome << " nao esta aqui.\n";
    }

    friend std::ostream& operator<<(std::ostream& os, Pulapula pp) {
        os << "\n[ ";   
        auto aux = pp.pulando;
        aux.reverse();

        for (auto value : aux) {
            os << value->getNome() << ':' << value->getIdade() << ' ';
        }

        std::cout << "] <= ";
        for (auto value : pp.espera) {
            os << value->getNome() << ':' << value->getIdade() << ' ';
        }
        std::cout << "\n\n";

        return os;
    }
};

int main() {
    clear_terminal();
    int qtd, idade_max;
    std::cout << "Digite o limite do pula pula: ";
    std::cin >> qtd;

    std::cout << "Digite a idade maxima: ";
    std::cin >> idade_max;
    
    Pulapula pula(qtd, idade_max);
    int escolha {1};

    while (escolha != 0) {        
        std::cout << "\n[1] - Entrar\n";
        std::cout << "[2] - Colocar para brincar\n";
        std::cout << "[3] - Retirar uma crianca\n";
        std::cout << "[4] - Chamar por nome\n";
        std::cout << "[5] - Mostrar relatório\n";
        std::cout << "[0] - Sair\n";
        
        std::cout << "Sua escolha: ";
        std::cin >> escolha;
        std::cout << '\n';

        if (escolha == 1) {
            clear_terminal();
            std::string nome {};
            int idade {};

            std::cout << "Digite o nome da crianca: ";
            std::cin >> nome;
            std::cout << "Digite a idade da crianca: ";
            std::cin >> idade; 

            pula.entrar(std::make_shared<Crianca>(nome, idade));
        }

        else if (escolha == 2) {
            clear_terminal();
            pula.colocarPraBrincar();
        }

        else if (escolha == 3) {
            clear_terminal();
            pula.retirarCrianca();
        }

        else if (escolha == 4) {
            clear_terminal();
            std::string nome {};
            std::cout << "Qual crianca vai chamar? ";
            std::cin >> nome;
            pula.retirarPorNome(nome);
        }

        else if (escolha == 5) {
            clear_terminal();
            std::cout << pula;
        }

        else if (escolha == 0) {
            clear_terminal();
            std::cout << "Fechando pula pula...\n";
        }

        else {
            clear_terminal();
            std::cout << "Opcao invalida.\n";
        }
    }
    
    return 0;
}