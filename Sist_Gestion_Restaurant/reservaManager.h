#pragma once

#include "menu.h"
#include "reservaArchivo.h"

class ReservaManager : public Menu{
private:
    ReservaArchivo _archivo;
    bool existeID(int id);
    int generarID();

public:
    ReservaManager();
    void mostrarOpciones();
    void ejecutarOpcion(int opcion);
    void cargar();
    void listar();
    void menuReserva();
};
