#include <iostream>
#include "reserva.h"

using namespace std;

Reserva::Reserva(){
    _estado = true;
    _estadoReserva = 1; ///Toda nueva reserva estara como "Pendiente"
}

Reserva::Reserva(int idReserva, int idCliente, int numeroMesa, Fecha fechaReserva, int horaReserva,
            int cantidadComensales, int estadoReserva, bool estado){
    _idReserva = idReserva;
    _idCliente = idCliente;
    _numeroMesa = numeroMesa;
    _fechaReserva = fechaReserva;
    _horaReserva = horaReserva;
    _cantidadComensales = cantidadComensales;
    _estadoReserva = estadoReserva;
    _estado = estado;
}

int Reserva::getIdReserva(){
    return _idReserva;
}

int Reserva::getIdCliente(){
    return _idCliente;
}

int Reserva::getNumeroMesa(){
    return _numeroMesa;
}

Fecha Reserva::getFechaReserva(){
    return _fechaReserva;
}

int Reserva::getHoraReserva(){
    return _horaReserva;
}

int Reserva::getCantidadComensales(){
    return _cantidadComensales;
}

int Reserva::getEstadoReserva(){
    return _estadoReserva;
}

bool Reserva::getEstado(){
    return _estado;
}

void Reserva::setIdReserva(int idReserva){
    _idReserva = idReserva;
}

void Reserva::setIdCliente(int idCliente){
    _idCliente = idCliente;
}
void Reserva::setNumeroMesa(int numeroMesa){
    _numeroMesa = numeroMesa;
}

void Reserva::setFechaReserva(Fecha fechaReserva){
    _fechaReserva = fechaReserva;
}

void Reserva::setHoraReserva(int horaReserva){
    _horaReserva = horaReserva;
}

void Reserva::setCantidadComensales(int cantidadComensales){
    _cantidadComensales = cantidadComensales;
}

void Reserva::setEstadoReserva(int estadoReserva){
    _estadoReserva = estadoReserva;
}

void Reserva::setEstado(bool estado){
    _estado = estado;
}

void Reserva::mostrar(){
    if(_estado){ //Solo se muestra si no esta dada de baja
        cout << "Reserva #" << _idReserva << endl;
        cout << "Mesa: " << _numeroMesa << endl;
        cout << "ID Cliente: " << _idCliente << endl;
        cout << "Fecha: " << _fechaReserva.toString() << endl;
        cout << "Hora: " << _horaReserva << ":00hs" << endl;
        cout << "Comensales: " << _cantidadComensales << endl;
        cout << "Estado de la reserva: ";
        switch(_estadoReserva){
        case 1:
            cout << "PENDIENTE" << endl;
            break;
        case 2:
            cout << "COMPLETADA" << endl;
            break;
        case 3:
            cout << "CANCELADA" << endl;
            break;
        default:
            cout << "DESCONOCIDO" << endl;
            break;
        }
        cout << "-----------------------------------------" << endl;
    }
}
