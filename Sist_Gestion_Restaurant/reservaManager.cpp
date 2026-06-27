#include <iostream>
#include <vector>
#include <algorithm>
#include "reservaManager.h"
#include "rlutil.h"

using namespace std;

ReservaManager::ReservaManager()
{
    setCantidadOpciones(9);
}

void ReservaManager::mostrarOpciones()
{
    rlutil::setBackgroundColor(rlutil::GREEN);
    rlutil::setColor(rlutil::WHITE);
    rlutil::cls();

    cout << "-------- MENU DE RESERVAS --------" << endl;
    cout << "                                  " << endl;
    cout << "1. NUEVA RESERVA                  " << endl;
    cout << "2. LISTAR TODAS LAS RESERVAS      " << endl;
    cout << "3. BUSCAR POR ID                  " << endl;
    cout << "4. CANCELAR RESERVA               " << endl;
    cout << "5. LISTADO POR FECHA              " << endl;
    cout << "6. LISTADO POR ESTADO             " << endl;
    cout << "7. CONSULTA POR FECHA             " << endl;
    cout << "8. CONSULTA POR CLIENTE           " << endl;
    cout << "9. CONSULTA POR ESTADO            " << endl;
    cout << "                                  " << endl;
    cout << "0. VOLVER AL MENU PRINCIPAL       " << endl;
    cout << "                                  " << endl;
    cout << "----------------------------------" << endl;
}

void ReservaManager::ejecutarOpcion(int opcion)
{
    switch(opcion)
    {
    case 1:
        cout << "=== RESERVAS ===" << endl;
        cargar();
        break;
    case 2:
        cout << "=== LISTADO DE RESERVAS ===" << endl;
        listar();
        break;
    case 3:
        buscarPorID();
        break;
    case 4:
        cancelarReserva();
        break;
    case 5:
        listarPorFecha();
        break;
    case 6:
        listarPorEstado();
        break;
    case 7:
        consultarPorFecha();
        break;
    case 8:
        consultarPorCliente();
        break;
    case 9:
        consultarPorEstado();
        break;
    case 0:
        cout << "Volviendo al menu principal..." << endl;
        break;
    }
}

void ReservaManager::menuReserva()
{
    iniciar();
}

void ReservaManager::cargar()
{
    int idReserva;
    int idCliente;
    int numeroMesa;
    int dia, mes, anio;
    int horaReserva;
    int cantidadComensales;
    int estadoReserva;
    bool estado;

    cout << "Ingrese los detalles de la reserva:" << endl;

    idReserva = generarID();

    cout << "ID Reserva: " << idReserva << endl;

    cout << "ID Cliente: ";
    cin >> idCliente;

    if(!clienteActivo(idCliente)){
        cout << "No existe un cliente activo con ese ID." << endl;
        return;
    }

    cout << "Numero Mesa: ";
    cin >> numeroMesa;

    if(!mesaActiva(numeroMesa)){
        cout << "No existe una mesa activa con ese numero." << endl;
        return;
    }

    cout << "Fecha de la Reserva (dia mes anio): ";
    cin >> dia;
    cin >> mes;
    cin >> anio;

    Fecha f(dia, mes, anio);

    cout << "Hora de la Reserva (ej. 21 para 21:00hs): ";
    cin >> horaReserva;

    if(horaReserva < 0 || horaReserva > 23){
        cout << "La hora debe estar entre 0 y 23." << endl;
        return;
    }

    cout << "Cantidad de Comensales: ";
    cin >> cantidadComensales;

    if(cantidadComensales <= 0){
        cout << "La cantidad de comensales debe ser mayor a 0." << endl;
        return;
    }

    if(existeReservaActiva(numeroMesa, f, horaReserva)){
        cout << "Ya existe una reserva activa para esa mesa, fecha y hora." << endl;
        return;
    }

    estadoReserva = 1;
    estado = true;

    Reserva reserva(idReserva, idCliente, numeroMesa, f, horaReserva, cantidadComensales, estadoReserva, estado);

    if(_archivo.guardar(reserva)){
        cout << "Reserva generada y guardada exitosamente!" << endl;
    }else{
        cout << "Error al intentar acceder al archivo reservas.dat." << endl;
    }
}

void ReservaManager::listar()
{
    int cantidad = _archivo.getCantidadRegistros();
    bool encontro = false;

    if (cantidad == 0) {
        cout << "No hay reservas registradas en el sistema." << endl;
        return;
    }

    for(int i = 0; i < cantidad; i++)
    {
        Reserva reg = _archivo.leer(i);
        if(reg.getEstado()){
            reg.mostrar();
            encontro = true;
        }
    }

    if(!encontro){
        cout << "No hay reservas activas para mostrar." << endl;
    }
}

void ReservaManager::buscarPorID()
{
    int id;

    cout << "ID Reserva: ";
    cin >> id;

    int pos = _archivo.buscar(id);

    if(pos < 0){
        cout << "No se encontro una reserva con ese ID." << endl;
        return;
    }

    listarReserva(_archivo.leer(pos));
}

void ReservaManager::cancelarReserva()
{
    int id;

    cout << "ID Reserva a cancelar: ";
    cin >> id;

    int pos = _archivo.buscar(id);

    if(pos < 0){
        cout << "No se encontro una reserva con ese ID." << endl;
        return;
    }

    Reserva reserva = _archivo.leer(pos);

    if(!reserva.getEstado()){
        cout << "La reserva esta dada de baja." << endl;
        return;
    }

    if(reserva.getEstadoReserva() == 3){
        cout << "La reserva ya estaba cancelada." << endl;
        return;
    }

    reserva.setEstadoReserva(3);

    if(_archivo.guardar(reserva, pos)){
        cout << "Reserva cancelada correctamente." << endl;
    }else{
        cout << "No se pudo actualizar la reserva." << endl;
    }
}

void ReservaManager::listarPorFecha()
{
    int cantidad = _archivo.getCantidadRegistros();
    vector<Reserva> reservas;

    for(int i = 0; i < cantidad; i++){
        Reserva reserva = _archivo.leer(i);
        if(reserva.getEstado()){
            reservas.push_back(reserva);
        }
    }

    sort(reservas.begin(), reservas.end(), [](Reserva a, Reserva b){
        return a.getFechaReserva().toNumero() < b.getFechaReserva().toNumero();
    });

    if(reservas.size() == 0){
        cout << "No hay reservas activas para mostrar." << endl;
        return;
    }

    for(int i = 0; i < (int)reservas.size(); i++){
        reservas[i].mostrar();
    }
}

void ReservaManager::listarPorEstado()
{
    int cantidad = _archivo.getCantidadRegistros();
    vector<Reserva> reservas;

    for(int i = 0; i < cantidad; i++){
        Reserva reserva = _archivo.leer(i);
        if(reserva.getEstado()){
            reservas.push_back(reserva);
        }
    }

    sort(reservas.begin(), reservas.end(), [](Reserva a, Reserva b){
        return a.getEstadoReserva() < b.getEstadoReserva();
    });

    if(reservas.size() == 0){
        cout << "No hay reservas activas para mostrar." << endl;
        return;
    }

    for(int i = 0; i < (int)reservas.size(); i++){
        reservas[i].mostrar();
    }
}

void ReservaManager::consultarPorFecha()
{
    int dia, mes, anio;
    bool encontro = false;

    cout << "Fecha a consultar (dia mes anio): ";
    cin >> dia >> mes >> anio;

    Fecha fecha(dia, mes, anio);

    for(int i = 0; i < _archivo.getCantidadRegistros(); i++){
        Reserva reserva = _archivo.leer(i);
        if(reserva.getEstado() && mismaFecha(reserva.getFechaReserva(), fecha)){
            reserva.mostrar();
            encontro = true;
        }
    }

    if(!encontro){
        cout << "No hay reservas para esa fecha." << endl;
    }
}

void ReservaManager::consultarPorCliente()
{
    int idCliente;
    bool encontro = false;

    cout << "ID Cliente: ";
    cin >> idCliente;

    for(int i = 0; i < _archivo.getCantidadRegistros(); i++){
        Reserva reserva = _archivo.leer(i);
        if(reserva.getEstado() && reserva.getIdCliente() == idCliente){
            reserva.mostrar();
            encontro = true;
        }
    }

    if(!encontro){
        cout << "No hay reservas para ese cliente." << endl;
    }
}

void ReservaManager::consultarPorEstado()
{
    int estadoReserva;
    bool encontro = false;

    cout << "Estado (1-Pendiente, 2-Completada, 3-Cancelada): ";
    cin >> estadoReserva;

    for(int i = 0; i < _archivo.getCantidadRegistros(); i++){
        Reserva reserva = _archivo.leer(i);
        if(reserva.getEstado() && reserva.getEstadoReserva() == estadoReserva){
            reserva.mostrar();
            encontro = true;
        }
    }

    if(!encontro){
        cout << "No hay reservas con ese estado." << endl;
    }
}

bool ReservaManager::existeID(int id)
{
    return _archivo.buscar(id) >= 0;
}

int ReservaManager::generarID()
{
    return _archivo.getCantidadRegistros() + 1;
}

bool ReservaManager::clienteActivo(int idCliente)
{
    int pos = _archivoCliente.buscar(idCliente);

    if(pos < 0){
        return false;
    }

    Cliente cliente = _archivoCliente.leer(pos);
    return cliente.getEstado();
}

bool ReservaManager::mesaActiva(int numeroMesa)
{
    int pos = _archivoMesa.buscar(numeroMesa);

    if(pos < 0){
        return false;
    }

    Mesa mesa = _archivoMesa.leer(pos);
    return mesa.getEstado();
}

bool ReservaManager::existeReservaActiva(int numeroMesa, Fecha fecha, int horaReserva)
{
    int cantidad = _archivo.getCantidadRegistros();

    for(int i = 0; i < cantidad; i++){
        Reserva reserva = _archivo.leer(i);
        if(reserva.getEstado()
           && reserva.getEstadoReserva() != 3
           && reserva.getNumeroMesa() == numeroMesa
           && reserva.getHoraReserva() == horaReserva
           && mismaFecha(reserva.getFechaReserva(), fecha)){
            return true;
        }
    }

    return false;
}

bool ReservaManager::mismaFecha(Fecha a, Fecha b)
{
    return a.toNumero() == b.toNumero();
}

void ReservaManager::listarReserva(Reserva reserva)
{
    if(reserva.getEstado()){
        reserva.mostrar();
    }else{
        cout << "La reserva esta dada de baja." << endl;
    }
}
