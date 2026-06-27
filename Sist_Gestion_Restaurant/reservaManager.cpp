#include <iostream>
#include <cstring>
#include "reservaManager.h"
#include "rlutil.h"
#include "inputUtils.h"

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
    int horaReserva;
    int cantidadComensales;
    int estadoReserva;
    bool estado;

    cout << "Ingrese los detalles de la reserva:" << endl;

    idReserva = generarID();

    cout << "ID Reserva: " << idReserva << endl;

    idCliente = leerEntero("ID Cliente: ");

    if(!clienteActivo(idCliente)){
        cout << "No existe un cliente activo con ese ID." << endl;
        return;
    }

    numeroMesa = leerEntero("Numero Mesa: ");

    if(!mesaActiva(numeroMesa)){
        cout << "No existe una mesa activa con ese numero." << endl;
        return;
    }

    Fecha f = leerFecha("Fecha de la Reserva");

    horaReserva = leerEnteroEnRango("Hora de la Reserva (ej. 21 para 21:00hs): ", 0, 23);

    cantidadComensales = leerEnteroEnRango("Cantidad de Comensales: ", 1, 100);

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
            mostrarReservaConDatos(reg);
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

    id = leerEntero("ID Reserva: ");

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

    id = leerEntero("ID Reserva a cancelar: ");

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
    int cantidadReservas = 0;
    Reserva *reservas = new Reserva[cantidad];

    for(int i = 0; i < cantidad; i++){
        Reserva reserva = _archivo.leer(i);
        if(reserva.getEstado()){
            reservas[cantidadReservas] = reserva;
            cantidadReservas++;
        }
    }

    ordenarReservasPorFecha(reservas, cantidadReservas);

    if(cantidadReservas == 0){
        cout << "No hay reservas activas para mostrar." << endl;
        delete[] reservas;
        return;
    }

    for(int i = 0; i < cantidadReservas; i++){
        mostrarReservaConDatos(reservas[i]);
    }

    delete[] reservas;
}

void ReservaManager::listarPorEstado()
{
    int cantidad = _archivo.getCantidadRegistros();
    int cantidadReservas = 0;
    Reserva *reservas = new Reserva[cantidad];

    for(int i = 0; i < cantidad; i++){
        Reserva reserva = _archivo.leer(i);
        if(reserva.getEstado()){
            reservas[cantidadReservas] = reserva;
            cantidadReservas++;
        }
    }

    ordenarReservasPorEstado(reservas, cantidadReservas);

    if(cantidadReservas == 0){
        cout << "No hay reservas activas para mostrar." << endl;
        delete[] reservas;
        return;
    }

    for(int i = 0; i < cantidadReservas; i++){
        mostrarReservaConDatos(reservas[i]);
    }

    delete[] reservas;
}

void ReservaManager::consultarPorFecha()
{
    bool encontro = false;

    Fecha fecha = leerFecha("Fecha a consultar");

    for(int i = 0; i < _archivo.getCantidadRegistros(); i++){
        Reserva reserva = _archivo.leer(i);
        if(reserva.getEstado() && mismaFecha(reserva.getFechaReserva(), fecha)){
            mostrarReservaConDatos(reserva);
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

    idCliente = leerEntero("ID Cliente: ");

    for(int i = 0; i < _archivo.getCantidadRegistros(); i++){
        Reserva reserva = _archivo.leer(i);
        if(reserva.getEstado() && reserva.getIdCliente() == idCliente){
            mostrarReservaConDatos(reserva);
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

    estadoReserva = leerEnteroEnRango("Estado (1-Pendiente, 2-Completada, 3-Cancelada): ", 1, 3);

    for(int i = 0; i < _archivo.getCantidadRegistros(); i++){
        Reserva reserva = _archivo.leer(i);
        if(reserva.getEstado() && reserva.getEstadoReserva() == estadoReserva){
            mostrarReservaConDatos(reserva);
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
        mostrarReservaConDatos(reserva);
    }else{
        cout << "La reserva esta dada de baja." << endl;
    }
}

void ReservaManager::mostrarReservaConDatos(Reserva reserva)
{
    if(!reserva.getEstado())
    {
        return;
    }

    cout << "-----------------------------------------" << endl;
    cout << "Reserva #" << reserva.getIdReserva() << endl;

    int posCliente = _archivoCliente.buscar(reserva.getIdCliente());
    cout << "Cliente: ";
    if(posCliente >= 0)
    {
        Cliente cliente = _archivoCliente.leer(posCliente);
        cout << cliente.getApellido() << ", " << cliente.getNombre()
             << " (ID " << reserva.getIdCliente() << ")";
    }
    else
    {
        cout << "No encontrado (ID " << reserva.getIdCliente() << ")";
    }
    cout << endl;

    int posMesa = _archivoMesa.buscar(reserva.getNumeroMesa());
    cout << "Mesa: " << reserva.getNumeroMesa();
    if(posMesa >= 0)
    {
        Mesa mesa = _archivoMesa.leer(posMesa);
        cout << " - " << mesa.getDescripcion() << " - ";
        switch(mesa.getUbicacion())
        {
            case 1: cout << "Interior"; break;
            case 2: cout << "Terraza"; break;
            default: cout << "Ubicacion desconocida"; break;
        }
    }
    cout << endl;

    cout << "Fecha: " << reserva.getFechaReserva().toString() << endl;
    cout << "Hora: " << reserva.getHoraReserva() << ":00hs" << endl;
    cout << "Comensales: " << reserva.getCantidadComensales() << endl;
    cout << "Estado de la reserva: ";
    switch(reserva.getEstadoReserva())
    {
        case 1: cout << "PENDIENTE"; break;
        case 2: cout << "COMPLETADA"; break;
        case 3: cout << "CANCELADA"; break;
        default: cout << "DESCONOCIDO"; break;
    }
    cout << endl;
}
