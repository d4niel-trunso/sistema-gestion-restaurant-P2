#include <iostream>
#include <cstring>
using namespace std;
#include "mesa.h"

Mesa :: Mesa()
{
    _numeroMesa = 0;
    strcpy(_descripcion,"");
    _cantidadSillas = 0;
    _ubicacion = 0;
    _estado = false;
}

/// SETTERS
void Mesa :: setNumeroMesa(int numero)
{
    _numeroMesa = numero;
}
void Mesa ::  setDescripcion(char* descripcion)
{
    strcpy(_descripcion,descripcion);
}
void Mesa ::  setCantidadSillas(int cantidad)
{
    _cantidadSillas = cantidad;
}
void Mesa ::  setUbicacion(int ubicacion)
{
    _ubicacion = ubicacion;
}
void Mesa ::  setEstado(bool estado)
{
    _estado = estado;
}

/// GETTERS
int Mesa ::  getNumeroMesa()
{
    return _numeroMesa;
}
char* Mesa ::  getDescripcion()
{
    return _descripcion;
}
int Mesa ::  getCantidadSillas()
{
    return _cantidadSillas;
}
int Mesa ::  getUbicacion()
{
    return _ubicacion;
}
bool Mesa ::  getEstado()
{
    return _estado;
}

///
void Mesa ::  cargar()
{
    int numeroMesa;
    char descripcion[50];
    int cantidadSillas;
    int ubicacion;
    bool estado;

    cout << "INGRESAR LA INFORMACION DE LA MESA.." << endl;
    cout << "NUMERO DE MESA : ";
    cin >> numeroMesa;

    cout << "DESCRIPCION : ";
    cin >> descripcion;

    cout << "CANTIDAD DE SILLAS : ";
    cin >> cantidadSillas;

    cout << "UBICACION..." << endl;
    cout << "1/INTERIOR " << endl;
    cout << "2/TERRAZA " << endl;
    cout << "INGRESE : ";
    cin >> ubicacion;

    estado = true;

    setNumeroMesa(numeroMesa);
    setDescripcion(descripcion);
    setCantidadSillas(cantidadSillas);
    setUbicacion(ubicacion);
    setEstado(estado);

}
void Mesa ::  mostrar()
{

    cout << "MOSTRANDO INFORMACION DE LA MESA.."<< endl;
    cout << "NUMERO DE MESA : " << _numeroMesa <<endl;
    cout << "DESCRIPCION : " << _descripcion << endl;
    cout << "CANTIDAD DE SILLAS : " << _cantidadSillas << endl;
    cout << "UBICACION : " << _ubicacion << endl;
    cout << "ESTADO : " << _estado << endl;
}
