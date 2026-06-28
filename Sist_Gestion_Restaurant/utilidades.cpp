#include <iostream>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#endif

#include "utilidades.h"

using namespace std;

void configurarConsola()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

static void limpiarBuffer()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void leerCadena(const char* mensaje, char* destino, int tamanio)
{
    cout << mensaje;
    cin >> ws;
    cin.getline(destino, tamanio);

    // Si el usuario ingresa una cadena de caracteres mas larga de la que se puede almacenar,
    // cin.getline va a llenar la cadena hasta tamanio y va a quedar en estado de error.
    // Por lo que limpiamos el error y el buffer para siguientes ingresos.
    if(cin.fail())
    {
        cin.clear();
        limpiarBuffer();
    }
}

int leerEntero(const char* mensaje)
{
    int valor;

    while(true)
    {
        cout << mensaje;
        if(cin >> valor)
        {
            limpiarBuffer();
            return valor;
        }

        cout << "Entrada invalida. Ingrese un numero entero." << endl;
        cin.clear();
        limpiarBuffer();
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
            limpiarBuffer();
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
            limpiarBuffer();
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

static bool esDigito(char caracter)
{
    return caracter >= '0' && caracter <= '9';
}

static bool esEspacio(char caracter)
{
    return caracter == ' ' || caracter == '\t' || caracter == '\r';
}

static bool leerNumeroFecha(const char* linea, int& posicion, int& numero)
{
    if(!esDigito(linea[posicion]))
    {
        return false;
    }

    numero = 0;
    while(esDigito(linea[posicion]))
    {
        numero = numero * 10 + (linea[posicion] - '0');
        posicion++;
    }

    return true;
}

static bool parsearFecha(const char* linea, int& dia, int& mes, int& anio)
{
    int posicion = 0;

    if(!leerNumeroFecha(linea, posicion, dia) || linea[posicion] != '/')
    {
        return false;
    }
    posicion++;

    if(!leerNumeroFecha(linea, posicion, mes) || linea[posicion] != '/')
    {
        return false;
    }
    posicion++;

    if(!leerNumeroFecha(linea, posicion, anio))
    {
        return false;
    }

    while(linea[posicion] != '\0')
    {
        if(!esEspacio(linea[posicion]))
        {
            return false;
        }
        posicion++;
    }

    return true;
}

Fecha leerFecha(const char* mensaje)
{
    char linea[50];
    int dia;
    int mes;
    int anio;

    while(true)
    {
        cout << mensaje << " (dia/mes/anio): ";
        cin >> ws;
        cin.getline(linea, 50);

        if(cin.fail())
        {
            cin.clear();
            limpiarBuffer();
        }
        else if(parsearFecha(linea, dia, mes, anio) && esFechaValida(dia, mes, anio))
        {
            return Fecha(dia, mes, anio);
        }

        cout << "Fecha invalida. Ingrese una fecha valida con formato dia/mes/anio." << endl;
    }
}

void ordenarFacturasPorFecha(Factura *facturas, int cantidad)
{
    for(int i = 0; i < cantidad - 1; i++)
    {
        for(int j = 0; j < cantidad - i - 1; j++)
        {
            if(facturas[j].getFechaFactura().toNumero() > facturas[j + 1].getFechaFactura().toNumero())
            {
                Factura aux = facturas[j];
                facturas[j] = facturas[j + 1];
                facturas[j + 1] = aux;
            }
        }
    }
}

void ordenarFacturasPorMesa(Factura *facturas, int cantidad)
{
    for(int i = 0; i < cantidad - 1; i++)
    {
        for(int j = 0; j < cantidad - i - 1; j++)
        {
            if(facturas[j].getNumeroMesa() > facturas[j + 1].getNumeroMesa())
            {
                Factura aux = facturas[j];
                facturas[j] = facturas[j + 1];
                facturas[j + 1] = aux;
            }
        }
    }
}

void ordenarReservasPorFecha(Reserva *reservas, int cantidad)
{
    for(int i = 0; i < cantidad - 1; i++)
    {
        for(int j = 0; j < cantidad - i - 1; j++)
        {
            if(reservas[j].getFechaReserva().toNumero() > reservas[j + 1].getFechaReserva().toNumero())
            {
                Reserva aux = reservas[j];
                reservas[j] = reservas[j + 1];
                reservas[j + 1] = aux;
            }
        }
    }
}

void ordenarReservasPorEstado(Reserva *reservas, int cantidad)
{
    for(int i = 0; i < cantidad - 1; i++)
    {
        for(int j = 0; j < cantidad - i - 1; j++)
        {
            if(reservas[j].getEstadoReserva() > reservas[j + 1].getEstadoReserva())
            {
                Reserva aux = reservas[j];
                reservas[j] = reservas[j + 1];
                reservas[j + 1] = aux;
            }
        }
    }
}
