#pragma once

#include "reserva.h"
#include <string>

class ReservaArchivo{
private:
    std::string _ruta;

public:
    ReservaArchivo();
    ReservaArchivo(std::string ruta);
    int getCantidadRegistros();
    bool guardar(Reserva reg);
    bool guardar(Reserva reg, int posicionAReemplazar);
    Reserva leer(int nroRegistro);
    void leer(Reserva *vec, int cantidadRegistrosALeer);
    int buscar(int ID);
    void vaciar();
};
