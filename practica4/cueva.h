#ifndef CUEVA_H
#define CUEVA_H
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;


class Cueva
{
private:
    int fila;
    int columna;
    int matriz[20][20];
    const int WALL = -1;
    const int EXIT = -2;
    const int ENTRANCE = -3;
public:
    Cueva();
    void crear(int fila, int columna);
    void guardar(string nombre);
    void paredesExternas();
    bool setEntrada(int fila, int columna);
    bool setSalida(int fila, int columna);
    bool leer(string nombre);
    void mostrar();
    void setPared(int fila, int columna);
    void encontrarRuta();
};

#endif // CUEVA_H
