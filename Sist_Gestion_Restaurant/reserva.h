#pragma once

#include "fecha.h"

class Reserva{
private:
    int _idReserva;
    int _idCliente;
    int _numeroMesa;
    Fecha _fechaReserva;
    int _horaReserva;
    int _cantidadComensales;
    int _estadoReserva;
    bool _estado;

public:
    Reserva();
    Reserva(int idReserva, int idCliente, int numeroMesa, Fecha fechaReserva, int horaReserva,
            int cantidadComensales, int estadoReserva, bool estado);

    ///Getters
    int getIdReserva();
    int getIdCliente();
    int getNumeroMesa();
    Fecha getFechaReserva();
    int getHoraReserva();
    int getCantidadComensales();
    int getEstadoReserva();
    bool getEstado();

    ///Setters
    void setIdReserva(int idReserva);
    void setIdCliente(int idCliente);
    void setNumeroMesa(int numeroMesa);
    void setFechaReserva(Fecha fechaReserva);
    void setHoraReserva(int horaReserva);
    void setCantidadComensales(int cantidadComensales);
    void setEstadoReserva(int estadoReserva);
    void setEstado(bool estado);

    void mostrar();
};
