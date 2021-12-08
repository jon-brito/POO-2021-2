#include <iostream>
#include "jogVolei.hpp"

int main() {
    jogVolei a("Giba", 26, "Olympikus", 12, 14, "Ponta", 17, 32, 56, 25);
    std::cout << a << "\n\n";

    a.descansar();
    a.treinar();
    a.vencer();
    a.vencer();
    a.perder();
    std::cout << a << "\n\n";

    a.fazerAce();
    a.atacar();
    a.defender();
    a.bloquear();
    a.bloquear();
    a.bloquear();
    std::cout << a << "\n\n";

    return 0;
}