#include <iostream>
using namespace std;

#include "cliente.h"
#include "persona.h"
#include "utilidades.h"

Cliente :: Cliente()
{

    _idCliente = 0;
    _esVip = false;
}

///SETTERS
void Cliente :: setIdCliente(int idCliente){
    _idCliente = idCliente;
}
void Cliente :: setEsVip(bool esVip){
    _esVip = esVip;
}

/// GETTERS
int Cliente :: getIdCliente(){
    return _idCliente;
}
bool Cliente :: getEsVip(){
    return _esVip;
}
///

void Cliente :: cargar(){

    bool esVip;

    cout << "INGRESE LA INFORMACION DEL CLIENTE.." << endl;

    Persona :: cargar();

    esVip = leerSiNo("ES VIP ?  (SI = 1 / NO = 0) ");

    setEsVip(esVip);

}

void Cliente :: mostrar(){

    Persona :: mostrar();

    cout << "ID CLIENTE : " << _idCliente << endl;
    cout << "ES VIP ? : ";
    switch(_esVip){
        case 0 : cout << "NO";
        break;
        case 1 : cout << "SI";
        break;
    }
    cout << endl;

}
