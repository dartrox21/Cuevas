#include "cueva.h"
Cueva::Cueva()
{

}

void Cueva::crear(int fila, int columna)
{

    for (int x = 0; x < fila; x++) {
        for (int y = 0; y < columna; y++) {
            this->matriz[x][y] = 0;
        }
    }

    this->fila = fila;
    this->columna = columna;
    paredesExternas();

}

void Cueva::guardar(string nombre)
{
    ofstream file(nombre + ".txt", ios::out);
    file.write((char*)this, sizeof(*this));
    file.close();
}

/*
 * Este método funciona para poner las paredes externas
 * de la matriz
*/

void Cueva::paredesExternas()
{
    for (int x = 0; x < fila; x++) {
        if (x == 0 || x == fila -1) {
            for (int y = 0; y < columna; ++y) {
                matriz[x][y] = WALL;
            }
        }
        matriz[x][0] = WALL;
        matriz[x][columna-1] = WALL;
    }
}

bool Cueva::setEntrada(int fila, int columna)
{
    if (fila >= this->fila || columna >= this->columna)
        return false;
    else if((fila == 0 && columna == 0) ||
            (fila == this->fila-1 && columna == this->columna-1))

        return false;
    else if((fila == 0 && columna == this->columna-1) ||
            (fila == this->fila-1 && columna == 0))
        return false;
    else if((fila > 0 && fila < this->fila-1) &&
            (columna > 0 && columna < this->columna-1))
        return false;
    else{
        matriz[fila][columna] = ENTRANCE;
        return true;
    }
}

bool Cueva::setSalida(int fila, int columna)
{
    if (fila >= this->fila || columna >= this->columna)
        return false;
    else if((fila == 0 && columna == 0) ||
            (fila == this->fila-1 && columna == this->columna-1))

        return false;
    else if((fila == 0 && columna == this->columna-1) ||
            (fila == this->fila-1 && columna == 0))
        return false;
    else if((fila > 0 && fila < this->fila-1) &&
            (columna > 0 && columna < this->columna-1))
        return false;
    else{
        matriz[fila][columna] = EXIT;
        return true;
    }

}

bool Cueva::leer(string nombre)
{
    ifstream file(nombre + ".txt", ios::in);
    if(!file.is_open())
        return false;
    else {
        while (!file.eof()) {
            file.read((char*)this, sizeof(*this));
            if(file.eof()) break;
        }
    }
    file.close();
    return true;
}

void Cueva::mostrar()
{
    cout << "   ";
    for (int x = 0; x < this->columna; x++) {
        cout << x << " ";

    }
    cout << endl;
    for (int x = 0; x < this->fila; x++){
        cout << x << " ";
        if(x < 10) cout << " ";
        for (int y = 0; y < this->columna; y++){
            if(y >= 10) cout << " ";
            if(this->matriz[x][y] == WALL)
                cout << "*";
            else if(this->matriz[x][y] == 0)
                cout << " ";
            else if(this->matriz[x][y] == EXIT)
                cout << "S";
            else if(this->matriz[x][y] == ENTRANCE)
                cout << "E";
            else if(this->matriz[x][y] > 0 )
                cout << matriz[x][y];
            cout << " ";
        }
        cout << endl;
    }
}
void Cueva::setPared(int fila, int columna)
{
    if(fila >= this->fila || columna >= this->columna)
        cout << "\nError: Fila\\Columna invalida" << endl;
    else if(matriz[fila][columna] == EXIT ||
            matriz[fila][columna] == ENTRANCE )
        cout << "\nError: Hay una Entrada\\Salida " << endl;
    else if(matriz[fila][columna] == WALL)
        cout << "\nErrod: Ya existe una pared" << endl;
    else if(matriz[fila-1][columna] == ENTRANCE ||
            matriz[fila-1][columna] == EXIT)
        cout << "\nError: Cierra Salida\\Entrada" << endl;
    else if(matriz[fila][columna-1] == ENTRANCE ||
            matriz[fila][columna-1] == EXIT)
        cout << "\nError: Cierra Salida\\Entrada" << endl;
    else if(matriz[fila][columna+1] == ENTRANCE||
            matriz[fila][columna+1] == EXIT)
        cout << "\nError: Cierra Salida\\Entrada" << endl;
    else if(matriz[fila+1][columna] == ENTRANCE ||
            matriz[fila+1][columna] == EXIT)
        cout << "\nError: Cierra Salida\\Entrada" << endl;
    else
        matriz[fila][columna] = WALL;

    system("pause");
    system("cls");
}
