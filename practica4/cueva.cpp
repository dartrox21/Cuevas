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
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    WORD wOldColorAttrs;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    //Getting the las color used, in this case white
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes;


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
            else if(this->matriz[x][y] > 0 ){
                SetConsoleTextAttribute ( h, FOREGROUND_BLUE | FOREGROUND_INTENSITY );
                cout << matriz[x][y];
                //use the code below if you want to change the numbers for a symbol
//                char symbol = 254;
//                cout << symbol;
            }
            SetConsoleTextAttribute ( h, wOldColorAttrs);
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

int menor(int a, int b, int c, int d){
    if(a < 0)
        a = 1000;
    if(b < 0)
        b = 1000;
    if(c < 0)
        c = 1000;
    if(d < 0)
        d = 1000;
    int minimo = std::min(a,std::min(b,std::min(c,d)));
    if(minimo == a)
        return 1;
    else if(minimo == b)
        return 2;
    else if(minimo == c)
        return 3;
    else if(minimo == d)
        return 4;
    return 0;
}
void Cueva::encontrarRuta(){
    bool continuar = true;
    int filaTemp;
    int columnaTemp;
    for (int x = 0; x < fila; x++) {
        for (int y = 0; y < columna; y++) {
            if(matriz[x][y] == -3){
                filaTemp = x;
                columnaTemp = y;
                break;
            }
        }
    }
    //First 4 conditions are to take out the actual position from a shore
    if(columnaTemp-1 > 0){
        if (matriz[filaTemp][columnaTemp-1] >= 0) {
            matriz[filaTemp][columnaTemp-1] += 1;
            columnaTemp --;
        }
        else if(matriz[filaTemp][columnaTemp-1] == EXIT){
            continuar = false;
        }
    }
    if(columnaTemp+1 < this->columna){
        if(matriz[filaTemp][columnaTemp+1] >=0){
            matriz[filaTemp][columnaTemp+1] += 1;
            columnaTemp ++;
        }
        else if(matriz[filaTemp][columnaTemp+1] == EXIT){
            continuar = false;
        }
    }
    if(filaTemp-1 > 0){
        if(matriz[filaTemp-1][columnaTemp] >=0){
            matriz[filaTemp-1][columnaTemp] += 1;
            filaTemp --;
        }
        else if(matriz[filaTemp-1][columnaTemp] == EXIT){
            continuar = false;
        }
    }
    if(filaTemp+1 < this->fila){
        if(matriz[filaTemp+1][columnaTemp] >=0){
            matriz[filaTemp+1][columnaTemp] += 1;
            filaTemp ++;
        }
        else if(matriz[filaTemp+1][columnaTemp] == EXIT){
            continuar = false;
        }
    }

    int getMenor;
    while(continuar == true){
        if((matriz[filaTemp][columnaTemp-1] == EXIT)||
                (matriz[filaTemp][columnaTemp+1] == EXIT) ||
                (matriz[filaTemp-1][columnaTemp] == EXIT) ||
                (matriz[filaTemp+1][columnaTemp] == EXIT)){
            continuar = false;
            break;
        }

        getMenor = menor(matriz[filaTemp][columnaTemp-1],
                matriz[filaTemp][columnaTemp+1],
                matriz[filaTemp-1][columnaTemp],
                 matriz[filaTemp+1][columnaTemp]);
        if (getMenor == 1) {
            matriz[filaTemp][columnaTemp-1] += 1;
            columnaTemp--;
        }
        else if (getMenor == 2) {
            matriz[filaTemp][columnaTemp+1] += 1;
            columnaTemp++;
        }
        else if(getMenor == 3){
            matriz[filaTemp-1][columnaTemp] += 1;
            filaTemp--;
        }
        else if (getMenor == 4) {
            matriz[filaTemp+1][columnaTemp] += 1;
            filaTemp++;
        }
    }
}
