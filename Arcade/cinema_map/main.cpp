#include <iostream>
#include "cinema.hpp"
using namespace std;

int main() {
    Cinema cine(4);

    cine.reservar("jorge", "123", 0);
    cine.reservar("marcos", "1412", 2);
    cine.reservar("marcos", "1412", 2);
    cine.reservar("ana", "1412", 2);
    cout << cine << "\n\n";

    cine.reservar("maria", "5233", 6);
    cine.reservar("mariana", "543", 1);
    cine.reservar("paula", "331", 2);
    cine.reservar("gustavo", "123", 3);
    cout << cine << "\n\n";

    cine.cancelar("marcos");
    cine.cancelar("sena");
    cout << cine << "\n\n";

    return 0;
}