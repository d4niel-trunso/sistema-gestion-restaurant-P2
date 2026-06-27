#include <iostream>
using namespace std;

#include "cliente.h"
#include "persona.h"

Cliente :: cliente()
{

    _idCliente = 0;
    _esVip = false;
}

///SETTERS
void Cliente :: setIdCliente(int idCliente){
    _idCliente = idCliente;
}
bool Cliente :: setEsVip(bool esVip){
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
