#include "menu.h"

Menu::Menu()
{

    string op;
    do{
        system("cls");
        cout << "\n\tMapa" << endl;
        cout << "1.- Crear " << endl
             << "2.- Mostrar " << endl
             << "3.- Salir " << endl
             << ">>> ";
        getline(cin, op);
        if (op == "1")
            crearMapa();
        else if(op == "2")
            mostrarMapa();
    }while(op != "3");
}

void Menu::crearMapa()
{
    system("cls");
    int fila;
    int columna;
    string nombre;
    cout << "\n\n\tCrear mapa" << endl;
    cout << "VALORES PERMITIDOS: 3 - 20" << endl;

    cout << "Tamanio Fila: ";
    cin >> fila;
    if(!((fila >= 3 )&& (fila <= 20)))
        return;

    cout << "Tamanio Columa: ";
    cin >> columna;
    if(!(columna >= 3 && columna <= 20))
        return;
    cin.ignore();
    cout << "Ingresa nombre de la cueva: ";
    getline(cin, nombre);
    cueva.crear(fila, columna);
    entradas();
    salidas();
    string op;
    do{
        system("cls");
        cin.ignore();
        cout << "\n\tPared" << endl;
        cout << "0.- Continuar" << endl
             << "1.- Agregar pared" << endl;
        getline(cin, op);
        if(op == "1")
            pared();
    }while(op != "0");
    cueva.guardar(nombre);
}

void Menu::mostrarMapa()
{
    system("cls");
    string nombre;
    cout << "\tMostrar Mapa" << endl;
    cout << "Ingrese nombre del mapa: ";
    getline(cin, nombre);
    if(cueva.leer(nombre))
        cueva.mostrar();
    else
        cout << "Error al mostrar cueva: " << nombre << ".txt" << endl;

    system("pause");
}

void Menu::entradas()
{
    int fila;
    int columna;
    do{
        system("cls");
        cout << "\n\tEntrada" << endl;
        cueva.leer(nombre);
        cueva.mostrar();
        cout << "Ingresa Fila: ";
        cin >>fila;
        cout << "Ingresa Columna: ";
        cin >> columna;

    }while(!cueva.setEntrada(fila, columna));
}

void Menu::salidas()
{
    int fila;
    int columna;
    do{
        system("cls");
        cout << "\n\tSalida" << endl;
        cueva.leer(nombre);
        cueva.mostrar();
        cout << "Ingresa Fila: ";
        cin >>fila;
        cout << "Ingresa Columna: ";
        cin >> columna;
    }while(!cueva.setSalida(fila, columna));
}

void Menu::pared()
{
    int fila;
    int columna;

    system("cls");
    cout << "\n\tPared" << endl;
    cueva.leer(nombre);
    cueva.mostrar();
    cout << "Ingresa Fila: ";
    cin >>fila;
    cout << "Ingresa Columna: ";
    cin >> columna;
    cueva.setPared(fila, columna);
}
