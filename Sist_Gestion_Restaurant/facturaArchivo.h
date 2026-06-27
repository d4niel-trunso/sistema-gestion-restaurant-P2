#pragma once

#include <string>
#include "factura.h"

class FacturaArchivo{
private:
    std::string _ruta;

public:
    FacturaArchivo();
    FacturaArchivo(std::string ruta);
    bool guardar(Factura reg);
    bool guardar(Factura reg, int pos);
    Factura leer(int pos);
    int getCantidadRegistros();
    int buscarPosicion(int idFactura);
};
