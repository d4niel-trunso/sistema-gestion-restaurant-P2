#pragma once

#include "reservaArchivo.h"

class ReservaManager{
private:
    ReservaArchivo _archivo;
    bool existeID(int id);
    int generarID();

public:
    void cargar();
    void listar();
    void menuReserva();
};
