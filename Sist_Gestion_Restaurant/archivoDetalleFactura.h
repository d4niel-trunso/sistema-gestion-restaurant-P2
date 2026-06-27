#pragma once

#include "DetalleFactura.h"

class ArchivoDetalleFactura{
private:
    char _nombreArchivo[30];
public:

    ArchivoDetalleFactura();

    int getCantidadRegistros();
    bool guardar(DetalleFactura obj);
    DetalleFactura leer(int pos);

};
