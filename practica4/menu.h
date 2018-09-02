#ifndef MENU_H
#define MENU_H
#include <iostream>
#include "cueva.h"
using namespace std;


class Menu
{
private:
    Cueva cueva;
    string nombre;
public:
    Menu();
    void crearMapa();
    void mostrarMapa();
    void entradas();
    void salidas();
    void pared();
};

#endif // MENU_H
