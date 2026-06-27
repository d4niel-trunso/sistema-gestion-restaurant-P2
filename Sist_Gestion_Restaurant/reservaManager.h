#pragma once

#include "menu.h"
#include "reservaArchivo.h"
#include "archivoCliente.h"
#include "archivoMesa.h"

class ReservaManager : public Menu{
private:
    ReservaArchivo _archivo;
    ArchivoCliente _archivoCliente;
    ArchivoMesa _archivoMesa;
    bool existeID(int id);
    int generarID();
    bool clienteActivo(int idCliente);
    bool mesaActiva(int numeroMesa);
    bool existeReservaActiva(int numeroMesa, Fecha fecha, int horaReserva);
    bool mismaFecha(Fecha a, Fecha b);
    void listarReserva(Reserva reserva);
    void mostrarReservaConDatos(Reserva reserva);

public:
    ReservaManager();
    void mostrarOpciones();
    void ejecutarOpcion(int opcion);
    void cargar();
    void listar();
    void buscarPorID();
    void cancelarReserva();
    void listarPorFecha();
    void listarPorEstado();
    void consultarPorFecha();
    void consultarPorCliente();
    void consultarPorEstado();
    void menuReserva();
};
