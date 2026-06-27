#include <iostream>
#include <cstring>
using namespace std;

#include "persona.h"
#include "inputUtils.h"

Persona :: Persona()
{
    strcpy(_dni, "");
    strcpy(_nombre, "");
    strcpy(_apellido, "");
    strcpy(_telefono, "");
    _estado = false;
}

/// SETTERS
void Persona :: setDni(char* dni)
{
    strcpy(_dni, dni);
}
void Persona :: setNombre(char* nombre)
{
    strcpy(_nombre, nombre);
}
void Persona :: setApellido(char* apellido)
{
    strcpy(_apellido, apellido);
}
void Persona :: setTelefono(char* telefono)
{
    strcpy(_telefono, telefono);
}
void Persona :: setEstado(bool estado)
{
    _estado = estado;
}

/// GETTERS
char* Persona :: getDni()
{
    return _dni;
}
char* Persona :: getNombre()
{
    return _nombre;
}
char* Persona :: getApellido()
{
    return _apellido;
}
char* Persona :: getTelefono()
{
    return _telefono;
}
bool Persona :: getEstado()
{
    return _estado;
}

///
void Persona :: cargar()
{
    char dni[15];
    char nombre[30];
    char apellido[30];
    char telefono[20];

    leerCadena("DNI : ", dni, 15);
    leerCadena("NOMBRE : ", nombre, 30);
    leerCadena("APELLIDO : ", apellido, 30);
    leerCadena("TELEFONO : ", telefono, 20);

    setDni(dni);
    setNombre(nombre);
    setApellido(apellido);
    setTelefono(telefono);
    setEstado(true);
}

void Persona :: mostrar()
{
    cout << "-----------------------------------------" << endl;
    cout << "DNI : " << _dni << endl;
    cout << "NOMBRE : " << _nombre << endl;
    cout << "APELLIDO : " << _apellido << endl;
    cout << "TELEFONO : " << _telefono << endl;
    cout << "ESTADO : ";
    switch(_estado)
    {
        case 0: cout << "INACTIVO";
        break;
        case 1: cout << "ACTIVO";
        break;
    }
    cout << endl;
}
