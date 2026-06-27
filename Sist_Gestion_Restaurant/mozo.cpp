#include <iostream>
#include <cstring>
using namespace std;

#include "mozo.h"
#include "fecha.h"

Mozo :: Mozo()
{

    _idMozo = 0;
    strcpy(_email, "");
    _turno = 0;
    _fechaNacimiento = Fecha();
}

/// SETTERS
void Mozo :: setIdMozo(int idMozo)
{
    _idMozo = idMozo;
}
void Mozo :: setEmail(char* email)
{
    strcpy(_email, email);
}
void Mozo :: setTurno(int valor)
{
    _turno = valor;
}
void Mozo :: setFechaNacimiento(int dia, int mes, int anio)
{
    _fechaNacimiento = Fecha(dia, mes,anio);
}

/// GETTERS
Fecha Mozo :: getFechaNacimiento()
{
    return _fechaNacimiento;
}
int Mozo :: getIdMozo()
{
    return _idMozo;
}
int Mozo :: getTurno()
{
    return _turno;
}
char* Mozo :: getEmail()
{
    return _email;
}


///

void Mozo :: cargar(){

    char email [50];
    int turno;

    int dia;
    int mes;
    int anio;

    Fecha fechaNacimiento;

    cout << "INGRESE LA INFORMACION DEL MOZO.." << endl;

    Persona :: cargar();

    cout << "EMAIL : ";
    cin >> email;

    cout << "SELECCIONE EL TURNO.. ";
    cout << "1/ Maniana" << endl;
    cout << "2/ Tarde" << endl;
    cout << "3/ Noche";
    cin >> turno;

    cout << "FECHA DE NACIMIENTO..."<<endl;
    cout << "DIA : ";
    cin >> dia;
    cout << "MES : ";
    cin >> mes;
    cout << "ANIO : ";
    cin >> anio;

    setEmail(email);
    setTurno(turno);
    setFechaNacimiento(dia,mes,anio);

}
void Mozo :: mostrar(){

    Persona :: mostrar();

    cout << "ID MOZO : " << _idMozo << endl;
    cout << "EMAIL : " << _email << endl;
    cout << "TURNO : " ;
    switch(_turno){
        case 1 : cout << "Maniana";
        break;
        case 2 : cout << "Tarde";
        break;
        case 3 : cout << "Noche";
        break;
    }

    cout << "FECHA DE NACIMIENTO : " << _fechaNacimiento.toString("DD/MM/YYYY") << endl;

}
