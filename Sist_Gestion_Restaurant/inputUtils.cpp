#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cstring>

#ifdef _WIN32
#include <windows.h>
#endif

#include "inputUtils.h"

using namespace std;

void configurarConsola()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

void leerCadena(const char* mensaje, char* destino, int tamanio)
{
    string valor;

    cout << mensaje;
    getline(cin >> ws, valor);

    strncpy(destino, valor.c_str(), tamanio - 1);
    destino[tamanio - 1] = '\0';
}

int leerEntero(const char* mensaje)
{
    int valor;

    while(true)
    {
        cout << mensaje;
        if(cin >> valor)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }

        cout << "Entrada invalida. Ingrese un numero entero." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int leerEnteroEnRango(const char* mensaje, int minimo, int maximo)
{
    int valor;

    while(true)
    {
        valor = leerEntero(mensaje);
        if(valor >= minimo && valor <= maximo)
        {
            return valor;
        }

        cout << "El valor debe estar entre " << minimo << " y " << maximo << "." << endl;
    }
}

float leerFloatMinimo(const char* mensaje, float minimo)
{
    float valor;

    while(true)
    {
        cout << mensaje;
        if(cin >> valor)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(valor >= minimo)
            {
                return valor;
            }
            cout << "El valor debe ser mayor o igual a " << minimo << "." << endl;
        }
        else
        {
            cout << "Entrada invalida. Ingrese un numero." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

bool leerSiNo(const char* mensaje)
{
    return leerEnteroEnRango(mensaje, 0, 1) == 1;
}

static bool esFechaValida(int dia, int mes, int anio)
{
    if(dia <= 0 || mes <= 0 || anio <= 0 || mes > 12)
    {
        return false;
    }

    int dias[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;

    if(bisiesto)
    {
        dias[1]++;
    }

    return dia <= dias[mes - 1];
}

Fecha leerFecha(const char* mensaje)
{
    string linea;
    string extra;
    int dia;
    int mes;
    int anio;

    while(true)
    {
        cout << mensaje << " (dia mes anio): ";
        getline(cin >> ws, linea);

        istringstream entrada(linea);
        if((entrada >> dia >> mes >> anio) && !(entrada >> extra) && esFechaValida(dia, mes, anio))
        {
            return Fecha(dia, mes, anio);
        }

        cout << "Fecha invalida. Ingrese una fecha valida con formato dia mes anio." << endl;
    }
}
